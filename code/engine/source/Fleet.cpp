#include "Fleet.h"
#include "Debug.h"
#include "Exception.h"
#include "FleetReactor.h"
#include "VirtualTimeActivityManager.h"

using std::string;
using namespace Shipping;

Fleet::Fleet(const string &_name, Fwk::Ptr<VirtualTimeActivityManager> _vtam) 
    : Fwk::NamedInterface(_name), virtualTimeActivityManager_(_vtam) {
    FWK_DEBUG("Fleet constructor with name " << _name);
    string reactorName = _name;
    reactorName.append("Reactor");
    FleetReactor::Ptr rp = FleetReactor::FleetReactorNew(reactorName, this, _vtam);
    notifieeIs("unusedName", rp);
}

Fleet::~Fleet(){
    FWK_DEBUG("Fleet::~Fleet() with name: " << name());
};

Fleet::Ptr Fleet::FleetNew(const string &_name, Fwk::Ptr<VirtualTimeActivityManager> _vtam) {
    FWK_DEBUG("Fleet::FleetNew with name " << _name);
    Fleet::Ptr p = new Fleet(_name, _vtam);
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

void Fleet::speedBufferIs(Vehicle _vehicle, MilesPerHour _speed) {
    FWK_DEBUG("Fleet::speedIs on" << name());
    if (vehicleBufferData_[_vehicle].speed_ == _speed) return;
    vehicleBufferData_[_vehicle].speed_ = _speed;
}

void Fleet::costIs(Vehicle _vehicle, DollarsPerMile _cost) {
    FWK_DEBUG("Fleet::costIs on" << name());
    if (vehicleData_[_vehicle].cost_ == _cost) return;
    vehicleData_[_vehicle].cost_ = _cost;
}

void Fleet::costBufferIs(Vehicle _vehicle, DollarsPerMile _cost) {
    FWK_DEBUG("Fleet::costIs on" << name());
    if (vehicleBufferData_[_vehicle].cost_ == _cost) return;
    vehicleBufferData_[_vehicle].cost_ = _cost;
}

void Fleet::capacityIs(Vehicle _vehicle, PackageCount _capacity) {
    FWK_DEBUG("Fleet::capacityIs on" << name());
    if (vehicleData_[_vehicle].capacity_ == _capacity) return;
    vehicleData_[_vehicle].capacity_ = _capacity;
}

void Fleet::capacityBufferIs(Vehicle _vehicle, PackageCount _capacity) {
    FWK_DEBUG("Fleet::capacityIs on" << name());
    if (vehicleData_[_vehicle].capacity_ == _capacity) return;
    vehicleData_[_vehicle].capacity_ = _capacity;
}

void Fleet::bufferStartIs(TimeOfDay _tod) {
    if (bufferStart_ == _tod) return;
    bufferStart_ = _tod;
}

void Fleet::bufferEndIs(TimeOfDay _tod) {
    if (bufferEnd_ == _tod) return;
    bufferEnd_ = _tod;
}


void Fleet::swapData() {
    for (int i=0; i<3; ++i) {
        Fleet::Data temp = vehicleData_[i];
        vehicleData_[i] = vehicleBufferData_[i];
        vehicleBufferData_[i] = temp;
    }
}

void Fleet::notifieeIs(const string &_name, Notifiee::Ptr _notifiee) {
    notifiee_ = _notifiee;
}

Fleet::Notifiee::Notifiee(const string &_name, Fleet* _notifier)
    : Fwk::BaseNotifiee<Fleet>(_name, _notifier) {}
