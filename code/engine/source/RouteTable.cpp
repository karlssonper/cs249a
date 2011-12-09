/*
 * RouteTable.cpp
 *
 *  Created on: Dec 2, 2011
 *      Author: per
 */

#include "RouteTable.h"
#include "DjikstrasAlgorithm.h"
#include "BreadthFirstSearch.h"
#include "ShortestDistance.h"
#include "Location.h"
#include "Segment.h"
#include "Output.h"
#include "Conn.h"

using namespace Shipping;
RouteTable::RouteTable(
        map<string, Location::PtrConst> * _graphLocation,
        map<string, Segment::PtrConst> * _graphSegment,
        Conn * _conn) :
        graphSegment_(_graphSegment),
        graphLocation_(_graphLocation),
        conn_(_conn),
        status_(needsUpdate), latestUpdate_(performDjikstras){
};

void RouteTable::statusIs(Status s) {
    if (s != status_)
        status_ = s;
    if (status_  == performDjikstras || status_  == performBFS) {
        latestUpdate_ = status_;
        updateRouteTable();
    }
};

Location::PtrConst RouteTable::nextLocation (Location::PtrConst cur,
        Location::PtrConst dest){
    if (status() != updated) updateRouteTable();
    Location::PtrConst next;
    if (table_[cur->name()]->next.find(dest->name()) != 
        table_[cur->name()]->next.end()) {
        next = table_[cur->name()]->next[dest->name()];
    } else {
        //error cur cant reach dest
    }

    Segment::PtrConst out;
    Location::OutSegmentIteratorConst it = cur->outSegmenterIterConst();
    for (int i =0; i < cur->outSegments(); ++i, ++it) {
        std::map<string, Fwk::Ptr<Segment const> >::iterator e =
            graphSegment_->end();
        if (graphSegment_->find((*it)->returnSegment()) != e) {
            Segment::PtrConst r = graphSegment_->at((*it)->returnSegment());
            if (r->source() == next->name()){
                out = *it;
                break;
            }
        } else {
            //error;
        }
    };

    std::cout << "Active packages: "  << out->activePackages().value() << 
        std::endl;
    std::cout << "Capacity: "  << out->capacity().value() << std::endl;

    if (out->activePackages() != out->capacity()) {
        return next;
    } else {
        addRS(out);
        Miles minDist = Miles::max();
        it = cur->outSegmenterIterConst();
        for (int i =0; i < cur->outSegments(); ++i, ++it) {
            std::map<string, Fwk::Ptr<Segment const> >::iterator e = 
                graphSegment_->end();
            if (graphSegment_->find((*it)->returnSegment()) != e) {
                Segment::PtrConst r = graphSegment_->at((*it)->returnSegment());
                if (r->source() == next->name()) continue;
                Location::PtrConst nl = graphLocation_->at(r->source());
                if (table_[nl->name()]->next.find(dest->name()) != 
                    table_[nl->name()]->next.end()) {
                    if ((*it)->length() < minDist && (*it)->source() != 
                        cur->name()) {
                        minDist = (*it)->length();
                        next = graphLocation_->at((*it)->source());
                    }
                }
            } else {
                //error;
            }
        };
    }

    return next;
    };

    void 
    RouteTable::addRS(Segment::PtrConst s) {
    const_cast<Segment*>(s.ptr())->refusedShipmentsInc();
}

void RouteTable::updateRouteTable() {
    switch(latestUpdate_) {
        case performBFS: {
            FWK_DEBUG("BFS d(graphLocation_, graphSegment_);");
            BreadthFirstSearch d(graphLocation_, graphSegment_, conn_);
            map<string, Location::PtrConst>::iterator it =
                    graphLocation_->begin();
            while(it != graphLocation_->end()) {
                const std::string name = it->second->name();
                table_[name] = d.shortestDistance(name);
                ++it;
            }
            break;
        }
        case performDjikstras : {
            FWK_DEBUG("DjikstrasAlgorithm d(graphLocation_, graphSegment_);");
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
