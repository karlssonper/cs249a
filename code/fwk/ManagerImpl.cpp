#include "ManagerImpl.h"
#include "LocationRep.h"

Ptr<Instance> ManagerImpl::instanceNew(const string& _name, const string& _type) {
    if (_type == "Customer") {
        Ptr<CustomerRep> p = new CustomerRep(_name, this);
        instance_[_name] = p;
        return p;
    } else if (_type == "Port") {
        Ptr<PortRep> p = new PortRep(name, this);
        instance_[_name] = p;
        return p;
    } else if (_type == "Truck terminal") {
        Ptr<TruckTerminalRep> p = new TruckTerminalRep(_name, this);
        instance_[_name] = p;
        return p;       
    } else if (_type == "Boat terminal") {
        Ptr<BoatTerminalRep> p = new BoatTerminalRep(_name, this);
        instance_[_name] = p;
        return p;
    } else if (_type == "Plane terminal") {
        Ptr<PlaneTerminalRep> p = new PlaneTerminalRep(_name, this);
        instance_[_name] = p;
        return p;
    } else if (_type == "Truck segment" {
        Ptr<TruckSegmentRep> p = new TruckSegmentRep(_name, this);
        instance_[_name] = p;
        return p;
    } else if (_type == "Boat segment" {
        Ptr<BoatSegmentRep> p = new BoatSegmentRep(_name, this);
        instance_[_name] = p;
        return p;
    } else if (_type == "Plane segment" {
        Ptr<PlaneSegmentRep> p = new PlaneSegmentRep(_name, this);
        instance_[_name] = p;
        return p;
    } else if (_type == "Stats" {
        Ptr<StatsRep> p = new StatsRep(_name, this);
        instance_[_name] = p;
        return p;
    } else if (_type == "Conn" {
        Ptr<ConnRep> p = new ConnRep(_name, this);
        instance_[_name] = p;
        return p;
    } else if (_type == "Fleet" {
        Ptr<FleetRep> p = new FleetRep(_name, this);
        instance_[_name] = p;
        return p;
    }
    return NULL;
}

Ptr<Instance> ManagerImpl::instance(const string& name) {
    map<string,Ptr<Instance> >::const_iterator t = instance_.find(name);
    return t == instance_.end() ? NULL : (*t).second;
}
