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
#include "Exception.h"
#include <sstream>
#include "Location.h"
#include "EntityManager.h"
using namespace Shipping;

SegmentReactor::SegmentReactor(std::string _name, Segment * seg,
        VirtualTimeActivityManager::Ptr vtam, Fleet::PtrConst _fleet,
        EntityManager::Ptr _entityManager) :
        Segment::Notifiee(_name, seg), owner_(seg), activityManager_(vtam),
        fleet_(_fleet), entityManager_(_entityManager) {

};

SegmentReactor::Ptr SegmentReactor::SegmentReactorNew(std::string _name,
        Segment * _owner, VirtualTimeActivityManager::Ptr vtam,
        Fleet::PtrConst _fleet, EntityManager::Ptr _entityManager) {
    Ptr p = new SegmentReactor(_name, _owner, vtam, _fleet,_entityManager);
    if (!p) {
        std::cerr << "SegmentReactorNew new() failed" << std::endl;
        throw(Fwk::MemoryException("SegmentReactorNew"));
    }
    return p;
};

SegmentReactor::~SegmentReactor() {
    FWK_DEBUG("SegmentReactor::~SegmentReactor() for name " << name());
};


void SegmentReactor::onShipmentEnq(Shipment::Ptr _shipment, Location::Ptr _nextLocation) {
    FWK_DEBUG("SegmentReactor::onShipmentEnq() for name " << name());
    if (owner_->activePackages().value() < owner_->capacity().value()){
        createActivity(_shipment,_nextLocation);
    } 
}

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

void SegmentReactor::createActivity(Shipment::Ptr _shipment, Location::Ptr _nextLocation) {

    PackageCount availableSegmentCapacity = owner_->capacity().value() -
                                            owner_->activePackages().value();
    PackageCount availableVehicleCapacity = fleet_->capacity(
            segTypeToFleetVehicle(owner_->type())
         );

    PackageCount availableCapacity =
            availableVehicleCapacity <  availableSegmentCapacity ?
availableVehicleCapacity : availableSegmentCapacity;
    FWK_SIM_DEBUG("SegmentReactor::createActivity availableCapacity: " << availableCapacity.value());
    if (availableCapacity == 0) return;

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
                _nextLocation,
                entityManager_,
                queuedPackages
            )
    );
    activity->statusIs(Fwk::Activity::nextTimeScheduled);
};

void SegmentReactor::addShipmentFromQueue() {
    PackageCount packages = owner_->activePackages();
    Segment::ShipmentIteratorConst it = owner_->shipmentIterConst();
    unsigned int i = 0;
    // owner (segment's) total package capacity is
    // the segment's shipment capacity (nr of shipments)
    // times the vehicles' capacity (nr of packages)
    PackageCount totalCapacity = owner_->capacity().value();
    while (packages < totalCapacity && i < owner_->shipments()) {
        if (it->shipment->waitingPackages() != 0) {
            createActivity(it->shipment,it->nextLocation);
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
