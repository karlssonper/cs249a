/*
 * Conn.cpp
 *
 *  Created on: Nov 4, 2011
 *      Author: per
 */

#include "Conn.h"
#include "Debug.h"
#include <queue>
#include "Engine.h"
#include "RouteTable.h"
#include "Exception.h"
using namespace Shipping;

Conn::Conn(std::string & _name, const EngineManager * _owner,
        EntityManager  * _notifier) :
        EntityManager::Notifiee(_name, _notifier), owner_(_owner)
{
    routeTable_ = new RouteTable(&graphLocation_, &graphSegment_);
    FWK_DEBUG("Constructing Conn objec with name " << _name);
};

Conn::~Conn(){
    FWK_DEBUG("Conn::Conn() with name: " << name());
};

void Conn::routingIs(Routing _routing){
    FWK_DEBUG("Conn::routingIs() with name: " << name());
    if (routing_ != _routing) {
        FWK_DEBUG("Conn::routingIs() routing_ = _routing ");
        routing_ = _routing;
    }
    if (routing_ == djikstras) {
        FWK_DEBUG("Conn::routingIs() routeTable_->statusIs(RouteTable::performDjikstras)");
        routeTable_->statusIs(RouteTable::performDjikstras);
    } else if (routing_ == breadthFirstSearch) {
        routeTable_->statusIs(RouteTable::performDFS);
    }
};

PathTree::Ptr Conn::explore(string locStr, ExploreData ed){
    FWK_DEBUG("Conn::explore() with startLoc: " << locStr);
    if (graphLocation_.find(locStr) == graphLocation_.end()) return NULL;
    Location::PtrConst root = graphLocation_[locStr];
    PathTree::Ptr p = new ExplorePathTree(ed, root, this);   
    return p;
};

PathTree::Ptr Conn::connect(string loc0, string loc1){
    FWK_DEBUG("Conn::connect() with startLoc: " << loc0<< " and end: " << loc1);
    if (graphLocation_.find(loc0) == graphLocation_.end() ||
        graphLocation_.find(loc1) == graphLocation_.end()) {
            FWK_DEBUG("Conn::connect(): location not found in graphLocation_.");
            return NULL;
    }
    Location::PtrConst root = graphLocation_[loc0];
    Location::PtrConst end = graphLocation_[loc1];
    PathTree::Ptr p = new ConnectPathTree(root, end,this);   
    return p;
};

void Conn::onSegmentDel(Segment::PtrConst seg0){
    FWK_DEBUG("Conn::onSegmentDel() with name: " << seg0->name());
    if (graphSegment_.find(seg0->name()) == graphSegment_.end()){
        FWK_DEBUG("Conn::onSegmentDel() did not find any segment called "
            << seg0->name() << " in the graph");
        return;
    }
    removeGraphSegment(seg0);
    if (seg0->returnSegment() != "")
        removeGraphSegment(graphSegment_[seg0->returnSegment()]);
};

void Conn::removeGraphSegment(Segment::PtrConst seg) {
    FWK_DEBUG("Conn::removeGraphSegment() with name: " << seg->name());
    graphSegment_.erase(seg->name());
    if (graphLocation_.find(seg->source()) != graphLocation_.end())
       removeGraphLocation(graphLocation_[seg->source()]);
};

void Conn::removeGraphLocation(Location::PtrConst loc) {
    FWK_DEBUG("Conn::removeGraphLocation() with name: " << loc->name());
    Location::OutSegmentIteratorConst it = loc->outSegmenterIterConst();
    for (unsigned int i = 0; i < loc->outSegments(); ++i, it++){
        if ( graphSegment_.find((*it)->name()) != graphSegment_.end()) return;
    };
    graphLocation_.erase(loc->name());
    routeTable_->statusIs(RouteTable::needsUpdate);
};

void Conn::onLocationDel(Location::PtrConst loc) {
    FWK_DEBUG("Conn::removeGraphLocation() with name: " << loc->name());
    Location::OutSegmentIteratorConst it = loc->outSegmenterIterConst();
    for (unsigned int i = 0; i < loc->outSegments(); ++i, it++){
        if ( graphSegment_.find((*it)->name()) != graphSegment_.end()){ 
            removeGraphSegment(*it);
            removeGraphSegment(graphSegment_[(*it)->returnSegment()]);
        }
    };
};

void Conn::onLocationShipmentNew(Location::PtrConst _cur,
        Shipment::Ptr _shipment) {
    FWK_DEBUG("Conn::onLocationShipmentNew() with name: " << _cur->name());

    Location::PtrConst next =
            routeTable_->nextLocation(_cur, _shipment->destination());
    Segment::PtrConst out;
    Location::OutSegmentIteratorConst it = _cur->outSegmenterIterConst();
    for (int i =0; i < _cur->outSegments(); ++i) {
        Segment::PtrConst r = graphSegment_.at((*it)->returnSegment());
        if (r->source() == next->name()){
            out = *it;
            break;
        }
    }
    Segment * s = const_cast<Segment *> (out.ptr());
    Location::Ptr p =  const_cast<Location *>(next.ptr());
    s->shipmentEnq(_shipment,p);
};

void Conn::onSegmentUpdate(Segment::PtrConst seg0) {
    FWK_DEBUG("Conn::onSegmentUpdate() with name: " << seg0->name());
    if (graphSegment_.find(seg0->name()) == graphSegment_.end()){
        FWK_DEBUG("Conn::onSegmentUpdate() did not find any segment called "
            << seg0->name() << " in the graph");
        if (isInsertable(seg0) == insertable_){
            Segment::PtrConst seg1 = owner_->entityManager()->segment(seg0->returnSegment());
            FWK_DEBUG("Conn::onSegmentUpdate() Adding " << seg0->name() << " to graph");
            graphSegment_[seg0->name()] = seg0;
            FWK_DEBUG("Conn::onSegmentUpdate() Adding " << seg1->name() << " to graph");
            graphSegment_[seg1->name()] = seg1;
            if (graphLocation_.find(seg0->source()) == graphLocation_.end()) {
                Location::PtrConst loc0 = owner_->entityManager()->location(seg0->source());
                FWK_DEBUG("Conn::onSegmentUpdate() Adding " << loc0->name() << " to graph");
                graphLocation_[loc0->name()] = loc0;
                routeTable_->statusIs(RouteTable::needsUpdate);
            }
            if (graphLocation_.find(seg1->source()) == graphLocation_.end()){
                Location::PtrConst loc1 = owner_->entityManager()->location(seg1->source());
                FWK_DEBUG("Conn::onSegmentUpdate() Adding " << loc1->name() << " to graph");
                graphLocation_[loc1->name()] = loc1;
                routeTable_->statusIs(RouteTable::needsUpdate);
            }
        } else {
            FWK_DEBUG("Conn::onSegmentUpdate() " << seg0->name() << " is not insertable");
            return;
        }
    }
    if (seg0->source() == ""){
        removeGraphSegment(seg0);
        removeGraphSegment(graphSegment_[seg0->returnSegment()]);
    }
    if (seg0->returnSegment() == ""){
        removeGraphSegment(seg0);
    }
};

void Conn::onLocationUpdate(Location::PtrConst loc){
    FWK_DEBUG("Conn::onLocationUpdate() with name: " << loc->name());
    removeGraphLocation(loc);
};

Conn::Insertable Conn::isInsertable(Segment::PtrConst seg){
    FWK_DEBUG("Conn::isInsertable() with name: " << seg->name());
    if (!owner_->entityManager()->segment(seg->returnSegment())){
        FWK_DEBUG("Conn::isInsertable() Missing Return");
        return missingReturn_;
    }
    if (!owner_->entityManager()->location(seg->source())){
        FWK_DEBUG("Conn::isInsertable() Missing Source");
        return missingSource_;
    }
    if (!owner_->entityManager()->location(
        owner_->entityManager()->segment(
            seg->returnSegment())->source())) {
        FWK_DEBUG("Conn::isInsertable() Missing Return Source");
        return missingReturnSource_;
    }
    FWK_DEBUG("Conn::isInsertable() Insertable");
    return insertable_;
};
