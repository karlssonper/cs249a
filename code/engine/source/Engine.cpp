#include "Engine.h"
#include "Debug.h"
#include "Exception.h"

using namespace Shipping;

EngineManager::Ptr EngineManager::EngineManagerNew(std::string name) {
    Ptr p = new EngineManager(name);
    if (!p) {
        std::cerr << "EngineManager::EngineManagerNew new() failed" << std::endl;
        throw(Fwk::MemoryException("EngineManager::EngineManagerNew"));
    }
    return p;
}

EngineManager::EngineManager(const std::string &_name) :
Fwk::NamedInterface(_name)
{
    FWK_DEBUG("EngineManager::EngineManager constructor with name: " << _name);

    entityManager_ =
        EntityManager::EntityManagerNew(std::string("EntityManager"));
    stats_ = Stats::StatsNew(std::string("Stats"), this, entityManager_.ptr());
    conn_ = Conn::ConnNew(std::string("Conn"), this, entityManager_.ptr());
    virtualTimeActivityManager_ =
        VirtualTimeActivityManager::VirtualTimeActivityManagerNew(
        std::string("VirtualTimeActivityManager")
        );
    realTimeActivityManager_ =
        RealTimeActivityManager::RealTimeActivityManagerNew(
        std::string("RealTimeActivityManager")
        );
    virtualTimeActivityManager_->realTimeActivityManagerIs(realTimeActivityManager_);
    realTimeActivityManager_->virtualTimeActivityManagerIs(virtualTimeActivityManager_);
    fleet_ = Fleet::FleetNew(std::string("Fleet"), virtualTimeActivityManager_);
};

void EngineManager::connIs(const std::string &_name) {
    FWK_DEBUG("EngineManager::connIs with name" << _name);

};

void EngineManager::fleetIs(const std::string &_name){
    FWK_DEBUG("EngineManager::fleetIs with name" << _name);

};

void EngineManager::statsIs(const std::string &_name){
    FWK_DEBUG("EngineManager::statsIs with name" << _name);

};

EngineManager::~EngineManager() {
    FWK_DEBUG("EngineManager::~EngineManager with name: " << name());
};
