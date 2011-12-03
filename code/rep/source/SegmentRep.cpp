#include "Engine.h"
#include "SegmentRep.h"
#include <stdlib.h>
#include <sstream>
#include "Debug.h"
#include "Exception.h"
#include "OutputFloatingPoint.h"

using namespace std;
using namespace Shipping;

SegmentRep::SegmentRep(const string &_name, Ptr<EngineManager> _engineManager)
    : DeletableInstance(_name), engineManager_(_engineManager) {
    FWK_DEBUG("SegmentRep::SegmentRep with _name: " << _name);
}

SegmentRep::~SegmentRep() {
    FWK_DEBUG("SegmentRep::~SegmentRep() on " << name());
    engineManager_->entityManager()->segmentDel(name()); 
}

void SegmentRep::del() {
    FWK_DEBUG("SegmentRep::deleteInstance() on " << name());
    engineManager_->entityManager()->segmentDel(name()); 
}


TruckSegmentRep::TruckSegmentRep(const string &_name, EngineManager::Ptr _engineManager)
    : SegmentRep(_name, _engineManager) {
    FWK_DEBUG("TruckSegmentRep::TruckSegmentRep with _name: " << _name);
        TruckSegment::Ptr p = TruckSegment::TruckSegmentNew(_name,
                _engineManager->virtualTimeActivityManager(),
                _engineManager->fleet());
        if (!p) {
            std::cerr << "TruckSegmentRep new() failed" << std::endl;
            throw(Fwk::MemoryException("TruckSegmentRep"));
        }
        engineManager_->entityManager()->segmentIs(_name, p);
}

TruckSegmentRep::~TruckSegmentRep(){
    FWK_DEBUG("TruckSegmentRep::~TruckSegmentRep()");
}

BoatSegmentRep::BoatSegmentRep(const string &_name, Ptr<EngineManager> _engineManager)
    : SegmentRep(_name, _engineManager) {
    FWK_DEBUG("BoatSegmentRep::BoatSegmentRep with _name: " << _name);
        BoatSegment::Ptr p = BoatSegment::BoatSegmentNew(_name,
                _engineManager->virtualTimeActivityManager(),
                _engineManager->fleet());
        if (!p) {
            std::cerr << "BoatSegmentRep new() failed" << std::endl;
            throw(Fwk::MemoryException("BoatSegmentRep"));
        }
        engineManager_->entityManager()->segmentIs(_name, p);
}

BoatSegmentRep::~BoatSegmentRep(){
    FWK_DEBUG("BoatSegmentRep::~BoatSegmentRep()");
}

PlaneSegmentRep::PlaneSegmentRep(const string &_name, Ptr<EngineManager> _engineManager)
    : SegmentRep(_name, _engineManager) {
    FWK_DEBUG("PlaneSegmentRep::PlaneSegmentRep with _name: " << _name);
        PlaneSegment::Ptr p = PlaneSegment::PlaneSegmentNew(_name,
                _engineManager->virtualTimeActivityManager(),
                _engineManager->fleet());
        if (!p) {
            std::cerr << "PlaneSegmentRep new() failed" << std::endl;
            throw(Fwk::MemoryException("PlaneSegmentRep"));
        }
        engineManager_->entityManager()->segmentIs(_name, p);
}

PlaneSegmentRep::~PlaneSegmentRep(){
    FWK_DEBUG("PlaneSegmentRep::~PlaneSegmentRep()");
}

string SegmentRep::attribute(const string &_attributeName) {

    if (engineManager_->entityManager()->segment(name()) == NULL) {
        cerr << name() << " not a valid segment (maybe deleted), returning empty string for " << _attributeName << endl;
            return "";
    }

    FWK_DEBUG("SegmentRep::attribute with attribute: " << _attributeName);
    ostringstream s;
    if (_attributeName == "source") {
        return engineManager_->entityManager()->segment(name())->source();
    } else if (_attributeName == "length") {
        s << fltPnt2str(engineManager_->entityManager()->segment(name())->length().value());
        return s.str();
    } else if (_attributeName == "return segment") {
        return engineManager_->entityManager()->segment(name())->returnSegment();
    } else if (_attributeName == "difficulty") {
        s << fltPnt2str(engineManager_->entityManager()->segment(name())->difficulty().value());
        return s.str();
    } else if(_attributeName == "expedite support") {
        Shipping::Segment::ExpediteSupport exp = 
            engineManager_->entityManager()->segment(name())->expediteSupport();
        if (exp == Shipping::Segment::fullExpediteSupport()) {
            return "yes";
        } else {
            return "no";
        }
    } else if (_attributeName == "shipments recieved") {
        s << fltPnt2str(engineManager_->entityManager()->segment(name())->recievedShipments().value());
        return s.str();
    } else if (_attributeName == "shipments refused") {
        s << fltPnt2str(engineManager_->entityManager()->segment(name())->refusedShipments().value());
        return s.str();
    } else if (_attributeName == "capacity" ) {
        s << fltPnt2str(engineManager_->entityManager()->segment(name())->capacity().value());
        return s.str();
    } else {  
        cerr << "SegmentRep::attribute: SegmentRep error: " << _attributeName << " is an invalid attribute." << endl;
        return "";
    }
}

void SegmentRep::attributeIs(const string &_name, const string &_v) {

    FWK_DEBUG("SegmentRep::attributeIs with name: " << _name << " and v: " << _v);

    if (engineManager_->entityManager()->segment(name()) == NULL) {
        cerr << "SegmentRep::attributeIs: " << name() << " not found";
        throw(Fwk::EntityNotFoundException("SegmentRep::attributeIs"));
    }

    if (_name == "source") {
        engineManager_->entityManager()->segmentSourceIs(name(),_v);
    } else if (_name == "length") {
        float length = atof(_v.c_str()); 
        Miles l(length);
        engineManager_->entityManager()->segmentLengthIs(name(),l);
    } else if (_name == "return segment") {
        engineManager_->entityManager()->segmentReturnSegmentIs(name(),_v);
    } else if (_name == "difficulty") {
        float diff = atof(_v.c_str());
        SegmentDifficulty d(diff);
        engineManager_->entityManager()->segmentDifficultyIs(name(),d);
    } else if (_name == "capacity") {
        float cap = atof(_v.c_str());
        ShipmentCount c((int)cap);
        engineManager_->entityManager()->segmentCapacityIs(name(), c);
    
    } else if (_name == "expedite support") {
        Segment::ExpediteSupport exp;
        if (_v == "yes") {
            exp = Segment::fullExpediteSupport();
        } else {
            exp = Segment::noExpediteSupport();
        }
        engineManager_->entityManager()->segmentExpediteSupportIs(name(),exp);
    } else {
        cerr << "SegmentRep::attributeIs error: " << _name << " is an invalid attribute name" << endl;
        throw(Fwk::UnknownArgException("SegmentRep::attributeIs"));
    }
}
