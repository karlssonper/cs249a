#ifndef VIRTUALTIMEACTIVITYMANAGER_H
#define VIRTUALTIMEACTIVITYMANAGER_H

#include <map>
#include <string>
#include <queue>
#include "Activity.h"

namespace Shipping {
    class EntityManager;
    class EngineManager;
    class RealTimeActivityManager;
    class VirtualTimeActivityManager : public Fwk::Activity::Manager {

    public:
        typedef Fwk::Ptr<VirtualTimeActivityManager> Ptr;
        typedef Fwk::Ptr<VirtualTimeActivityManager const> PtrConst;
        virtual Fwk::Activity::Ptr activityNew(const string& name);
        virtual Fwk::Activity::Ptr activity(const string& name) const;
        virtual void activityDel(const string& name);
        virtual Fwk::Time now() const { return now_; }
        virtual void nowIs(Fwk::Time time);
        Fwk::Time simluationEnd() const { return simulationEnd_; };
        virtual void simluationEndIs(Fwk::Time _time);

        static Ptr VirtualTimeActivityManagerNew(const string &_name,
                                                 EntityManager *_entityManager,
                                                 EngineManager *_engineManager);

        virtual void lastActivityIs(Fwk::Activity::Ptr activity);

        void realTimeActivityManagerIs(Fwk::Ptr<RealTimeActivityManager>);
        Fwk::Ptr<RealTimeActivityManager> realTimeActivityManager();

    protected:
        VirtualTimeActivityManager(const std::string &_name,
                                   EntityManager *_entityManager,
                                   EngineManager *_engineManager);

        std::priority_queue<Fwk::Activity::Ptr, std::vector<Fwk::Activity::Ptr>, Fwk::Activity::Comp> scheduledActivities_;
        std::map<std::string, Fwk::Activity::Ptr> activities_; 
        Fwk::Time now_;
        Fwk::Time simulationEnd_;
        EngineManager *engineManager_;
        EntityManager *entityManager_;
        Fwk::Ptr<RealTimeActivityManager> realTimeActMgr_;
    };
}
#endif
