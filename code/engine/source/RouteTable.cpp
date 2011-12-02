/*
 * RouteTable.cpp
 *
 *  Created on: Dec 2, 2011
 *      Author: per
 */

#include "RouteTable.h"
#include "Location.h"
using namespace Shipping;

RouteTable::RouteTable(Routing _routing,
        map<string, Location::PtrConst> * _graphLocation){
    switch(_routing) {
        case breadthFirstSearch:

            break;
        case djikstras :

            break;
        }
};
