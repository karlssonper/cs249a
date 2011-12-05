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
class Conn;
class RouteTable : public Fwk::PtrInterface<RouteTable>{
public:
    enum Status{
        needsUpdate, performDjikstras, performBFS, updated
    };
    RouteTable(map<string, Fwk::Ptr<Location const> > *,
             map<string, Fwk::Ptr<Segment const> > *,
             Conn *);
    Fwk::Ptr<Location const> nextLocation (Fwk::Ptr<Location const>,Fwk::Ptr<Location const>);

    Status status() const { return status_;};
    void statusIs(Status s);
private:
    map<string, Fwk::Ptr<Segment const> > * graphSegment_;
    map<string, Fwk::Ptr<Location const> > * graphLocation_;
    map<string,  Fwk::Ptr<ShortestDistance> > table_;
    Fwk::Ptr<Conn> conn_;
    Status status_;
    Status latestUpdate_;
    RouteTable();
    RouteTable(const RouteTable & );
    void updateRouteTable();
};
};
#endif /* ROUTETABLE_H_ */
