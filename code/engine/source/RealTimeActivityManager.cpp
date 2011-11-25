#include "RealTimeActivityManager.h"
#include "VirtualTimeActivityManager.h"

using namespace Shipping;


void RealTimeActivityManager::activityIs(Fwk::Activity::Ptr _activity) {
    activity_ = _activity;
}

void RealTimeActivityManager::endTimeIs(Fwk::Time t) {
    while (activity_) {
        Fwk::Activity::Ptr nextInLine
        if (nextToRun->nextTime() > t) {
            break;
        }
        Fwk::Time diff = Fwk::Time(nextToRun->nextTime().value() - now_.value());
        now_ = nextToRun->nextTime();
        scheduledActivities_.pop();
        nextToRun->statusIs(Fwk::Activity::executing);
        nextToRun->statusIs(Fwk::Activity::free);
    }
    now_ = t;
}

RealTimeActivityManager::RealTimeActivityManager(
        const std::string &_name,
        EntityManager *_entityManager,
        EngineManager *_engineManager) :
        Fwk::Activity::Manager(_name),
        entityManager_(_entityManager),
        engineManager_(_engineManager), now_(0.0) {}

Shipping::RealTimeActivityManager::Ptr
Shipping::RealTimeActivityManager::RealTimeActivityManagerNew(const std::string &_name,
        EntityManager *_entityManager,
        EngineManager *_engineManager) {
    RealTimeActivityManager::Ptr p = new RealTimeActivityManager(
            _name, _entityManager, _engineManager);
    return p;
}

void Shipping::RealTimeActivityManager::virtualTimeActivityManagerIs(Fwk::Ptr<VirtualTimeActivityManager> _virtualTimeActMgr) {
    virtualTimeActMgr_ = _virtualTimeActMgr;
}

Fwk::Ptr<VirtualTimeActivityManager> RealTimeActivityManager::virtualTimeActivityManager() 
{
    if (virtualTimeActMgr_) return virtualTimeActMgr_;
}







