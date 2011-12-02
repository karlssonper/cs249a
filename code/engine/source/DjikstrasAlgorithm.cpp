/*
 * DjikstrasAlgorithm.cpp
 *
 *  Created on: Dec 2, 2011
 *      Author: per
 */

#include "DjikstrasAlgorithm.h"
#include "Location.h"
using namespace Shipping;
DjikstrasAlgorithm::DjikstrasAlgorithm(
        std::map<std::string, Location::PtrConst > * _graphLocation) :
        graphLocation_(_graphLocation) {

};
