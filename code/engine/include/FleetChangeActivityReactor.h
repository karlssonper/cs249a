#ifndef FLEETCHANGEACTIVITYREACTOR_H
#define FLEETCHANGEACTIVITYREACTOR_H

#include "Activity.h"
#include "Utils.h"
#include "VirtualTimeActivityManager.h"

namespace Shipping {

    class FleetChangeActivityReactor : public Fwk::Activity::Notifiee {
    public:
        FleetChangeActivityReactor(const string &_name, 
                                  Fwk::Ptr<VirtualTimeActivityManager> _virtualManager,
                                  Fwk::Ptr<Fwk::Activity> _activity,
                                  TimeOfDay _timeToSwap);

        void onStatus();

    protected:
        Fwk::Ptr<VirtualTimeActivityManager> virtualManager_;
        TimeOfDay _timeToSwap;
        Fwk::Ptr<Fwk::Activity> _activity;
    };
}

#endif