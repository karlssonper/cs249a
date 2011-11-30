#include "RealTimeActivityManager.h"
#include "VirtualTimeActivityManager.h"

using namespace Shipping;
Fwk::Activity::Ptr RealTimeActivityManager::activityNew(const string &_name) {
    Fwk::Activity::Ptr activity = activities_[_name];
    if (activity != NULL) {
        std::cerr << "Activity already exists!" << std::endl;
        return NULL;
    }
    activity = new Fwk::Activity(_name, this);
    activities_[_name] = activity;
    return activity;
}

RealTimeActivityManager::Ptr
RealTimeActivityManager::RealTimeActivityManagerNew(const string &_name) {
    RealTimeActivityManager::Ptr p = new RealTimeActivityManager(_name);
    return p;
}

RealTimeActivityManager::RealTimeActivityManager(const std::string &_name) :
        Fwk::Activity::Manager(_name), now_(0.0)
{

};

Fwk::Activity::Ptr RealTimeActivityManager::activity(const string &_name) const {
    std::map<std::string, Fwk::Activity::Ptr>::const_iterator it = activities_.find(_name);
    if(it != activities_.end() ) {
        return (*it).second;
    }
    return NULL;
}

void RealTimeActivityManager::lastActivityIs(Fwk::Activity::Ptr _activity) {
    //scheduledActivities_.push(_activity);

    //CREATE ACTIVITY AND REAL TIME ACTIVITY REACTOR
    //QUEUE
}

void RealTimeActivityManager::activityDel(const string &_name) {
    activities_.erase(_name);
}

void RealTimeActivityManager::nowIs(Fwk::Time t) {
    while (!scheduledActivities_.empty()) {
        Fwk::Activity::Ptr nextToRun = scheduledActivities_.top();
        if (nextToRun->nextTime() > t) {
            break;
        }
        now_ = nextToRun->nextTime();
        scheduledActivities_.pop();
        nextToRun->statusIs(Fwk::Activity::executing);
        nextToRun->statusIs(Fwk::Activity::free);
    }
    now_ = t;
}

void RealTimeActivityManager::virtualTimeActivityManagerIs(
        VirtualTimeActivityManager::Ptr _virtualTimeActMgr) {
    virtualTimeActMgr_ = _virtualTimeActMgr;
}

VirtualTimeActivityManager::Ptr RealTimeActivityManager::virtualTimeActivityManager() {
    if (virtualTimeActMgr_) return virtualTimeActMgr_;
}



