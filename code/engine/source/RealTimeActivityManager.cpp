#include "RealTimeActivityManager.h"
#include "VirtualTimeActivityManager.h"
#include "Exception.h"
#include "Debug.h"
#ifdef WIN32
    #include <windows.h>
#else
    #include <time.h>
#endif

using namespace Shipping;
long unsigned int RealTimeActivityManager::idx = 0;
Fwk::Activity::Ptr RealTimeActivityManager::activityNew(const string &_name) {
    Fwk::Activity::Ptr activity = activities_[_name];
    if (activity != NULL) {
        std::cerr << "RealTimeActivityManager::activityNew already exists!" << std::endl;
        throw(Fwk::NameInUseException("RealTimeActivityManager::activityNew"));
    }
    activity = new Fwk::Activity(_name, this);
    if (!activity) {
        std::cerr << "RealTimeActivityManagerNew::activityNew new() failed" << std::endl;
        throw(Fwk::MemoryException("RealTimeActivityManager"));
    }
    activities_[_name] = activity;
    return activity;
}

RealTimeActivityManager::Ptr
RealTimeActivityManager::RealTimeActivityManagerNew(const string &_name) {
    RealTimeActivityManager::Ptr p = new RealTimeActivityManager(_name);
    if (!p) {
        std::cerr << "RealTimeActivityManagerNew new() failed" << std::endl;
        throw(Fwk::MemoryException("RealTimeActivityManager"));
    }
    return p;
}

RealTimeActivityManager::RealTimeActivityManager(const std::string &_name) :
        Fwk::Activity::Manager(_name), now_(0.0)
{

};

Fwk::Activity::Ptr RealTimeActivityManager::activity(const string &_name)const {
    std::map<std::string, Fwk::Activity::Ptr>::const_iterator it =
            activities_.find(_name);
    if(it != activities_.end() ) {
        return (*it).second;
    }
    return NULL;
    // accessor, do not throw exception
}

void RealTimeActivityManager::lastActivityIs(Fwk::Activity::Ptr _activity) {
    FWK_DEBUG("RealTimeActivityManager::lastActivityIs " << _activity->name());
    scheduledActivities_.push(_activity);
}

void RealTimeActivityManager::activityDel(const string &_name) {
    activities_.erase(_name);
}

void RealTimeActivityManager::nowIs(Fwk::Time t) {
    FWK_DEBUG("RealTimeActivityManager::nowIs " << t.value());
    while (!scheduledActivities_.empty()) {
        Fwk::Activity::Ptr nextToRun = scheduledActivities_.top();
        if (nextToRun->nextTime() > t) {
            break;
        }

        //calculate amount of time to sleep
	    Fwk::Time diff = Fwk::Time(nextToRun->nextTime().value() - now_.value());
#ifdef WIN32
	    Sleep( static_cast<int>((diff.value() * 3600000)));
#else
        usleep(static_cast<int>((diff.value() * 3600000000)));
#endif

        now_ = nextToRun->nextTime();
        scheduledActivities_.pop();
        nextToRun->statusIs(Fwk::Activity::executing);
        //nextToRun->statusIs(Fwk::Activity::free);
    }
    now_ = t;
}

void RealTimeActivityManager::scaleIs(TimeScale ts) {
    FWK_DEBUG("RealTimeActivityManager::scaleIs " << ts.value());
    if (ts != scale_)
        scale_ = ts;
};

void RealTimeActivityManager::virtualTimeActivityManagerIs(
        VirtualTimeActivityManager::Ptr _virtualTimeActMgr) {
    virtualTimeActMgr_ = _virtualTimeActMgr;
}

VirtualTimeActivityManager::Ptr
RealTimeActivityManager::virtualTimeActivityManager() {
    if (virtualTimeActMgr_) { 
        return virtualTimeActMgr_;
    } else {
        std::cerr << "RealTimeActivityManager::virtualTimeActivityManager() vtmgr not found" << std::endl;
        throw(Fwk::EntityNotFoundException("RealTimeActivityManager::virtualTimeActivityManager"));
    }
}



