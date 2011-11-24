#include "VirtualTimeActivityManager.h"

Fwk::Activity::Ptr Shipping::VirtualTimeActivityManager::activityNew(const string &_name) {
    Fwk::Activity::Ptr activity = activities_[_name];
    if (activity != NULL) {
        std::cerr << "Activity already exists!" << std::endl;
        return NULL;
    }
    activity = new Fwk::Activity(_name, this);
    activities_[_name] = activity;
    return activity;
}

Fwk::Activity::Ptr Shipping::VirtualTimeActivityManager::activity(const string &_name) const {
    std::map<std::string, Fwk::Activity::Ptr>::const_iterator it = activities_.find(_name);
    if(it != activities_.end() ) {
        return (*it).second;
    }
    return NULL; 
}

void Shipping::VirtualTimeActivityManager::activityDel(const string &_name) {
    activities_.erase(_name);
}

void Shipping::VirtualTimeActivityManager::lastActivityIs(Fwk::Activity::Ptr _activity) {
    scheduledActivities_.push(_activity);
}

void Shipping::VirtualTimeActivityManager::nowIs(Fwk::Time t) {
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

Shipping::VirtualTimeActivityManager::VirtualTimeActivityManager(const std::string &_name,
                                                                 EntityManager *_entityManager,
                                                                 EngineManager *_engineManager) :
                                                                 Fwk::Activity::Manager(_name),
                                                                 entityManager_(_entityManager),
                                                                 engineManager_(_engineManager) {}

Shipping::VirtualTimeActivityManager::Ptr Shipping::VirtualTimeActivityManager::VirtualTimeActivityManagerNew(const std::string &_name,
                                                                                                              EntityManager *_entityManager,
                                                                                                              EngineManager *_engineManager) {
    Shipping::VirtualTimeActivityManager::Ptr p = new Shipping::VirtualTimeActivityManager(_name, _entityManager, _engineManager);
    return p;
}



