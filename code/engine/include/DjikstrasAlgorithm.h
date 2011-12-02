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
class DjikstrasAlgorithm {
public:
    DjikstrasAlgorithm(std::map<std::string, Fwk::Ptr<Location const> > *);
private:
    DjikstrasAlgorithm();
    DjikstrasAlgorithm(const DjikstrasAlgorithm &);
    std::map<std::string, Fwk::Ptr<Location const> > * _graphLocation;
};
};
#endif /* DJIKSTRASALGORITHM_H_ */
