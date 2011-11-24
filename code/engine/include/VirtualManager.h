#ifndef VIRTUALMANAGER_H
#define VIRTUALMANAGER_H

#include "Activity.h"

namespace Shipping {

    class VirtualManager : public Activity::Manager {

    public:
        typedef Fwk::Ptr<VirtualManager> Ptr;
        virtual Activity::Ptr activityNew(const string& name);
        virtual Activity::Ptr activity(const string& name) const;
        virtual void activityDel(const string& name);
        virtual Time now() const { return now_; }
        virtual void nowIs(Time time);

        static Ptr VirtualManagerNew(const string &_name,
            EntityManager *_entityManager,
            EngineManager *_engineManager);

        virtual void lastActivityIs(Activity::Ptr activity);

    protected:
        VirtualManager(const string &_name,
            EntityManager *_entityManager,
            EngineManager *_engineManager);

        priority_queue<Activity::Ptr, vector<Activity::Ptr>, ActivityComp> scheduledActivities_;
        map<string, Activity::Ptr> activities_; 
        Time now_;
        EngineManager *engineManager_;
        EntityManager *entityManager_;
    };
}
#endif
