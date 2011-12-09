#include "FleetReactor.h"
#include "VirtualTimeActivityManager.h"
#include "Activity.h"
#include "FleetChangeActivityReactor.h"
#include "Exception.h"

using namespace Shipping;

FleetReactor::FleetReactor(const string &_name, 
                           Fleet *_notifier,
                           VirtualTimeActivityManager::Ptr _vtam) :
                           Fleet::Notifiee(_name, _notifier),
                           activityManager_(_vtam),
                           status_(notActive()),
                           activity1_(NULL),
                           activity2_(NULL) {
reactor1_ = new FleetChangeActivityReactor(
                                   "FleetChangeActReactor1",
                                   activityManager_,
                                   NULL,
                                   notifier(),
                                   notifier()->bufferStart());
reactor2_ = new FleetChangeActivityReactor(
                                   "FleetChangeReactor2",
                                   activityManager_,
                                   NULL,
                                   notifier(),
                                   notifier()->bufferStart());

}

FleetReactor::Ptr FleetReactor::FleetReactorNew(const string &_name, 
                                   Fleet *_notifier,
                                   Fwk::Ptr<VirtualTimeActivityManager> _vtam) {
    FleetReactor::Ptr p = new FleetReactor(_name, _notifier, _vtam);
    if (!p) {
        std::cerr << "FleetReactorNew new () failed" << std::endl;
        throw(Fwk::MemoryException("FleetReactorNew"));
    }
    return p;
}

void FleetReactor::onTimeChange() {
    try {
        if (status_ == notActive()) {
            if (notifier()->bufferStart() != notifier()->bufferEnd()) {
                status_ = active();
                string tempName = name();
                tempName.append("Swapper1");
                if (!activity1_) {
                    activity1_ = activityManager_->activityNew(tempName);
                }
                tempName = name();
                tempName.append("Swapper2");
                if (!activity2_) {
                    activity2_ = activityManager_->activityNew(tempName);
                }
                tempName = name();
                tempName.append("Swapper1Reactor");
                reactor1_->activityIs(activity1_);
                activity1_->nextTimeIs(Fwk::Time(
                    notifier()->bufferStart().value()));
                activity1_->notifieeIs(tempName, reactor1_);
                activity1_->statusIs(Fwk::Activity::nextTimeScheduled);
                tempName = name();
                tempName.append("Swapper2Reactor");
                reactor2_->activityIs(activity2_);
                activity2_->nextTimeIs(Fwk::Time
                    (notifier()->bufferEnd().value()));
                activity2_->notifieeIs(tempName, reactor2_);
                activity2_->statusIs(Fwk::Activity::nextTimeScheduled);
            } 
        } else /*active*/ {
            if (notifier()->bufferStart() != notifier()->bufferEnd()) {

               activity1_->nextTimeIs(notifier()->bufferStart().value());
               reactor1_->timeToSwapIs(notifier()->bufferStart());
          
               reactor2_->timeToSwapIs(notifier()->bufferEnd());
               activity2_->nextTimeIs(notifier()->bufferEnd().value());

            } else {
                // deactivate
                status_ = notActive();
                activity1_->notifieeIs("",0);
                activityManager_->activityDel(activity1_->name());
                activity1_ = NULL;
                reactor1_ = NULL;
                activity2_->notifieeIs("",0);
                activityManager_->activityDel(activity2_->name());
                activity2_ = NULL;
                reactor2_ = NULL;


            }
        }

    } // try

    catch(Fwk::Exception e) {
        std::cerr << "Exception in FleetReactor::onTimeChange: " <<
            e.what() << std::endl;
        onNotificationException();
    }
}