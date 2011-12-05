/*
 * BreadthFirstSearch.cpp
 *
 *  Created on: Dec 2, 2011
 *      Author: per
 */

#include "BreadthFirstSearch.h"
#include "ShortestDistance.h"
#include "Location.h"
#include "Segment.h"
#include "Conn.h"
using namespace Shipping;

BreadthFirstSearch::BreadthFirstSearch(
        std::map<std::string, Location::PtrConst > * _graphLocation,
        std::map<std::string, Segment::PtrConst > * _graphSegment,
        Conn::Ptr _conn) :
        graphLocation_(_graphLocation), graphSegment_(_graphSegment),
        conn_(_conn){
};

ShortestDistance::Ptr BreadthFirstSearch::shortestDistance(
        const std::string & source){
    ShortestDistance::Ptr s = new ShortestDistance();
    std::map<std::string, Location::PtrConst >::iterator lIt = 
        graphLocation_->begin();
    while (lIt != graphLocation_->end()) {
        if (lIt->second->name() == source) {
            ++lIt;
            continue;
        }
        PathTree::Ptr p = conn_->connect(source, lIt->second->name());
        PathTree::PathIteratorConst it = p->pathIterConst();   
        Miles minDist = Miles::max();
        Location::PtrConst next;
        for (unsigned int i = 0; i < p->paths(); ++i, ++it){
            Path::PathItemIteratorConst pit = (*it)->pathItemIterConst();
            //cout << "source: " << source << " dest: " << lIt->second->name() << std::endl;
            Miles dist = 0;
            for (unsigned int j = 0; j < (*it)->pathItems(); ++j, ++pit){
                if (pit->seg){
                    dist = dist.value() + pit->seg->length().value();
                }
                //cout << pit->loc->name() << " ";
            }
            //std::cout << std::endl ;
            if (dist < minDist) {
                minDist = dist;
                Path::PathItemIteratorConst temp = (*it)->pathItemIterConst();
                ++temp;
                next = temp->loc;
            }
        }
        s->next[lIt->second->name()] = next;
        FWK_DEBUG("SOURCE: " << source << " DEST: " << lIt->second->name() << " NEXT: " <<
            next->name() << " DIST : " << minDist.value());
        ++lIt;
    };
    return s;
}