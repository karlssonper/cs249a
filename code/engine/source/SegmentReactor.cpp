/*
 * SegmentReactor.cpp
 *
 *  Created on: Nov 23, 2011
 *      Author: per
 */

#include "SegmentReactor.h"
#include "Shipment.h"
#include "Fleet.h"
#include "VirtualTimeActivityManager.h"
#include "ForwardActivityReactor.h"

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
        Fwk::Activity::Ptr activity = activityManager_->activityNew("lol");
        activity->nextTimeIs(activityManager_->now());
        string s;
        activity->lastNotifieeIs(
                new ForwardActivityReactor(
                    s,
                    activityManager_.ptr(),
                    activity.ptr(),
                    fleet_,
                    owner_,
                    _shipment
                )
        );
    }
};

void SegmentReactor::onShipmentDeq() {
    FWK_DEBUG("SegmentReactor::onShipmentDeq() for name " << name());

    PackageCount packages = owner_->activePackages();
    Segment::ShipmentIteratorConst it = owner_->shipmentIterConst();
    unsigned int i = 0;
    while (packages < owner_->capacity() && i < owner_->shipments()) {
        ++i;
        //owner_->sh
    }

};

void SegmentReactor::onActivePackageInc(PackageCount c) {
    FWK_DEBUG("SegmentReactor::onActivePackageInc() for name " << name());


};

void SegmentReactor::onActivePackageDec(PackageCount c) {
    FWK_DEBUG("SegmentReactor::onActivePackageDec() for name " << name());
};
