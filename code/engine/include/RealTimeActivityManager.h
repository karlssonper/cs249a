

#ifndef REALTIMEACTIVITYMANAGER_H
#define REALTIMEACTIVITYMANAGER_H

#include <map>
#include <string>
#include <queue>
#include "Activity.h"
#include "Nominal.h"

namespace Shipping {
    class EntityManager;
    class EngineManager;
    class VirtualTimeActivityManager;

    class TimeScale : public Ordinal<TimeScale, double> {
    public:
        TimeScale() : Ordinal<TimeScale, double>(0.f) {}
        TimeScale(double value) : Ordinal<TimeScale, double>(value) {
            if (value < 0.0)
            {
                std::cerr << "TimeScale out of range, using default value (0.0)" << std::endl;
                value = 0.0;
            }
        }
        static TimeScale max() { return std::numeric_limits<double>::max(); }
    };


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

        TimeScale timeScale() { return timeScale_; }

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
        TimeScale timeScale_;
    };
}
#endif


