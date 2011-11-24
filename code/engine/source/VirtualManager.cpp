#include "VirtualManager.h"

Activity::Ptr Shipping::VirtualManager::activityNew(const string &_name) {
    Activity::Ptr activity = activities_[_name];
    if (activity != NULL) {
        cerr << "Activity already exists!" << endl;
        return NULL;
    }
    activity = new Activity(_name, this);
    activities_[_name] = activity;
    return activity;
}

Activity::Ptr Shipping::VirtualManager::activity(const string &_name) const {
    map<string, Activity::Ptr>::const_iterator it = activities_.find(_name);
    if(it != activities_.end() ) {
        return (*it).second;
    }
    return NULL; 
}

void Shipping::VirtualManager::activityDel(const string &_name) {
    activities_.erase(_name);
}

void Shipping::VirtualManager::lastActivityIs(Activity::Ptr _activity) {
    scheduledActivities_.push(_activity);
}

void Shipping::VirtualManager::nowIs(Time t) {
    while (!scheduledActivities_.empty()) {
        Activity::Ptr nextToRun = scheduledActivities_.top();
        if (nextToRun->nextTime() > t) {
            break;
        }
        Time diff = Time(nextToRun->nextTime().value() - now_.value());
        now_ = nextToRun->nextTime();
        scheduledActivities_.pop();
        nextToRun->statusIs(Activity::executing);
        nextToRun->statusIs(Activity::free);
    }

    now_ = t;
}

