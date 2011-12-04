#include "FleetReactor.h"
#include "VirtualTimeActivityManager.h"
#include "Activity.h"
#include "FleetChangeActivityReactor.h"

using namespace Shipping;

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
                reactor1_ = new FleetChangeActivityReactor(tempName,
                                                           activityManager_,
                                                           activity1_,
                                                           notifier()->bufferStart());
                tempName = name();
                tempName.append("Swapper2Reactor");
                reactor2_ = new FleetChangeActivityReactor(tempName,
                                                           activityManager_,
                                                           activity2_,
                                                           notifier()->bufferEnd());


            } 
        }
    
    }
     catch(Fwk::Exception e) {
        std::cerr << "Exception in FleetReactor::onTimeChange: " << e.what() << std::endl;
        onNotificationException();
    }
}