#include "Segment.h"
#include "Debug.h"

using namespace Shipping;

Segment::Segment(const string &_name, SegmentType _st) : 
Fwk::NamedInterface(_name),
    source_(""),
    returnSegment_(""),
    expediteSupport_(Segment::noExpediteSupport()),
    type_(_st) {
        FWK_DEBUG("Segment constructor with name " << _name);
}

Segment::~Segment(){
    FWK_DEBUG("Segment::~Segment() with name: " << name());
};

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

TruckSegment::TruckSegment(const string &_name) : Segment(_name, truckSegment()) {
    FWK_DEBUG("TruckSegment constructor with name " << _name);
}

TruckSegment::~TruckSegment(){
    FWK_DEBUG("TruckSegment::~TruckSegment() with name: " << name());
};

TruckSegment::Ptr TruckSegment::TruckSegmentNew(const string &_name) {
    FWK_DEBUG("TruckSegmet::TruckSegmentNew with name " << _name);
    TruckSegment::Ptr p = new TruckSegment(_name);
    return p;
}

BoatSegment::BoatSegment(const string &_name) : Segment(_name, boatSegment()) {
    FWK_DEBUG("BoatSegment constructor with name " << _name);
}

BoatSegment::~BoatSegment(){
    FWK_DEBUG("BoatSegment::~BoatSegment() with name: " << name());
};

BoatSegment::Ptr BoatSegment::BoatSegmentNew(const string &_name) {
    FWK_DEBUG("BoatSegment::BoatSegmentNew with name " << _name);
    BoatSegment::Ptr p = new BoatSegment(_name);
    return p;
}

PlaneSegment::PlaneSegment(const string &_name) : Segment(_name, planeSegment()) {
    FWK_DEBUG("PlaneSegment constructor with name " << _name);
}

PlaneSegment::~PlaneSegment(){
    FWK_DEBUG("PlaneSegment::~PlaneSegment() with name: " << name());
};


PlaneSegment::Ptr PlaneSegment::PlaneSegmentNew(const string &_name) {
    FWK_DEBUG("PlaneSegment::PlaneSegmentNew with name " << _name);
    PlaneSegment::Ptr p = new PlaneSegment(_name);
    return p;
}

