/*
* ForwardActivityReactor.cpp
*
*  Created on: Nov 22, 2011
*      Author: per
*/

#include "ForwardActivityReactor.h"
#include "Shipment.h"


using namespace Shipping;


ForwardActivityReactor::ForwardActivityReactor(
    const std::string &_name,
    Fwk::Ptr<Fwk::Activity::Manager> _manager,
    Fwk::Activity* _activity,
    Fleet::PtrConst _fleet,
    Segment::Ptr _segment,
    Shipment::Ptr _shipment,
    PackageCount _quededPackages) :
Notifiee(_name,_activity),
    manager_(_manager),
    activity_(_activity),
    fleet_(_fleet),
    segment_(_segment),
    shipment_(_shipment),
    activePackages_(0),
    queuedPackages_(_quededPackages)
{

}

void ForwardActivityReactor::onStatus() {
    try {
        switch (activity_->status()) {
        case Fwk::Activity::executing: {
            removeActivePackagesFromSegment();
            if (queuedPackages_ > 0 ){
                shipment_->queuedPackagesDec(queuedPackages_);
                queuedPackages_ = 0;
            }
            if (shipment_->waitingPackages().value() == 0){
                segment_->shipmentDeq();

                //ADD TO NEXT LOCATION

                return;
            }
            addActivePackagesToSegment();
            forwardActivity();
            break;
                                       }
        case Fwk::Activity::nextTimeScheduled:
            manager_->lastActivityIs(activity_);
            break;
        default: 
            std::cerr << "ForwardActivityReactor::onStatus() out of range" << std::endl;
            throw(Fwk::RangeException("ForwardActivityReactor::onStatus()"));
        }
    } // try
    catch (Fwk::Exception e) {
        std::cerr << "Exception in ForwardActivityReactor::onStatus(): " << e.what() << std::endl;
        BaseNotifiee::onNotificationException();
    }
}

void ForwardActivityReactor::removeActivePackagesFromSegment() {
    FWK_DEBUG("ForwardActivityReactor::removeActivePackagesFromSegment");
    if (activePackages_.value() > 0) {
        FWK_DEBUG("Removing " << activePackages_.value() << " packages.");
        //segment_->packagesDec(activePackages_.value());
        activePackages_ = 0;
    }
};

void ForwardActivityReactor::addActivePackagesToSegment() {
    PackageCount availableSegmentCapacity = segment_->capacity().value() -
        segment_->activePackages().value();
    PackageCount availableVehicleCapacity = fleet_->capacity(
        segTypeToFleetVehicle(segment_->type())
        );

    PackageCount availableCapacity =
        availableVehicleCapacity <  availableSegmentCapacity ?
availableVehicleCapacity : availableSegmentCapacity;

    if (shipment_->waitingPackages() > availableCapacity) {
        segment_->activePackageInc(availableCapacity);
        shipment_->transferedPackagesInc(availableCapacity);
        activePackages_ = availableCapacity;
    } else {
        segment_->activePackageInc(shipment_->waitingPackages());
        shipment_->transferedPackagesInc(shipment_->waitingPackages());
        activePackages_ = shipment_->waitingPackages();
    }
};

void ForwardActivityReactor::forwardActivity() {
    MilesPerHour speed = fleet_->speed(segTypeToFleetVehicle(segment_->type()));
    Miles length = segment_->length();

    activity_->nextTimeIs(
        Fwk::Time(activity_->nextTime().value() +speed.value() / length.value())
        );
    activity_->statusIs(Fwk::Activity::nextTimeScheduled);
};

Fleet::Vehicle ForwardActivityReactor::segTypeToFleetVehicle(
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
