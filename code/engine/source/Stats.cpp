/*
* Stats.cpp
*
*  Created on: Nov 4, 2011
*      Author: per
*/

#include "Stats.h"
#include "Debug.h"
#include "Engine.h"

using namespace Shipping;

Stats::Stats(std::string & _name, 
             const EngineManager * _owner,
             EntityManager  * _notifier) :
             EntityManager::Notifiee(_name, _notifier), 
             owner_(_owner),
             customerCount_(0),
             portCount_(0),
             boatTerminalCount_(0),
             planeTerminalCount_(0),
             truckTerminalCount_(0),
             truckSegmentCount_(0),
             boatSegmentCount_(0),
             planeSegmentCount_(0),
             totalSegmentCount_(0),
             expeditedSupportCount_(0),
             expeditedPercentage_(0.0) {
        FWK_DEBUG("Stats constructor with name " << _name);

}

Stats::Ptr Stats::StatsNew(std::string _name, 
    const EngineManager * _owner,
    EntityManager * _entityManager) {
        FWK_DEBUG("Stats::StatsNew with name " << _name);
        Ptr p = new Stats(_name, _owner, _entityManager);
        return p;
};

Stats::~Stats() {
    FWK_DEBUG("Stats::~Stats() with name: " << name());
}

void Stats::onSegmentNew(Segment::PtrConst _p) {
    FWK_DEBUG("Stats::onSegmentNew(" << _p->name() << ")");
    if (_p->type() == Segment::boatSegment()) {
        boatSegmentCount_++;
    } else if (_p->type() == Segment::truckSegment()) {
        truckSegmentCount_++;
    } else if (_p->type() == Segment::planeSegment()) {
        planeSegmentCount_++;
    }

    if (_p->expediteSupport() == Segment::fullExpediteSupport()) {
        expeditedSupportCount_++;
    }
    totalSegmentCount_++;
    updateExpPercentage();
}

void Stats::onSegmentDel(Segment::PtrConst _p) {

    FWK_DEBUG("Stats::onSegmentDel(" << _p->name() << ")");

    if (_p->type() == Segment::boatSegment()) {
        boatSegmentCount_--;
    } else if (_p->type() == Segment::truckSegment()) {
        truckSegmentCount_--;
    } else if (_p->type() == Segment::planeSegment()) {
        planeSegmentCount_--;
    }

    if (_p->expediteSupport() == Segment::fullExpediteSupport()) {
        expeditedSupportCount_--;
    };
    totalSegmentCount_--;
    updateExpPercentage();
}

void Stats::onSegmentExpUpdate(Segment::PtrConst _p) {
    FWK_DEBUG("Stats::onSegmentUpdate with " << _p->name());
    if (_p->expediteSupport() == Segment::fullExpediteSupport()) {
        expeditedSupportCount_++;
    } else {
        expeditedSupportCount_--;
    }
    updateExpPercentage();
}

void Stats::onLocationNew(Location::PtrConst _p) {
    FWK_DEBUG("Stats::onLocationNew(" << _p->name() << ")");
    if (_p->type() == Location::customer()) {
        customerCount_++;
    } else if (_p->type() == Location::port()) {
        portCount_++;
    } else if (_p->type()  == Location::truckTerminal()) {
        truckTerminalCount_++;
    } else if (_p->type()  == Location::boatTerminal()) {
        boatTerminalCount_++;
        FWK_DEBUG("boatTerminalCount_: " << boatTerminalCount_);
    } else if (_p->type()  == Location::planeTerminal()) {
        planeTerminalCount_++;
    }
}

void Stats::onLocationDel(Location::PtrConst _p) {
    FWK_DEBUG("Stats::onLocationDel(" << _p->name() << ")");
    if (_p->type()  == Location::customer()) {
        customerCount_--;
    } else if (_p->type()  == Location::port()) {
        portCount_--;
    } else if (_p->type()  == Location::truckTerminal()) {
        truckTerminalCount_--;
    } else if (_p->type()  == Location::boatTerminal()) {
        boatTerminalCount_--;
    } else if (_p->type()  == Location::planeTerminal()) {
        planeTerminalCount_--;
    }
}

void Stats::updateExpPercentage() {
    FWK_DEBUG("Updating exp percentage on " << name());
    double tot = totalSegmentCount_;
    double exp = expeditedSupportCount_;
    double perc = 100.0*exp/tot;
    expeditedPercentage_ = ExpeditedPercentage(perc);
}