/*
 * ShippingActivityReactor.cpp
 *
 *  Created on: Nov 21, 2011
 *      Author: per
 */

#include "ShippingActivityReactor.h"

using namespace Shipping;

ShippingActivityReactor::ShippingActivityReactor(
        Fwk::Ptr<Activity::Manager> manager,
        Activity* activity,
        EngineManager * _engine,
        PackageCount _packages) :
            Notifiee(activity),
            activity_(activity),
            activityManager_(manager),
            conn_(_engine->conn().ptr()),
            entityManager_(_engine->entityManager())
            packages_(_packages),
            position_(created_)
{
}

void ShippingActivityReactor::onStatus(){
    switch (activity_->status()) {
        case Activity::executing: {
            //if moving, reset the queue time on the previous segment
            if (position_ == moving_ ){
                entityManager_->segmentQueueIs(curSeg_->name(), 0);
                position_ = idle_;
            }

            Segment::PtrConst nextSegment;
            //= conn_->connect(curLoc_->name(), dest_->name()));

            if (nextSegment->queue() > 0) {
                activity_->nextTimeIs(nextSegment->queue());
            }

            activity_->statusIs(Activity::nextTimeScheduled);
            break;
        }
        case Activity::free: {
            break;
        }
        case Activity::nextTimeScheduled: {
            //add myself to be scheduled
            manager_->lastActivityIs(activity_);
            break;

            break;
        }
        default: {


            break;
        }
    }
};
