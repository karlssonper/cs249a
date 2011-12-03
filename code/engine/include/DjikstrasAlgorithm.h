/*
 * DjikstrasAlgorithm.h
 *
 *  Created on: Dec 2, 2011
 *      Author: per
 */

#ifndef DJIKSTRASALGORITHM_H_
#define DJIKSTRASALGORITHM_H_

#include "Ptr.h"
#include <map>
#include <string>

namespace Shipping {
class Location;
class Segment;
class ShortestDistance;
class DjikstrasAlgorithm {
public:
    DjikstrasAlgorithm(std::map<std::string, Fwk::Ptr<Location const> > *,
                       std::map<std::string, Fwk::Ptr<Segment const> > *);
    Fwk::Ptr<ShortestDistance> shortestDistance(const std::string &);
private:
    DjikstrasAlgorithm();
    DjikstrasAlgorithm(const DjikstrasAlgorithm &);
    std::map<std::string, Fwk::Ptr<Location const> > * graphLocation_;
    std::map<std::string, Fwk::Ptr<Segment const> > * graphSegment_;
};
};
#endif /* DJIKSTRASALGORITHM_H_ */
