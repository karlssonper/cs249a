/*
* StatsRep.cpp
*
*  Created on: Nov 4, 2011
*      Author: per
*/

#include "StatsRep.h"
#include "Engine.h"
#include <stdlib.h>
#include "Debug.h"
#include <sstream>
#include "OutputFloatingPoint.h"

using namespace Shipping;
using namespace std;


StatsRep::StatsRep(const string& _name, EngineManager::Ptr _engineManager)
    : DeletableInstance(_name), engineManager_(_engineManager) {
        FWK_DEBUG("StatsRep::StatsRep with _name: " << _name);
};

StatsRep::~StatsRep() {
    FWK_DEBUG("StatsRep::~StatsRep()");
};

string StatsRep::attribute(const string& _attributeName) {

    FWK_DEBUG("StatsRep::attribute with attribute: " << _attributeName);

    if (_attributeName == "Customer") {
        unsigned int count = engineManager_->stats()->customerCount();
        ostringstream s;
        s << count;
        return s.str();
    } else if (_attributeName == "Port") {
        unsigned int count = engineManager_->stats()->portCount();
        ostringstream s;
        s << count;
        return s.str();
    } else if (_attributeName == "Truck terminal") {
        unsigned int count = engineManager_->stats()->truckTerminalCount();
        ostringstream s;
        s << count;
        return s.str();
    } else if (_attributeName == "Boat terminal") {
        unsigned int count = engineManager_->stats()->boatTerminalCount();
        ostringstream s;
        s << count;
        return s.str();
    } else if (_attributeName == "Plane terminal") {
        unsigned int count = engineManager_->stats()->planeTerminalCount();
        ostringstream s;
        s << count;
        return s.str();
    } else if (_attributeName == "Truck segment") {
        int count = engineManager_->stats()->truckSegmentCount();
        ostringstream s;
        s << count;
        return s.str();
    } else if (_attributeName == "Boat segment") {
        int count = engineManager_->stats()->boatSegmentCount();
        ostringstream s;
        s << count;
        return s.str();
    } else if (_attributeName == "Plane segment") {
        int count = engineManager_->stats()->planeSegmentCount();
        ostringstream s;
        s << count;
        return s.str();
    } else if (_attributeName == "expedite percentage") {
        ostringstream s;
        s << fltPnt2str(engineManager_->stats()->expeditedPercentage().value());
        return s.str();
    } else {
        cerr << "StatsRep::attribute: " << _attributeName << " is an invalid attribute." << endl;
        return "";
    }
};

void StatsRep::attributeIs(const string& name, const string& v) {
    FWK_DEBUG("StatsRep::attributeIs with name: " << name << " and v: " << v);
};
