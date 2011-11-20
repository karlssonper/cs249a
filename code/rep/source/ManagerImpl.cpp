#include "ManagerImpl.h"
#include "Engine.h"
#include "LocationRep.h"
#include "StatsRep.h"
#include "ConnRep.h"
#include "FleetRep.h"
#include "SegmentRep.h"
#include "Debug.h"

using namespace Shipping;

ManagerImpl::ManagerImpl(string _name) :
engineManager_(EngineManager::EngineManagerNew(_name)),
    stats_(NULL), fleet_(NULL), conn_(NULL){
        FWK_DEBUG("ManagerImpl constructor with name " << _name);
};

ManagerImpl::~ManagerImpl() {
    FWK_DEBUG("~ManagerImpl::ManagerImpl()");
}

Ptr<Instance> ManagerImpl::instanceNew(const string& _name, const string& _type) {

    FWK_DEBUG("ManagerImpl::instanceNew(" << _name << ", " << _type << ")");

    if (instance_.find(_name) != instance_.end()) {
        cerr << "ManagerImpl::instanceNew: " << _name << " already exists, returning NULL" << endl;
        return NULL;
    }

    if (_type == "Customer") {
        Ptr<CustomerRep> p = new CustomerRep(_name, engineManager_);
        instance_[_name] = p;
        return p;
    } else if (_type == "Port") {
        Ptr<PortRep> p = new PortRep(_name, engineManager_);
        instance_[_name] = p;
        return p;
    } else if (_type == "Truck terminal") {
        Ptr<TruckTerminalRep> p = new TruckTerminalRep(_name, engineManager_);
        instance_[_name] = p;
        return p;       
    } else if (_type == "Boat terminal") {
        Ptr<BoatTerminalRep> p = new BoatTerminalRep(_name, engineManager_);
        instance_[_name] = p;
        return p;
    } else if (_type == "Plane terminal") {
        Ptr<PlaneTerminalRep> p = new PlaneTerminalRep(_name, engineManager_);
        instance_[_name] = p;
        return p;
    } else if (_type == "Truck segment" ){
        Ptr<TruckSegmentRep> p = new TruckSegmentRep(_name, engineManager_);
        instance_[_name] = p;
        return p;
    } else if (_type == "Boat segment") {
        Ptr<BoatSegmentRep> p = new BoatSegmentRep(_name, engineManager_);
        instance_[_name] = p;
        return p;
    } else if (_type == "Plane segment" ){
        Ptr<PlaneSegmentRep> p = new PlaneSegmentRep(_name, engineManager_);
        instance_[_name] = p;
        return p;
    } else if (_type == "Stats") {
        if (stats_) {
            return Ptr<StatsRep>(stats_);
        } else {
            Ptr<StatsRep> p = new StatsRep(_name, engineManager_);
            instance_[_name] = p;
            return p;
        }
    }  else if (_type == "Conn") {
        if (conn_) {
            return Ptr<ConnRep>(conn_);
        } else {
            Ptr<ConnRep> p = new ConnRep(_name, engineManager_);
            instance_[_name] = p;
            return p;
        }
    } else if (_type == "Fleet") {
        if (fleet_) {
            return Ptr<FleetRep>(fleet_);
        } else {
            Ptr<FleetRep> p = new FleetRep(_name, engineManager_);
            instance_[_name] = p;
            return p;
        }
    }

    cerr << "ManagerImpl::instanceNew: " << _type << " is an invalid type, returning NULL." << endl;
    return NULL;
}

void ManagerImpl::instanceDel(const string &_name) {
    FWK_DEBUG("ManagerImpl::instanceDel(" << _name << ")");

    map<string,Ptr<Instance> >::iterator instIt = instance_.find(_name);
    if (instIt == instance_.end()) {
        cerr << "ManagerImpl::instanceDel: " << _name << " was not found." << endl;
        return;
    }
    Ptr<DeletableInstance> deletablePtr= static_cast<DeletableInstance*>(instIt->second.ptr());
    deletablePtr->del();

    instance_.erase(instIt);
    if (instance_.find(_name) == instance_.end()) FWK_DEBUG (_name << " deleted from instance_");
}

Ptr<Instance> ManagerImpl::instance(const string& name){
    map<string,Ptr<Instance> >::const_iterator t = instance_.find(name);
    return t == instance_.end() ? NULL : (*t).second;
};

