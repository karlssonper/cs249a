#ifndef REALTIMEACTIVITYREACTOR_H
#define REALTIMEACTIVITYREACTOR_H

#include "Activity.h"
#include "RealTimeActivityManager.h"

namespace Shipping {
class VirtualTimeActivityManager;

class RealTimeActivityReactor : public Fwk::Activity::Notifiee {
public:
    typedef Fwk::Ptr<RealTimeActivityReactor> Ptr;
    typedef Fwk::Ptr<RealTimeActivityReactor const> PtrConst;

    static Ptr RealTimeActivityReactorNew(const string &_name,
                            RealTimeActivityManager::Ptr _realTimeActMgr,
                            Fwk::Ptr<VirtualTimeActivityManager> _virtualTimeActMgr,
                            Fwk::Activity::Ptr _activity,
                            TimeScale _timeScale);

    virtual void onStatus();
   
protected:
    RealTimeActivityReactor();
    RealTimeActivityReactor(const RealTimeActivityReactor&);
    RealTimeActivityReactor(const string &_name,
                            RealTimeActivityManager::Ptr _realTimeActMgr,
                            Fwk::Ptr<VirtualTimeActivityManager> _virtualTimeActMgr,
                            Fwk::Activity::Ptr _activity,
                            TimeScale _timeScale);
    Fwk::Activity::Ptr activity_;
    RealTimeActivityManager::Ptr realTimeActMgr_;
    Fwk::Ptr<VirtualTimeActivityManager> virtualTimeActMgr_;
    TimeScale timeScale_;

};

}

#endif