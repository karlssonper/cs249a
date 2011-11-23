/*
 * ForwardActivityReactor.cpp
 *
 *  Created on: Nov 22, 2011
 *      Author: per
 */

#include "ForwardActivityReactor.h"
#include "Shipment.h"
#include "Fleet.h"
#include "Segment.h"

using namespace Shipping;


ForwardActivityReactor::ForwardActivityReactor(
        Fwk::Ptr<Fwk::Activity::Manager> _manager,
        Fwk::Activity* _activity,
        Fleet::PtrConst _fleet,
        Segment::Ptr _segment,
        Shipment::Ptr _shipment) :
        Notifiee(_activity),
        manager_(_manager),
        activity_(_activity),
        fleet_(_fleet),
        segment_(_segment),
        shipment_(_shipment)
{

}
void ForwardActivityReactor::onStatus() {
    switch (activity_->status()) {
        case Fwk::Activity::executing: {
            PackageCount packagesPerTransport;
            switch(segment_->type()){
                case Segment::boatSegment_:
                        packagesPerTransport = fleet_->capacity(Fleet::boat()).value();
                        break;
                case Segment::planeSegment_:
                        packagesPerTransport = fleet_->capacity(Fleet::plane()).value();
                        break;
                case Segment::truckSegment_:
                        packagesPerTransport = fleet_->capacity(Fleet::truck()).value();
                        break;
                default:
                    break;
            }


            shipment_->transferedPackagesInc(PackageCount());
            if (shipment_->waitingPackages() == shipment_->totalPackages()){
                //dequeue segment
                //entityManager->location->newSegment
                activity_->statusIs(Fwk::Activity::deleted);
            } else {
                //activity_->nextTimeIs(Hours(activity_->nextTime().value() + rate_));
                activity_->statusIs(Fwk::Activity::nextTimeScheduled);
            }

            break;
        }
    }
}
