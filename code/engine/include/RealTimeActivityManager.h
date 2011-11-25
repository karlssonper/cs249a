#ifndef REALTIMEACTIVITYMANAGER_H
#define REALTIMEACTIVITYMANAGER_H

#include <string>
#include <queue>
#include "Activity.h"

namespace Shipping {
    class EntityManager;
    class EngineManager;
    class VirtualTimeActivityManager;
    class RealTimeActivityManager : public Fwk::Activity::Manager {

    public:
        typedef Fwk::Ptr<RealTimeActivityManager> Ptr;
        typedef Fwk::Ptr<RealTimeActivityManager const> PtrConst;
        virtual Fwk::Time endTime() const { return endTime_; }
        virtual void endTimeIs(Fwk::Time time);
        

        static Ptr RealTimeActivityManagerNew(const string &_name,
                                              EntityManager *_entityManager,
                                              EngineManager *_engineManager);

        virtual void activityIs(Fwk::Activity::Ptr activity);

        void virtualTimeActivityManagerIs(Fwk::Ptr<VirtualTimeActivityManager>);
        Fwk::Ptr<VirtualTimeActivityManager> virtualTimeActivityManager();

    protected:
        RealTimeActivityManager(const std::string &_name,
                                EntityManager *_entityManager,
                                EngineManager *_engineManager);

        Fwk::Activity::Ptr activity_; 
        Fwk::Time endTime_;
        EngineManager *engineManager_;
        EntityManager *entityManager_;
        Fwk::Ptr<VirtualTimeActivityManager> virtualTimeActMgr_;
    };
}
#endif
/*
#include <map>
#include <string>
#include <queue>
#include "Activity.h"

namespace Shipping {
    class EntityManager;
    class EngineManager;
    class VirtualTimeActivityManager;
    class RealTimeActivityManager : public Fwk::Activity::Manager {

    public:
        typedef Fwk::Ptr<RealTimeActivityManager> Ptr;
        typedef Fwk::Ptr<RealTimeActivityManager const> PtrConst;
        virtual Fwk::Activity::Ptr activityNew(const string& name);
        virtual Fwk::Activity::Ptr activity(const string& name) const;
        virtual void activityDel(const string& name);
        virtual Fwk::Time now() const { return now_; }
        virtual void nowIs(Fwk::Time time);
        

        static Ptr RealTimeActivityManagerNew(const string &_name,
                                              EntityManager *_entityManager,
                                              EngineManager *_engineManager);

        virtual void lastActivityIs(Fwk::Activity::Ptr activity);

        void virtualTimeActivityManagerIs(Fwk::Ptr<VirtualTimeActivityManager>);
        Fwk::Ptr<VirtualTimeActivityManager> virtualTimeActivityManager();

    protected:
        RealTimeActivityManager(const std::string &_name,
                                EntityManager *_entityManager,
                                EngineManager *_engineManager);

        std::priority_queue<Fwk::Activity::Ptr, std::vector<Fwk::Activity::Ptr>, Fwk::Activity::Comp> scheduledActivities_;
        std::map<std::string, Fwk::Activity::Ptr> activities_; 
        Fwk::Time now_;
        EngineManager *engineManager_;
        EntityManager *entityManager_;
        Fwk::Ptr<VirtualTimeActivityManager> virtualTimeActMgr_;
    };
}

*/
#endif


