#include "Segment.h"
#include "Debug.h"
#include "Shipment.h"
#include "SegmentReactor.h"
#include "VirtualTimeActivityManager.h"
#include "Fleet.h"
#include "Exception.h"

using namespace Shipping;

Segment::Segment(const string &_name, SegmentType _st,
        VirtualTimeActivityManager::Ptr vtam, Fleet::PtrConst _fleet) :
    Fwk::NamedInterface(_name),
    source_(""),
    returnSegment_(""),
    expediteSupport_(Segment::noExpediteSupport()),
    capacity_(10),
    type_(_st) {
    FWK_DEBUG("Segment constructor with name " << _name);
    notifiee_ = SegmentReactor::SegmentReactorNew(_name +std::string("Reactor"),
            this, vtam, _fleet);
}

Segment::~Segment(){

};

Segment::Notifiee::~Notifiee() {
        FWK_DEBUG("Segment::Notifiee::~Notifiee() with name: " << name());
};

Segment::Notifiee::Notifiee(std::string _name, Segment * seg) :
        Fwk::BaseNotifiee<Segment>(_name, seg) {
    FWK_DEBUG("Segment::Notifiee::Notifiee() with name: " << name());
};

void Segment::Notifiee::onShipmentEnq(Shipment::Ptr p) {

};

void Segment::Notifiee::onShipmentDeq() {
};

void Segment::Notifiee::onActivePackageInc(PackageCount pc) {
};

void Segment::Notifiee::onActivePackageDec(PackageCount pc) {
}

void Segment::notifieeIs(string _name, Notifiee* _p) {
    FWK_DEBUG("Segment::notifieeIs, name " << _name );

    if (!_p) {
        //notifiee_.erase(notifiee_.find(_name));
        return;
    }

    if (notifiee_) {
        cerr << "Segment::notifieeIs: " << _name << " already exists" << endl;
        throw(Fwk::NameInUseException("Segment::notifieeIs"));
    }

    Notifiee::Ptr p = _p;
    notifiee_ = _p;
}

void Segment::activePackageInc(PackageCount c) {
    FWK_DEBUG("Segment::activePackageInc with name: " << name());
    activePackages_ = activePackages_.value() + c.value();

    FWK_DEBUG("Notifying -> " << notifiee_->name());
    notifiee_->onActivePackageInc(c);
}
void Segment::activePackageDec(PackageCount c) {
    FWK_DEBUG("Segment::activePackageDec with name: " << name());
    activePackages_ = activePackages_.value() - c.value();

    FWK_DEBUG("Notifying -> " << notifiee_->name());
    notifiee_->onActivePackageDec(c);
}

void Segment::shipmentEnq(Fwk::Ptr<Shipment> _s) {
    FWK_DEBUG("Segment::shipmentEnq with name: " << name());
    shipment_.push_back(_s);

    FWK_DEBUG("Notifying -> " << notifiee_->name());
    notifiee_->onShipmentEnq(_s);
}

void Segment::shipmentDeq() {
    FWK_DEBUG("Segment::shipmentEnq with name: " << name());
    shipment_.pop_front();

    FWK_DEBUG("Notifying -> " << notifiee_->name());
    notifiee_->onShipmentDeq();
}

void Segment::sourceIs(const string &_source) {
    FWK_DEBUG("Segment::sourceIs: " << _source);
    if (source_ == _source) return;
    source_ = _source;
}

void Segment::lengthIs(Miles _length) {
    FWK_DEBUG("Segment::lengthIs");
    if (length_ == _length) return;
    length_ = _length;
}

void Segment::capacityIs(ShipmentCount _capacity) {
    FWK_DEBUG("Segment::capacityIs");
    if (capacity_ == _capacity) return;
    capacity_ = _capacity;
}

void Segment::returnSegmentIs(const string &_returnSegment) {
    FWK_DEBUG("Segment::returnSegmentIs " << _returnSegment);
    if (returnSegment_ == _returnSegment) return;
    returnSegment_ = _returnSegment;
}

void Segment::difficultyIs(SegmentDifficulty _difficulty) {
    FWK_DEBUG("Segment::difficultyIs");
    if (difficulty_ == _difficulty) return;
    difficulty_ = _difficulty;
}

void Segment::expediteSupportIs(ExpediteSupport _expediteSupport) {
    FWK_DEBUG("Segment::expediteSupportIs");
    if (expediteSupport_ == _expediteSupport) return;
    expediteSupport_ = _expediteSupport;
}

void Segment::recievedShipmentsInc() {
    FWK_DEBUG("Segment::recievdShipmentsInc");
    ++recievedShipments_;
}

void Segment::refusedShipmentsInc() {
    FWK_DEBUG("Segment::refusedShipmentsInc");
    ++refusedShipments_;
}

TruckSegment::TruckSegment(const string &_name,
        VirtualTimeActivityManager::Ptr vtam, Fleet::PtrConst _fleet) :
        Segment(_name, truckSegment(), vtam, _fleet) {
    FWK_DEBUG("TruckSegment constructor with name " << _name);
}

TruckSegment::~TruckSegment(){
    FWK_DEBUG("TruckSegment::~TruckSegment() with name: " << name());
};

TruckSegment::Ptr TruckSegment::TruckSegmentNew(const string &_name,
        VirtualTimeActivityManager::Ptr vtam, Fleet::PtrConst _fleet) {
    FWK_DEBUG("TruckSegmet::TruckSegmentNew with name " << _name);
    TruckSegment::Ptr p = new TruckSegment(_name, vtam, _fleet);
    if (!p) {
        std::cerr << "TruckSegmentNew new() failed" << std::endl;
        throw(Fwk::MemoryException("TruckSegmentNew"));
    }
    return p;
}

BoatSegment::BoatSegment(const string &_name,
        VirtualTimeActivityManager::Ptr vtam, Fleet::PtrConst _fleet) :
        Segment(_name, boatSegment(), vtam, _fleet) {
    FWK_DEBUG("BoatSegment constructor with name " << _name);
}

BoatSegment::~BoatSegment(){
    FWK_DEBUG("BoatSegment::~BoatSegment() with name: " << name());
};

BoatSegment::Ptr BoatSegment::BoatSegmentNew(const string &_name,
        VirtualTimeActivityManager::Ptr vtam, Fleet::PtrConst _fleet) {
    FWK_DEBUG("BoatSegment::BoatSegmentNew with name " << _name);
    BoatSegment::Ptr p = new BoatSegment(_name, vtam, _fleet);
     if (!p) {
        std::cerr << "BoatSegmentNew new() failed" << std::endl;
        throw(Fwk::MemoryException("BoatSegmentNew"));
    }
    return p;
}

PlaneSegment::PlaneSegment(const string &_name,
        VirtualTimeActivityManager::Ptr vtam, Fleet::PtrConst _fleet) :
        Segment(_name, planeSegment(), vtam, _fleet) {
    FWK_DEBUG("PlaneSegment constructor with name " << _name);
}

PlaneSegment::~PlaneSegment(){
    FWK_DEBUG("PlaneSegment::~PlaneSegment() with name: " << name());
};


PlaneSegment::Ptr PlaneSegment::PlaneSegmentNew(const string &_name,
        VirtualTimeActivityManager::Ptr vtam, Fleet::PtrConst _fleet) {
    FWK_DEBUG("PlaneSegment::PlaneSegmentNew with name " << _name);
    PlaneSegment::Ptr p = new PlaneSegment(_name, vtam, _fleet);
      if (!p) {
        std::cerr << "PlaneSegmentNew new() failed" << std::endl;
        throw(Fwk::MemoryException("PlaneSegmentNew"));
    }
    return p;
}

