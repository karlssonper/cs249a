#include "VirtualTimeActivityManager.h"
#include "RealTimeActivityManager.h"
#include "RealTimeActivityReactor.h"
#include <ostream>
#include <sstream>

using namespace Shipping;
Fwk::Activity::Ptr VirtualTimeActivityManager::activityNew(const string &_name) {
    Fwk::Activity::Ptr activity = activities_[_name];
    if (activity != NULL) {
        std::cerr << "Activity already exists!" << std::endl;
        return NULL;
    }
    activity = new Fwk::Activity(_name, this);
    activities_[_name] = activity;
    return activity;
}

Fwk::Activity::Ptr VirtualTimeActivityManager::activity(const string &_name) const {
    std::map<std::string, Fwk::Activity::Ptr>::const_iterator it = activities_.find(_name);
    if(it != activities_.end() ) {
        return (*it).second;
    }
    return NULL; 
}

void VirtualTimeActivityManager::activityDel(const string &_name) {
    activities_.erase(_name);
}

void VirtualTimeActivityManager::lastActivityIs(Fwk::Activity::Ptr _activity) {
    scheduledActivities_.push(_activity);

    std::ostringstream s;
    s << runningIndex_;
 

    FWK_DEBUG("VTAM making a clone in " << realTimeActMgr_->name());

    string activityName = "realTimeAct";
    string reactorName = "realTimeReactor";

    activityName.append(s.str());
    reactorName.append(s.str());

    runningIndex_++;

    // create a 'clone' activity with the same time in real time mgr
    Fwk::Activity::Ptr realTimeAct = realTimeActMgr_->activityNew(activityName);

    FWK_DEBUG("VTAM setting nextTimeIs for the cloned activity");
    realTimeAct->nextTimeIs(_activity->nextTime());

    FWK_DEBUG("VTAM creating a reactor");

    // create a reactor (unique to this cloned activity)
    RealTimeActivityReactor::Ptr realTimeReact = RealTimeActivityReactor::RealTimeActivityReactorNew(reactorName,
                                                                                                     realTimeActMgr_,
                                                                                                     this,
                                                                                                     realTimeAct,
                                                                                                     realTimeActMgr_->timeScale());
    realTimeActReactors_[reactorName] = realTimeReact;
    

    FWK_DEBUG("VTAM scheduling the real time activity");

    // schedule the real time activity
    realTimeAct->statusIs(Fwk::Activity::nextTimeScheduled);
}

void VirtualTimeActivityManager::nowIs(Fwk::Time t) {

    FWK_DEBUG("VTAM nowIs " << t.value());

    while (!scheduledActivities_.empty()) {
        Fwk::Activity::Ptr nextToRun = scheduledActivities_.top();
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

VirtualTimeActivityManager::VirtualTimeActivityManager(
        const std::string &_name,
        EntityManager *_entityManager,
        EngineManager *_engineManager) :
        Fwk::Activity::Manager(_name),
        entityManager_(_entityManager),
        engineManager_(_engineManager), 
        now_(0.0),
        runningIndex_(0) {}

Shipping::VirtualTimeActivityManager::Ptr
Shipping::VirtualTimeActivityManager::VirtualTimeActivityManagerNew(const std::string &_name,
        EntityManager *_entityManager,
        EngineManager *_engineManager) {
    VirtualTimeActivityManager::Ptr p = new VirtualTimeActivityManager(
            _name, _entityManager, _engineManager);
    return p;
}

void Shipping::VirtualTimeActivityManager::realTimeActivityManagerIs(Fwk::Ptr<RealTimeActivityManager> _realTimeActMgr) {
    realTimeActMgr_ = _realTimeActMgr;
}

Fwk::Ptr<RealTimeActivityManager> Shipping::VirtualTimeActivityManager::realTimeActivityManager() {
    if (realTimeActMgr_) return realTimeActMgr_;
}







