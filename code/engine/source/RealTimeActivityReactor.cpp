/*
 * RealTimeActivityReactor.cpp
 *
 *  Created on: Nov 24, 2011
 *      Author: per
 */

#include "RealTimeActivityReactor.h"
#include "VirtualTimeActivityManager.h"
#include "RealTimeActivityManager.h"
#include "Exception.h"
#include "Output.h"

using namespace Shipping;

RealTimeActivityReactor::RealTimeActivityReactor(const std::string &_name,
                       Fwk::Activity* _activity,
                       VirtualTimeActivityManager::Ptr _vtam,
                       RealTimeActivityManager::Ptr _rtam,
                       Fwk::Time _nextVirtualTime) :
                       Fwk::Activity::Notifiee(_name,_activity),
                       activity_(_activity),
                       manager_(_rtam),
                       virtualTimeActivityManager_(_vtam),
                       nextVirtualTime_(_nextVirtualTime) {
}

void RealTimeActivityReactor::onStatus() {
    switch (activity_->status()) {
        case Fwk::Activity::executing: {
            FWK_DEBUG("RealTImeActivityReactor executing");
            virtualTimeActivityManager_->nowIs(nextVirtualTime_);
            break;
        }
        case Fwk::Activity::nextTimeScheduled:
            manager_->lastActivityIs(activity_);
            break;
        default:
            std::cerr << 
                "RealTimeActivityReactor::onStatus out of range" << std::endl;
            throw(Fwk::RangeException("RealTimeActivityReactor::onStatus"));
    }
};

