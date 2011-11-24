/*
 * SegmentReactor.cpp
 *
 *  Created on: Nov 23, 2011
 *      Author: per
 */

#include "SegmentReactor.h"
#include "Shipment.h"

using namespace Shipping;

SegmentReactor::SegmentReactor(std::string _name, Segment * seg) :
        Segment::Notifiee(_name, seg), owner_(seg) {

};

SegmentReactor::~SegmentReactor() {
    FWK_DEBUG("SegmentReactor::~SegmentReactor() for name " << name());
};


void SegmentReactor::onShipmentEnq(Shipment::Ptr _shipment) {
    FWK_DEBUG("SegmentReactor::onShipmentEnq() for name " << name());

    if (owner_->activePackages().value() < owner_->capacity().value()){
        //Create activity
    }
};

void SegmentReactor::onShipmentDeq() {
    FWK_DEBUG("SegmentReactor::onShipmentDeq() for name " << name());

};

void SegmentReactor::onActivePackageInc(PackageCount c) {
    FWK_DEBUG("SegmentReactor::onActivePackageInc() for name " << name());


};

void SegmentReactor::onActivePackageDec(PackageCount c) {
    FWK_DEBUG("SegmentReactor::onActivePackageDec() for name " << name());
};
