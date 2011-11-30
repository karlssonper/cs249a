#ifndef REALTIMEACTIVITYMANAGER_H
#define REALTIMEACTIVITYMANAGER_H

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
        
        static Ptr RealTimeActivityManagerNew(const string &_name);

        virtual Fwk::Activity::Ptr activityNew(const string& name);
        virtual Fwk::Activity::Ptr activity(const string& name) const;
        virtual void activityDel(const string& name);
        virtual Fwk::Time now() const { return now_; }
        virtual void nowIs(Fwk::Time time);
        virtual void lastActivityIs(Fwk::Activity::Ptr activity);
        void virtualTimeActivityManagerIs(Fwk::Ptr<VirtualTimeActivityManager>);
        Fwk::Ptr<VirtualTimeActivityManager> virtualTimeActivityManager();

    protected:
        RealTimeActivityManager(const std::string &_name);
        RealTimeActivityManager();
        RealTimeActivityManager(const RealTimeActivityManager &);

        std::priority_queue<Fwk::Activity::Ptr,
                            std::vector<Fwk::Activity::Ptr>,
                            Fwk::Activity::Comp> scheduledActivities_;
        std::map<std::string, Fwk::Activity::Ptr> activities_;
        Fwk::Time now_;
        Fwk::Ptr<VirtualTimeActivityManager> virtualTimeActMgr_;
    };
}
#endif


