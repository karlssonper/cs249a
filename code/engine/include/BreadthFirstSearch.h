/*
 * BreadthFirstSearch.h
 *
 *  Created on: Dec 2, 2011
 *      Author: per
 */

#ifndef BREADTHFIRSTSEARCH_H_
#define BREADTHFIRSTSEARCH_H_

#include "Ptr.h"
#include <map>
#include <string>
namespace Shipping {
class ShortestDistance;
class Location;
class Segment;
class Conn;
class BreadthFirstSearch {
public:
    BreadthFirstSearch(std::map<std::string, Fwk::Ptr<Location const> > *,
                       std::map<std::string, Fwk::Ptr<Segment const> > *,
                       Fwk::Ptr<Conn> );
    Fwk::Ptr<ShortestDistance> shortestDistance( const std::string & source);
private:
    BreadthFirstSearch();
    BreadthFirstSearch(const BreadthFirstSearch &);
    Fwk::Ptr<Conn> conn_;
    std::map<std::string, Fwk::Ptr<Location const> > * graphLocation_;
    std::map<std::string, Fwk::Ptr<Segment const> > * graphSegment_;
};
};

#endif /* BREADTHFIRSTSEARCH_H_ */
