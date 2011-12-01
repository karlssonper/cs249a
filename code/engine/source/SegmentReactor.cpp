/*
 * SegmentReactor.cpp
 *
 *  Created on: Nov 23, 2011
 *      Author: per
 */

#include "SegmentReactor.h"
#include "Shipment.h"
#include "VirtualTimeActivityManager.h"
#include "ForwardActivityReactor.h"
#include <sstream>

using namespace Shipping;

SegmentReactor::SegmentReactor(std::string _name, Segment * seg,
        VirtualTimeActivityManager::Ptr vtam, Fleet::PtrConst _fleet) :
        Segment::Notifiee(_name, seg), owner_(seg), activityManager_(vtam),
        fleet_(_fleet) {

};

SegmentReactor::Ptr SegmentReactor::SegmentReactorNew(std::string _name,
        Segment * _owner, VirtualTimeActivityManager::Ptr vtam,
        Fleet::PtrConst _fleet) {
    Ptr p = new SegmentReactor(_name, _owner, vtam, _fleet);
    return p;
};

SegmentReactor::~SegmentReactor() {
    FWK_DEBUG("SegmentReactor::~SegmentReactor() for name " << name());
};


void SegmentReactor::onShipmentEnq(Shipment::Ptr _shipment) {
    FWK_DEBUG("SegmentReactor::onShipmentEnq() for name " << name());

    if (owner_->activePackages().value() < owner_->capacity().value()){
        createActivity(_shipment);
    }
};

void SegmentReactor::onShipmentDeq() {
    FWK_DEBUG("SegmentReactor::onShipmentDeq() for name " << name());
    addShipmentFromQueue();
};

void SegmentReactor::onActivePackageInc(PackageCount c) {
    FWK_DEBUG("SegmentReactor::onActivePackageInc() for name " << name());
    addShipmentFromQueue();
};

void SegmentReactor::onActivePackageDec(PackageCount c) {
    FWK_DEBUG("SegmentReactor::onActivePackageDec() for name " << name());
};

void SegmentReactor::createActivity(Shipment::Ptr _shipment) {

    PackageCount availableSegmentCapacity = owner_->capacity().value() -
                                            owner_->activePackages().value();
    PackageCount availableVehicleCapacity = fleet_->capacity(
            segTypeToFleetVehicle(owner_->type())
         );

    PackageCount availableCapacity =
            availableVehicleCapacity <  availableSegmentCapacity ?
                    availableVehicleCapacity : availableSegmentCapacity;

    PackageCount queuedPackages =
            _shipment->waitingPackages() > availableCapacity ?
                  availableCapacity : _shipment->waitingPackages();
    _shipment->queuedPackagesInc(queuedPackages);

    std::stringstream ss;
    ss << "VirtualTimeActivity" << VirtualTimeActivityManager::activityIndex();
    Fwk::Activity::Ptr activity = activityManager_->activityNew(ss.str());
    activity->nextTimeIs(activityManager_->now());
    activity->lastNotifieeIs(
            new ForwardActivityReactor(
                ss.str() + std::string("Reactor"),
                activityManager_.ptr(),
                activity.ptr(),
                fleet_,
                owner_,
                _shipment,
                queuedPackages
            )
    );
};

void SegmentReactor::addShipmentFromQueue() {
    PackageCount packages = owner_->activePackages();
    Segment::ShipmentIteratorConst it = owner_->shipmentIterConst();
    unsigned int i = 0;
    while (packages < owner_->capacity() && i < owner_->shipments()) {
        if ((*it)->waitingPackages() != 0) {
            createActivity(*it);
            break;
        }
        ++i;
    }
};

Fleet::Vehicle SegmentReactor::segTypeToFleetVehicle(
        Segment::SegmentType st) {
    switch(st){
        case Segment::boatSegment_:
            return Fleet::boat();
        case Segment::planeSegment_:
            return Fleet::plane();
        case Segment::truckSegment_:
            return Fleet::truck();
        default:
            return Fleet::undefined();
    }
};
