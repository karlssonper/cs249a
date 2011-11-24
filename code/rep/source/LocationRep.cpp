#include "LocationRep.h"
#include "Engine.h"
#include "Debug.h"
#include <stdlib.h>
#include <ostream>
#include <sstream>

using namespace Shipping;
using namespace std;

const string LocationRep::segmentStr = "segment";
const int LocationRep::segmentStrlen = LocationRep::segmentStr.length();

LocationRep::LocationRep(const string& _name, EngineManager::Ptr engineManager)
    : DeletableInstance(_name), engineManager_(engineManager) {
        FWK_DEBUG("LocationRep::LocationRep with _name: " << _name);
};

LocationRep::~LocationRep() {
    FWK_DEBUG("LocationRep::~LocationRep() on " << name());
    engineManager_->entityManager()->locationDel(name()); 
};

void LocationRep::del() {
    FWK_DEBUG("LocationRep::deleteInstance() on " << name());
    engineManager_->entityManager()->locationDel(name()); 
}

unsigned int LocationRep::segmentNumber(const string& name) {
    if (name.substr(0, segmentStrlen) == segmentStr) {
        const char* t = name.c_str() + segmentStrlen;
        return atoi(t);
    }
    return 0;
};

string LocationRep::attribute(const string& attributeName) {

    FWK_DEBUG("LocationRep::attribute " << attributeName);

    Location::PtrConst locPtr = engineManager_->entityManager()->location(name());

    if (locPtr == NULL) {
        cerr << name() << " not a valid location (maybe deleted), returning empty string for " << attributeName << endl;
        return "";
    }

    if (attributeName.substr(0,7) == "segment" ) {
        unsigned int segNr = LocationRep::segmentNumber(attributeName)-1;
        if (segNr >= locPtr->outSegments() ) {
            cerr << "Segment number " << segNr+1 << " does not exist. Returning empty string.\n";
            return "";
        }
        Location::OutSegmentIteratorConst it = 
            engineManager_->entityManager()->location(name())->outSegmenterIterConst(segNr);
        string attr = locPtr->outSegment(it)->name();

        return attr;
    } else {
        
        // only valid for customers
        if (locPtr->type() != Location::customer()) {
            cerr << name() << " is not a customer, only segment attributes are valid" << endl;
            return "";
        }
        Customer::PtrConst cusPtr = static_cast<const Customer*>(locPtr.ptr());
        ostringstream s;
        if (attributeName == "transfer rate" ) {
            s << cusPtr->transferRate().value();
            return s.str();
        } else if (attributeName == "shipment size") {
            s << cusPtr->shipmentSize().value();
            return s.str();
        } else if (attributeName == "destination" ) {
            return cusPtr->destination();
        } else if (attributeName == "shipments recieved") {
            s << cusPtr->recievedShipments().value();
            return s.str();
        } else if (attributeName == "average latency") {
            s << cusPtr->averageLatency().value();
            return s.str();
        } else if (attributeName == "total cost") {
            s << cusPtr->totalCost().value();
            return s.str();
        } else {
            cerr << attributeName << " is an invalid attrib name for customer" << endl;
            return "";
        }
        
    }


    /*
    if (attributeName.substr(0,7) != "segment" ) {
    cerr << "LocationRep::attribute: " << attributeName << " is not a valid attribute name" << endl;
    return "";
    }

    unsigned int segNr = LocationRep::segmentNumber(attributeName)-1;

    FWK_DEBUG("segNr " << segNr << ", outSegments(): " << locPtr->outSegments() );
    if (segNr >= locPtr->outSegments() ) {
    cerr << "Segment number " << segNr+1 << " does not exist. Returning empty string.\n";
    return "";
    }

    Location::OutSegmentIteratorConst it = 
    engineManager_->entityManager()->location(name())->outSegmenterIterConst(segNr);
    string attr = locPtr->outSegment(it)->name();

    return attr;
    */
};


void LocationRep::attributeIs(const string& name, const string& v) {
    FWK_DEBUG("LocationRep::attributeIs with _name: " << name << " and v: " << v << ", doing nothing");
    return;
};

CustomerRep::CustomerRep(const string &_name, EngineManager::Ptr _engineManager)
    : LocationRep(_name, _engineManager) {
        FWK_DEBUG("CustomerRep::CustomerRep with _name: " << _name);
        Customer::Ptr p = Customer::CustomerNew(_name, _engineManager->virtualTimeActivityManager());
        engineManager_->entityManager()->locationIs(_name, p);
};

CustomerRep::~CustomerRep() {
    FWK_DEBUG("CustomerRep::~CustomerRep() on " << name());
};

PortRep::PortRep(const string &_name, EngineManager::Ptr _engineManager)
    : LocationRep(_name, _engineManager) {
        FWK_DEBUG("PortRep::PortRep with _name: " << _name);
        Port::Ptr p = Port::PortNew(_name);
        engineManager_->entityManager()->locationIs(_name, p);
}

PortRep::~PortRep() {
    FWK_DEBUG("PortRep::~PortRep()");
};

TruckTerminalRep::TruckTerminalRep(const string &_name, EngineManager::Ptr _engineManager)
    : LocationRep(_name, _engineManager) {
        FWK_DEBUG("TruckTerminalRep::TruckTerminalRep with _name: " << _name);
        TruckTerminal::Ptr p = TruckTerminal::TruckTerminalNew(_name);
        engineManager_->entityManager()->locationIs(_name, p);
}

TruckTerminalRep::~TruckTerminalRep(){
    FWK_DEBUG("TruckTerminalRep::~TruckTerminalRep()");
};

BoatTerminalRep::BoatTerminalRep(const string &_name, EngineManager::Ptr _engineManager)
    : LocationRep(_name, _engineManager) {
        FWK_DEBUG("BoatTerminalRep::BoatTerminalRep with _name: " << _name);
        BoatTerminal::Ptr p = BoatTerminal::BoatTerminalNew(_name);
        engineManager_->entityManager()->locationIs(_name, p);
}

BoatTerminalRep::~BoatTerminalRep() {
    FWK_DEBUG("BoatTerminalRep::~BoatTerminalRep()");
};

PlaneTerminalRep::PlaneTerminalRep(const string &_name, EngineManager::Ptr _engineManager)
    : LocationRep(_name, _engineManager) {
        FWK_DEBUG("PlaneTerminalRep::PlaneTerminalRep with _name: " << _name);
        PlaneTerminal::Ptr p = PlaneTerminal::PlaneTerminalNew(_name);
        engineManager_->entityManager()->locationIs(_name, p);
}

PlaneTerminalRep::~PlaneTerminalRep() {
    FWK_DEBUG("PlaneTerminalRep::~PlaneTerminalRep()");
};





