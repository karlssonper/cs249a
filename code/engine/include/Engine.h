#ifndef ENGINE_H
#define ENGINE_H

#include "NamedInterface.h"
#include "Ptr.h"
#include "Conn.h"
#include "Fleet.h"
#include "Stats.h"
#include "EntityManager.h"
#include <string>
#include "VirtualTimeActivityManager.h"
#include "RealTimeActivityManager.h"

namespace Shipping {
    class EngineManager : public Fwk::NamedInterface {
    public:
        typedef Fwk::Ptr<EngineManager const> PtrConst;
        typedef Fwk::Ptr<EngineManager> Ptr;

        Conn::Ptr conn() const { return conn_;};
        void connIs(const std::string &name);
        Fleet::Ptr fleet() const { return fleet_;};
        void fleetIs(const std::string &name);
        Stats::Ptr stats() const { return stats_;};
        void statsIs(const std::string &name);
        EntityManager::Ptr entityManager() const {return entityManager_;};
        VirtualTimeActivityManager::Ptr virtualTimeActivityManager() const { 
            return virtualTimeActivityManager_; }
        RealTimeActivityManager::Ptr realTimeActivityManager() const { 
            return realTimeActivityManager_; }
        ~EngineManager();

        static EngineManager::Ptr EngineManagerNew(std::string name);

    private:
        EngineManager();
        EngineManager(const std::string &name);
        EngineManager(const EngineManager &);
        Conn::Ptr conn_;
        Fleet::Ptr fleet_;
        Stats::Ptr stats_;
        Fwk::Ptr<EntityManager> entityManager_;
        Fwk::Ptr<VirtualTimeActivityManager> virtualTimeActivityManager_;
        Fwk::Ptr<RealTimeActivityManager> realTimeActivityManager_;
    };

};//end namespace
#endif
