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
RouteTable::RouteTable(Routing _routing,
        map<string, Location::PtrConst> * _graphLocation,
        map<string, Segment::PtrConst> * _graphSegment){
    switch(_routing) {
        case breadthFirstSearch: {

            break;
        }
        case djikstras : {
            DjikstrasAlgorithm d(_graphLocation, _graphSegment);
            map<string, Location::PtrConst>::iterator it =
                    _graphLocation->begin();
            while(it != _graphLocation->end()) {
                const std::string name = it->second->name();
                table_[name] = d.shortestDistance(name);
                ++it;
                std::cout << "snopp, hihi" << std::endl;
            }
            break;
        }
    }
};
