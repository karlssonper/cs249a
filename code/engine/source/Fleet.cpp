/*
 * Fleet.cpp
 *
 *  Created on: Nov 4, 2011
 *      Author: per
 */

#include "Fleet.h"
#include "Debug.h"

using std::string;

using namespace Shipping;

Fleet::Fleet(const string &_name) : Fwk::NamedInterface(_name) {
    FWK_DEBUG("Fleet constructor with name " << _name);
}

Fleet::~Fleet(){
    FWK_DEBUG("Fleet::~Fleet() with name: " << name());
};

Fleet::Ptr Fleet::FleetNew(const string &_name) {
    FWK_DEBUG("Fleet::FleetNew with name " << _name);
    Fleet::Ptr p = new Fleet(_name);
    return p;
}

void Fleet::speedIs(Vehicle _vehicle, MilesPerHour _speed) {
    FWK_DEBUG("Fleet::speedIs on" << name());
    vehicleData_[_vehicle].speed_ = _speed;
}

void Fleet::costIs(Vehicle _vehicle, DollarsPerMile _cost) {
    FWK_DEBUG("Fleet::costIs on" << name());
    vehicleData_[_vehicle].cost_ = _cost;
}

void Fleet::capacityIs(Vehicle _vehicle, PackageCapacity _capacity) {
    FWK_DEBUG("Fleet::capacityIs on" << name());
    vehicleData_[_vehicle].capacity_ = _capacity;
}
