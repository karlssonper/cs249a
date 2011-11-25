#include "RealTimeActivityReactor.h"
#include "VirtualTimeActivityManager.h"

using namespace Shipping;

RealTimeActivityReactor::RealTimeActivityReactor(
    const string &_name,
    RealTimeActivityManager::Ptr _realTimeActMgr,
    Fwk::Ptr<VirtualTimeActivityManager> _virtualTimeActMgr,
    Fwk::Activity::Ptr _activity,
    TimeScale _timeScale) :
Notifiee(_name, _activity.ptr()),
    realTimeActMgr_(_realTimeActMgr),
    virtualTimeActMgr_(_virtualTimeActMgr),
    activity_(_activity),
    timeScale_(_timeScale) {}

RealTimeActivityReactor::Ptr RealTimeActivityReactor::RealTimeActivityReactorNew(
    const string &_name,
    RealTimeActivityManager::Ptr _realTimeActMgr,
    Fwk::Ptr<VirtualTimeActivityManager> _virtualTimeActMgr,
    Fwk::Activity::Ptr _activity,
    TimeScale _timeScale) {
        RealTimeActivityReactor::Ptr p = new RealTimeActivityReactor(_name, _realTimeActMgr, _virtualTimeActMgr, _activity, _timeScale);
        return p;
}

void RealTimeActivityReactor::onStatus() {

    switch(activity_->status()) {

    case Fwk::Activity::executing:
        FWK_DEBUG("RealTimeAct " << name() << " executing");
       virtualTimeActMgr_->nowIs(realTimeActMgr_->now());
    case Fwk::Activity::free:
        FWK_DEBUG("RealTimeAct " << name() << " free");
        // remove from reactor list
        break;
    case Fwk::Activity::nextTimeScheduled:
        FWK_DEBUG("RealTimeAct " << name() << " adding itself to be scheduled");
        realTimeActMgr_->lastActivityIs(activity_);
        break;
    default:
        break;
    }

}