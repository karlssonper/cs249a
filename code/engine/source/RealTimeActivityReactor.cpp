/*
 * RealTimeActivityReactor.cpp
 *
 *  Created on: Nov 24, 2011
 *      Author: per
 */

#include "RealTimeActivityReactor.h"
#include "VirtualTimeActivityManager.h"
#include "Exception.h"

using namespace Shipping;

RealTimeActivityReactor::RealTimeActivityReactor(const std::string &_name,
                       Fwk::Activity* _activity,
                       VirtualTimeActivityManager::Ptr _vtam,
                       Fwk::Time _nextVirtualTime) :
                       Fwk::Activity::Notifiee(_name,_activity),
                       virtualTimeActivityManager_(_vtam),
                       nextVirtualTime_(_nextVirtualTime) {
}

void RealTimeActivityReactor::onStatus() {
    switch (activity_->status()) {
        case Fwk::Activity::executing: {
            virtualTimeActivityManager_->nowIs(nextVirtualTime_);
            break;
        }
        case Fwk::Activity::nextTimeScheduled:
            manager_->lastActivityIs(activity_);
            break;
        default:
            std::cerr << "RealTimeActivityReactor::onStatus out of range" << std::endl;
            throw(Fwk::RangeException("RealTimeActivityReactor::onStatus"));
    }
};

