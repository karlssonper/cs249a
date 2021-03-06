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
#include "Exception.h"

using namespace Shipping;

BreadthFirstSearch::BreadthFirstSearch(
    std::map<std::string, Location::PtrConst > * _graphLocation,
    std::map<std::string, Segment::PtrConst > * _graphSegment,
    Conn::Ptr _conn) :
graphLocation_(_graphLocation), graphSegment_(_graphSegment),
    conn_(_conn){
};

ShortestDistance::Ptr BreadthFirstSearch::shortestDistance(
    const std::string & source) {
        ShortestDistance::Ptr s = new ShortestDistance();
        if (!s) {
            std::cerr << "BreadthFirstSearch new() failed" << std::endl;
            throw(Fwk::MemoryException("BreadthFirstSearch::shortestDistance"));
        }
        std::map<std::string, Location::PtrConst >::iterator lIt = 
            graphLocation_->begin();
        while (lIt != graphLocation_->end()) {
            if (lIt->second->name() == source) {
                ++lIt;
                continue;
            }
            PathTree::Ptr p = conn_->connect(source, lIt->second->name());
            PathTree::PathIteratorConst it = p->pathIterConst();   
            Hours minTime = Hours::max();
            Location::PtrConst next;
            for (unsigned int i = 0; i < p->paths(); ++i, ++it){
                Hours time = (*it)->time();
                if (time < minTime) {
                    minTime = time;
                    Path::PathItemIteratorConst temp = 
                        (*it)->pathItemIterConst();
                    ++temp;
                    next = temp->loc;
                }
            }
            s->next[lIt->second->name()] = next;
            ++lIt;
        };
        return s;
}
