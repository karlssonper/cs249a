/*
* FleetRep.cpp
*
*  Created on: Nov 4, 2011
*      Author: per
*/

#include "FleetRep.h"
#include "Engine.h"
#include <stdlib.h>
#include "Debug.h"
#include <sstream>
#include "OutputFloatingPoint.h"
#include "Exception.h"
#include <algorithm>
#include <iterator>

using namespace Shipping;
using namespace std;

FleetRep::FleetRep(const string& _name, EngineManager::Ptr _engineManager)
    : DeletableInstance(_name), engineManager_(_engineManager) {
        FWK_DEBUG("FleetRep::FleetRep with _name: " << _name);
}

FleetRep::~FleetRep(){
    FWK_DEBUG("FleetRep::~FleetRep()");
};

string FleetRep::attribute(const string& attributeName) {
    FWK_DEBUG("FleetRep::attribute with attribute: " << attributeName);
    FleetRep::FleetAttribute fleetAttribute =
        parseFleetAttribute(attributeName);
    ostringstream s;
    if (fleetAttribute.prop == "speed" ) {
        s << fltPnt2str(
            engineManager_->fleet()->speed(fleetAttribute.vehicle).value());
        return s.str();
    } else if (fleetAttribute.prop == "speedAlt") {
        s << fltPnt2str(
            engineManager_->fleet()->speedBuffer(
            fleetAttribute.vehicle).value());
        return s.str();
    } else if (fleetAttribute.prop == "cost") {
        s << fltPnt2str(
            engineManager_->fleet()->cost(fleetAttribute.vehicle).value());
        return s.str();
    } else if (fleetAttribute.prop == "costAlt") {
        s << fltPnt2str(
            engineManager_->fleet()->costBuffer(
            fleetAttribute.vehicle).value());
        return s.str();
    } else if (fleetAttribute.prop == "capacity") {
        s << fltPnt2str(engineManager_->fleet()->capacity(
            fleetAttribute.vehicle).value());
        return s.str();
    } else if (fleetAttribute.prop == "capacityAlt") {
        s << fltPnt2str(engineManager_->fleet()->capacityBuffer(
            fleetAttribute.vehicle).value());
        return s.str();
    } else if (fleetAttribute.prop == "altTimeStart") {
        s << fltPnt2str(engineManager_->fleet()->bufferStart().value());
        return s.str();
    } else if (fleetAttribute.prop == "altTimeEnd") {
        s << fltPnt2str(engineManager_->fleet()->bufferEnd().value());
        return s.str();
    } else {
        cerr << "FleetRep::attribute: << " <<
            attributeName << " invalid." << endl;
        return ""; 
    }
}

void FleetRep::attributeIs(const string& name, const string& _v) {
    FWK_DEBUG("FleetRep::attributeIs with name: " << name << " and v: " << _v);

    if (name == "alt time") {
        
        deque<string> parseWords;
        istringstream iss(_v);
        copy(std::istream_iterator<std::string>(iss), 
            istream_iterator<std::string>(),
        back_inserter<deque<std::string> >(parseWords) );

        unsigned int firstTime = atoi(parseWords.front().c_str());
        parseWords.pop_front();
        unsigned int secondTime = atoi(parseWords.front().c_str());
        TimeOfDay ftod(firstTime);
        TimeOfDay stod(secondTime);
        engineManager_->fleet()->bufferIs(ftod, stod);
        return;
    }  

    FleetRep::FleetAttribute fleetAttribute = parseFleetAttribute(name);
    if (fleetAttribute.vehicle == Fleet::undefined()) {
        cerr << "FleetRep::attributeIs: Undefined Fleet type." << endl;
        throw(Fwk::UnknownArgException("FleetRep::attributeIs"));
    } else if (fleetAttribute.prop == "speed" ) {
        float speed = atof(_v.c_str());
        MilesPerHour mph(speed);
        engineManager_->fleet()->speedIs(fleetAttribute.vehicle, mph);
    } else if (fleetAttribute.prop == "speedAlt" ) {
        float speed = atof(_v.c_str());
        MilesPerHour mph(speed);
        engineManager_->fleet()->speedBufferIs(fleetAttribute.vehicle, mph);
    } else if (fleetAttribute.prop == "cost") {
        float cost = atof(_v.c_str());
        DollarsPerMile dpm(cost);
        engineManager_->fleet()->costIs(fleetAttribute.vehicle, dpm);
    } else if (fleetAttribute.prop == "costAlt") {
        float cost = atof(_v.c_str());
        DollarsPerMile dpm(cost);
        engineManager_->fleet()->costBufferIs(fleetAttribute.vehicle, dpm);
    } else if (fleetAttribute.prop == "capacity") {
        int capacity = atoi(_v.c_str());
        if (capacity < 0 ) return;
        PackageCount pc(capacity);
        engineManager_->fleet()->capacityIs(fleetAttribute.vehicle, pc);
    } else if (fleetAttribute.prop == "capacityAlt") {
        int capacity = atoi(_v.c_str());
        if (capacity < 0 ) return;
        PackageCount pc(capacity);
        engineManager_->fleet()->capacityBufferIs(fleetAttribute.vehicle, pc);
    } else {
        cerr << "FleetRep error: Invalid property." << endl;
        throw(Fwk::UnknownArgException("FleetRep::attributeIs"));
    }
}

FleetRep::FleetAttribute FleetRep::parseFleetAttribute(
    const string & attributeName) {
    FWK_DEBUG("parseFleetAttribute on " << attributeName);
    FleetRep::FleetAttribute fleetAttribute;
    string mode;
    size_t modeLength;
    modeLength = attributeName.find_first_of(",");
    mode = attributeName.substr(0,modeLength);
    fleetAttribute.prop = attributeName.substr(
        modeLength+2,attributeName.size()-modeLength+2);
    if (mode == "Truck") {
        fleetAttribute.vehicle = Fleet::truck();
    } else if (mode == "Boat") {
        fleetAttribute.vehicle = Fleet::boat();
    } else if (mode == "Plane") {
        fleetAttribute.vehicle = Fleet::plane();
    } else {
        cerr << "FleetRep error: " << attributeName <<
            " is an invalid vehicle" << endl;
        throw(Fwk::RangeException("FleetRep::parseFleetAttribute"));
    }
    return fleetAttribute;
};
