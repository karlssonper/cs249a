#include "Location.h"
#include "Debug.h"
#include "Activity.h"

using namespace Shipping;

Location::Location(const string &_name, LocationType _type) 
    : Fwk::NamedInterface(_name), type_(_type), activityManager_(Fwk::activityManagerInstance().ptr()) {
        FWK_DEBUG("Location constructor with name " << _name);
}

Location::~Location(){
    FWK_DEBUG("Location::~Location() with name: " << name());

};

Location::OutSegmentIteratorConst Location::outSegmenterIterConst(const unsigned int n) const {
    if (n >= outSegment_.size()) FWK_DEBUG("ERROR outSegmenterIterConst(int n) where n > size");
    OutSegmentIteratorConst it = outSegment_.begin();
    for (int i=0; i < n; ++i) it++;
    return it;
};

Location::OutSegmentIterator Location::outSegmenterIter(unsigned int n) {
    n;
    if (n >= outSegment_.size()) FWK_DEBUG("ERROR outSegmenterIter(int n) where n > size");
    OutSegmentIterator it = outSegment_.begin();
    for (int i=0; i < n; ++i) it++;
    return it;
};

Segment::Ptr Location::outSegment(OutSegmentIteratorConst it) const {
    FWK_DEBUG("Location::outSegment() with name " << (*it)->name());
    return *it;
};

void Location::outSegmentNew(Segment::Ptr _p) {
    FWK_DEBUG("Location::outSegmentNew adding " << _p->name());
    outSegment_.push_back(_p);
}

void Location::outSegmentDel(Segment::Ptr _p) {
    FWK_DEBUG("Location::outSegmentDel removing " << _p->name() << " from outgoing segments list");
    Location::OutSegmentIterator it = outSegmenterIter();
    for (unsigned int i = 0; i < outSegments(); ++i, it++) {
        if ((*it)->name() == _p->name()) break;
    }
    if (it == outSegment_.end()) {
        FWK_DEBUG("Location::outSegmentDel  " << _p->name() << " not found in outgoing segments list");
        return;
    }
    outSegment_.erase(it);
}

Customer::Customer(const string &_name) 
    : Location(_name,customer()) {
        FWK_DEBUG("Customer constructor with name " << _name);
}

Customer::~Customer(){
    FWK_DEBUG("Customer::~Customer() with name: " << name());
};

Customer::Ptr Customer::CustomerNew(const string &_name) {
    FWK_DEBUG("Customer::CustomerNew with name " << _name);
    Customer::Ptr p = new Customer(_name);
    return p;
}

void Customer::notifieeIs(const string &_name, Notifiee* _notifiee) {
    notifiee_ = _notifiee;
}

void Customer::transferRateIs(TransferRate _transferRate) {
    FWK_DEBUG(name() <<  "transferRateIs " << _transferRate.value());
    if (transferRate_ == _transferRate) return;
    transferRate_ = _transferRate;
    if (notifiee_) notifiee_->onAtttributeUpdate(this);
}

void Customer::shipmentSizeIs(PackageCount _shipmentSize) {
    FWK_DEBUG(name() <<  "shipmentSizeIs " << _shipmentSize.value());
    if (shipmentSize_ == _shipmentSize) return;
    shipmentSize_ = _shipmentSize;
    if (notifiee_) notifiee_->onAtttributeUpdate(this);
}

void Customer::destinationIs(const string &_destination) {
    FWK_DEBUG(name() <<  "destinationIs " << _destination);
    if (destination_ == _destination) return;
    destination_ = _destination;
    if (notifiee_) notifiee_->onAtttributeUpdate(this);
}

void Customer::recievedPackagesIs(PackageCount _recievedPackages) {
    FWK_DEBUG(name() << " recievedPackagesIs " << _recievedPackages.value());
    if (recievedPackages_ == _recievedPackages) return;
    recievedPackages_ = _recievedPackages;
    if (notifiee_) notifiee_->onAtttributeUpdate(this);
}

Port::Port(const string &_name) 
    : Location(_name, port()) {
        FWK_DEBUG("Port constructor with name " << _name);
}

Port::~Port(){
    FWK_DEBUG("Port::~Port() with name: " << name());
};

Port::Ptr Port::PortNew(const string &_name) {
    FWK_DEBUG("Port::PortNew with name " << _name);
    Port::Ptr p = new Port(_name);
    return p;
}

TruckTerminal::TruckTerminal(const string &_name) 
    : Location(_name, truckTerminal()) {
        FWK_DEBUG("TruckTerminal constructor with name " << _name);
}

TruckTerminal::~TruckTerminal(){
    FWK_DEBUG("TruckTerminal::~TruckTerminal() with name: " << name());
};


TruckTerminal::Ptr TruckTerminal::TruckTerminalNew(const string &_name) {
    FWK_DEBUG("TruckTerminal::TruckTerminalNew with name " << _name);
    TruckTerminal::Ptr p = new TruckTerminal(_name);
    return p;
}

BoatTerminal::BoatTerminal(const string &_name) 
    : Location(_name, boatTerminal()) {
        FWK_DEBUG("BoatTerminal constructor with name " << _name);
}

BoatTerminal::~BoatTerminal(){
    FWK_DEBUG("BoatTerminal::~BoatTerminal() with name: " << name());
};

BoatTerminal::Ptr BoatTerminal::BoatTerminalNew(const string &_name) {
    FWK_DEBUG("BoatTerminal::BoatTerminalNew with name " << _name);
    BoatTerminal::Ptr p = new BoatTerminal(_name);
    return p;
}

PlaneTerminal::PlaneTerminal(const string &_name) 
    : Location(_name, planeTerminal()) {
        FWK_DEBUG("PlaneTerminal constructor with name " << _name);
}

PlaneTerminal::~PlaneTerminal() {
    FWK_DEBUG("PlaneTerminal::~PlaneTerminal() with name: " << name());
};


PlaneTerminal::Ptr PlaneTerminal::PlaneTerminalNew(const string &_name) {
    FWK_DEBUG("PlaneTerminal::PlaneTerminalNew with name " << _name);
    PlaneTerminal::Ptr p = new PlaneTerminal(_name);
    return p;
}




