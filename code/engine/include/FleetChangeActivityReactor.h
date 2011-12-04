#ifndef FLEETCHANGEACTIVITYREACTOR_H
#define FLEETCHANGEACTIVITYREACTOR_H

#include "Activity.h"
#include "Utils.h"
#include "VirtualTimeActivityManager.h"


namespace Shipping {
    class Fleet;
    class FleetChangeActivityReactor : public Fwk::Activity::Notifiee {
    public:
        FleetChangeActivityReactor(const string &_name, 
                                  Fwk::Ptr<VirtualTimeActivityManager> _virtualManager,
                                  Fwk::Ptr<Fwk::Activity> _activity,
                                  Fleet* _fleet,
                                  TimeOfDay _timeToSwap);

        void onStatus();

        void timeToSwapIs(TimeOfDay _timeToSwap) {
            if (_timeToSwap == timeToSwap_) return;
            timeToSwap_ == _timeToSwap;
        }

    protected:
        Fleet* fleet_;
        Fwk::Ptr<VirtualTimeActivityManager> virtualManager_;
        TimeOfDay timeToSwap_;
        Fwk::Ptr<Fwk::Activity> activity_;
    };
}

#endif