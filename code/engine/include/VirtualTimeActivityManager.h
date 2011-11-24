#ifndef VIRTUALTIMEACTIVITYMANAGER_H
#define VIRTUALTIMEACTIVITYMANAGER_H

#include <map>
#include <string>
#include "Activity.h"

namespace Shipping {

    class VirtualTimeActivityManager : public Fwk::Activity::Manager {

    public:
        typedef Fwk::Ptr<VirtualTimeActivityManager> Ptr;
        virtual Fwk::Activity::Ptr activityNew(const string& name);
        virtual Fwk::Activity::Ptr activity(const string& name) const;
        virtual void activityDel(const string& name);
        virtual Fwk::Time now() const { return now_; }
        virtual void nowIs(Fwk::Time time);

        static Ptr VirtualTimeActivityManagerNew(const string &_name,
                                                 EntityManager *_entityManager,
                                                 EngineManager *_engineManager);

        virtual void lastActivityIs(Fwk::Activity::Ptr activity);

    protected:
        VirtualTimeActivityManager(const std::string &_name,
                                   EntityManager *_entityManager,
                                   EngineManager *_engineManager);

        priority_queue<Fwk::Activity::Ptr, vector<Fwk::Activity::Ptr>, Fwk::ActivityComp> scheduledActivities_;
        std::map<std::string, Fwk::Activity::Ptr> activities_; 
        Fwk::Time now_;
        EngineManager *engineManager_;
        EntityManager *entityManager_;
    };
}
#endif
