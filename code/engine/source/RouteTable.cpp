/*
 * RouteTable.cpp
 *
 *  Created on: Dec 2, 2011
 *      Author: per
 */

#include "RouteTable.h"
#include "ShortestDistance.h"
#include "DjikstrasAlgorithm.h"
#include "Location.h"
#include "Segment.h"
using namespace Shipping;
RouteTable::RouteTable(
        map<string, Location::PtrConst> * _graphLocation,
        map<string, Segment::PtrConst> * _graphSegment) :
        graphSegment_(_graphSegment),
        graphLocation_(_graphLocation),
        status_(needsUpdate), latestUpdate_(performDjikstras){
};

void RouteTable::statusIs(Status s) {
    if (s != status_)
        status_ = s;
    if (status_  == performDjikstras || status_  == performDFS) {
        latestUpdate_ = status_;
        updateRouteTable();
    }
};

Location::PtrConst RouteTable::nextLocation (Location::PtrConst cur,
        Location::PtrConst dest){
    if (status() != updated) updateRouteTable();
    Location::PtrConst next = table_[cur->name()]->next[dest->name()];

/*
    Segment::PtrConst out;
    Location::OutSegmentIteratorConst it = cur->outSegmenterIterConst();
    for (int i =0; i < cur->outSegments(); ++i) {
        Segment::PtrConst r =graphSegment_->at((*it)->returnSegment());
        if (r->source() == next->name()){
            out = *it;
            break;
        }
    };*/
    return next;
};

void RouteTable::updateRouteTable() {
    switch(latestUpdate_) {
        case performDFS: {

            break;
        }
        case performDjikstras : {
            DjikstrasAlgorithm d(graphLocation_, graphSegment_);
            map<string, Location::PtrConst>::iterator it =
                    graphLocation_->begin();
            while(it != graphLocation_->end()) {
                const std::string name = it->second->name();
                table_[name] = d.shortestDistance(name);
                ++it;
            }
            break;
        }
    }
    status_ = updated;
};
