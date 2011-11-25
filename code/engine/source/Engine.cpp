/*
 * Engine.cpp
 *
 *  Created on: Nov 4, 2011
 *      Author: per
 */

#include "Engine.h"
#include "Debug.h"
using namespace Shipping;

EngineManager::EngineManager(const std::string &_name) :
        Fwk::NamedInterface(_name)
{
    FWK_DEBUG("EngineManager::EngineManager constructor with name: " << _name);

    fleet_ = Fleet::FleetNew(std::string("Fleet"));
    entityManager_ =
            EntityManager::EntityManagerNew(std::string("EntityManager"));
    stats_ = Stats::StatsNew(std::string("Stats"), this, entityManager_.ptr());
    conn_ = Conn::ConnNew(std::string("Conn"), this, entityManager_.ptr());
    virtualTimeActivityManager_ =
            VirtualTimeActivityManager::VirtualTimeActivityManagerNew(
                    std::string("VirtualTimeActivityManager"),
                    entityManager_.ptr(),
                    this
                    );
    realTimeActivityManager_ =
        RealTimeActivityManager::RealTimeActivityManagerNew(
        std::string("RealTimeActivityManager"),
        entityManager_.ptr(),
        this
        );

    realTimeActivityManager_->virtualTimeActivityManagerIs(virtualTimeActivityManager_);
    virtualTimeActivityManager_->realTimeActivityManagerIs(realTimeActivityManager_);
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
