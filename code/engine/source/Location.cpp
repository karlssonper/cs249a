#include "Location.h"
#include "Exception.h"
#include "Output.h"
#include "CustomerReactor.h"
#include "VirtualTimeActivityManager.h"
#include "EntityManager.h"

using namespace Shipping;

Location::Location(const string &_name, LocationType _type) 
    : Fwk::NamedInterface(_name), type_(_type) {
        FWK_DEBUG("Location constructor with name " << _name);
}

Location::~Location(){
    FWK_DEBUG("Location::~Location() with name: " << name());

};

Location::OutSegmentIteratorConst Location::outSegmenterIterConst(
    const unsigned int n) const {
    if (n >= outSegment_.size()) {
        FWK_DEBUG("ERROR outSegmenterIterConst(int n) where n > size");
    }
    OutSegmentIteratorConst it = outSegment_.begin();
    for (unsigned int i=0; i < n; ++i) it++;
    return it;
};

Location::OutSegmentIterator Location::outSegmenterIter(unsigned int n) {
    n;
    if (n >= outSegment_.size()) {
        cerr << "Location::outSegmenterIter(int n) where n > size" << endl;
        throw(Fwk::RangeException("Location::OutSegmentIterator"));
    }
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
    FWK_DEBUG("Location::outSegmentDel removing " << _p->name() << 
        " from outgoing segments list");
    Location::OutSegmentIterator it = outSegmenterIter();
    for (unsigned int i = 0; i < outSegments(); ++i, it++) {
        if ((*it)->name() == _p->name()) break;
    }
    if (it == outSegment_.end()) {
        FWK_DEBUG("Location::outSegmentDel  " << _p->name() <<
            " not found in outgoing segments list");
        return;
    }
    outSegment_.erase(it);
}

Customer::Customer(const string &_name,
                   VirtualTimeActivityManager::Ptr vtAm, 
                   Fwk::Ptr<EntityManager> _entityManager)
                   : Location(_name,customer()),entityManager_(_entityManager){
                       FWK_DEBUG("Customer constructor with name " << _name);
                       string reactorName = _name;
                       reactorName.append("Reactor");
                       CustomerReactor::Ptr p = 
                           CustomerReactor::CustomerReactorNew(
                           reactorName, this, vtAm, _entityManager);
                       notifieeIs("unusedName",p);
}

Customer::~Customer() {
    FWK_DEBUG("Customer::~Customer() with name: " << name());
};

Customer::Ptr Customer::CustomerNew(const string &_name,
                                   VirtualTimeActivityManager::Ptr vtAm, 
                                   Fwk::Ptr<EntityManager> _entityManager) {
    FWK_DEBUG("Customer::CustomerNew with name " << _name);
    Customer::Ptr p = new Customer(_name, vtAm, _entityManager);
    if (!p) {
        cerr << "Customer::CustomeNew new() failed" << endl;
        throw(Fwk::MemoryException("Customer::CustomerNew"));
    }
    return p;
}

Customer::Notifiee::Notifiee(const string &_name, Customer* _notifier)
    : Fwk::BaseNotifiee<Customer>(_name, _notifier) {}

void Customer::notifieeIs(const string &_name, Notifiee::Ptr _notifiee) {
    FWK_DEBUG("Customer::notifieeIs on " << name());
    notifiee_ = _notifiee;
    if (notifiee_) FWK_DEBUG("Notifiee: " << notifiee_->name());
    else FWK_DEBUG("Notifiee removed");
}

void Customer::transferRateIs(TransferRate _transferRate) {
    FWK_DEBUG(name() <<  " transferRateIs " << _transferRate.value());
    if (transferRate_ == _transferRate) return;
    transferRate_ = _transferRate;
    if (notifiee_) notifiee_->onAttributeUpdate();
}

void Customer::shipmentSizeIs(PackageCount _shipmentSize) {
    FWK_DEBUG(name() <<  " shipmentSizeIs " << _shipmentSize.value());
    if (shipmentSize_ == _shipmentSize) return;
    shipmentSize_ = _shipmentSize;
    if (notifiee_) notifiee_->onAttributeUpdate();
}

void Customer::destinationIs(const string &_destination) {
    FWK_DEBUG(name() <<  " destinationIs " << _destination);
    if (destination_ == _destination) return;
    destination_ = _destination;
    if (notifiee_) {
        FWK_DEBUG("Customer:destinationIs notifying " << notifiee_->name());
        notifiee_->onAttributeUpdate();
    }
}

void Customer::recievedShipmentsIs(ShipmentCount _recievedShipments) {
    FWK_DEBUG(name() << " recievedPackagesIs " << _recievedShipments.value());
    if (recievedShipments_ == _recievedShipments) return;
    recievedShipments_ = _recievedShipments;
}

void Customer::recievedShipmentsInc() {
    recievedShipments_ = recievedShipments_.value() + 1;
    FWK_SIM_DEBUG(name() << " recievedShipmentsInc(), total now is " <<
        recievedShipments().value());
}

void Customer::averageLatencyIs(Hours _averageLatency) {
    FWK_DEBUG(name() << " averageLatencyIs " << _averageLatency.value());
    if (averageLatency_ == _averageLatency) return;
    averageLatency_ = _averageLatency;
}

void Customer::totalLatencyIs(Hours _totalLatency) {
    FWK_DEBUG(name() << " totalLatencyIs " << _totalLatency.value());
    if (totalLatency_ == _totalLatency) return;
    totalLatency_ = _totalLatency;
}

void Customer::totalCostIs(Dollars _totalCost) {
    FWK_DEBUG(name() << " totalCostIs " << _totalCost.value());
    if (totalCost_ == _totalCost) return;
    totalCost_ = _totalCost;
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
    if (!p) {
        cerr << "Port::PortNew new() failed" << endl;
        throw(Fwk::MemoryException("Port::PortNew"));
    }
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
    if (!p) {
        cerr << "TruckTerminal::TruckTerminalNew new() failed" << endl;
        throw(Fwk::MemoryException("TruckTerminal::TruckTerminalNew"));
    }
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
    if (!p) {
        cerr << "BoatTerminal::BoatTerminalNew new() failed" << endl;
        throw(Fwk::MemoryException("BoatTerminal::BoatTerminalNew"));
    }
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
    if (!p) {
        cerr << "PlaneTerminal::PlaneTerminalNew new() failed" << endl;
        throw(Fwk::MemoryException("PlaneTerminal::PlaneTerminalNew"));
    }
    return p;
}




