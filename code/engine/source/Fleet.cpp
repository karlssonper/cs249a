#include "Fleet.h"
#include "Debug.h"
#include "Exception.h"

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
    if (!p) {
        std::cerr << "Fleet::FleetNew new() failed" << std::endl;
        throw(Fwk::MemoryException("Fleet::FleetNew"));
    }
    return p;
}

void Fleet::speedIs(Vehicle _vehicle, MilesPerHour _speed) {
    FWK_DEBUG("Fleet::speedIs on" << name());
    if (vehicleData_[_vehicle].speed_ == _speed) return;
    vehicleData_[_vehicle].speed_ = _speed;
}

void Fleet::costIs(Vehicle _vehicle, DollarsPerMile _cost) {
    FWK_DEBUG("Fleet::costIs on" << name());
    if (vehicleData_[_vehicle].cost_ == _cost) return;
    vehicleData_[_vehicle].cost_ = _cost;
}

void Fleet::capacityIs(Vehicle _vehicle, PackageCount _capacity) {
    FWK_DEBUG("Fleet::capacityIs on" << name());
    if (vehicleData_[_vehicle].capacity_ == _capacity) return;
    vehicleData_[_vehicle].capacity_ = _capacity;
}

void Fleet::swapData() {
    for (int i=0; i<3; ++i) {
        Fleet::Data temp = vehicleData_[i];
        vehicleData_[i] = vehicleBufferData_[i];
        vehicleBufferData_[i] = temp;
    }
}
