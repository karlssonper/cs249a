/*
 * RouteTable.h
 *
 *  Created on: Dec 2, 2011
 *      Author: per
 */

#ifndef ROUTETABLE_H_
#define ROUTETABLE_H_

#include <map>
#include "PtrInterface.h"
#include "Ptr.h"
#include <string>

using std::map;
using std::string;

namespace Shipping {
class Location;
class Segment;
class ShortestDistance;

class RouteTable : public Fwk::PtrInterface<RouteTable>{
public:
    enum Routing {
        breadthFirstSearch, djikstras
    };
    RouteTable(Routing, map<string, Fwk::Ptr<Location const> > *
            , map<string, Fwk::Ptr<Segment const> > *);
private:
    map<string,  Fwk::Ptr<ShortestDistance> > table_;
    RouteTable();
    RouteTable(const RouteTable & );
};
};
#endif /* ROUTETABLE_H_ */
