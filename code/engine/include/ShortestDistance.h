/*
 * ShortestDistance.h
 *
 *  Created on: Dec 2, 2011
 *      Author: per
 */

#ifndef SHORTESTDISTANCE_H_
#define SHORTESTDISTANCE_H_

#include "PtrInterface.h"
#include "Ptr.h"
#include <map>
#include <list>
#include <string>
namespace Shipping {
class Location;
class ShortestDistance  : public Fwk::PtrInterface<ShortestDistance> {
public:
    typedef Fwk::Ptr<ShortestDistance const> PtrConst;
    typedef Fwk::Ptr<ShortestDistance> Ptr;
    std::map<std::string, Fwk::Ptr<Location const> > next;
};
}
#endif /* SHORTESTDISTANCE_H_ */
