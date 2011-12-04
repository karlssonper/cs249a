#ifndef FLEETREACTOR_H
#define FLEETREACTOR_H

#include "Ptr.h"
#include "Fleet.h"

namespace Fwk { class Activity; }

namespace Shipping {

    class VirtualTimeActivityManager;
    class FleetChangeActivityReactor;

    class FleetReactor : public Fleet::Notifiee {
    public:
        typedef Fwk::Ptr<FleetReactor const> PtrConst;
        typedef Fwk::Ptr<FleetReactor> Ptr;

        enum Status {
            notActive_, active_
        };

        static Status notActive() { return notActive_; }
        static Status active() { return active_; }

        static Ptr FleetReactorNew(const string &_name, 
                                   Fleet *_notifier,
                                   Fwk::Ptr<VirtualTimeActivityManager> _vtam);
        ~FleetReactor() {}

        virtual void onTimeChange();
        
    protected:
        Status status_;
        FleetReactor(const string &_name,
                     Fleet *_notifier,
                     Fwk::Ptr<VirtualTimeActivityManager> _vtam);
        FleetReactor();
        FleetReactor(const FleetReactor&);
        Fwk::Ptr<Fwk::Activity> activity1_;
        Fwk::Ptr<Fwk::Activity> activity2_;
        Fwk::Ptr<VirtualTimeActivityManager> activityManager_;
        FleetChangeActivityReactor *reactor1_;
        FleetChangeActivityReactor *reactor2_;
    };

}

#endif