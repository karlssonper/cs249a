/*
 * DjikstrasAlgorithm.cpp
 *
 *  Created on: Dec 2, 2011
 *      Author: per
 */

#include "DjikstrasAlgorithm.h"
#include "ShortestDistance.h"
#include "Location.h"
#include <set>
using namespace Shipping;
DjikstrasAlgorithm::DjikstrasAlgorithm(
        std::map<std::string, Location::PtrConst > * _graphLocation,
        std::map<std::string, Segment::PtrConst > * _graphSegment) :
        graphLocation_(_graphLocation), graphSegment_(_graphSegment) {
};

ShortestDistance::Ptr DjikstrasAlgorithm::shortestDistance(
        const std::string & source){
    ShortestDistance::Ptr s = new ShortestDistance();
    const unsigned int size = graphLocation_->size();

    //Djikstras!

    Miles * dist = new Miles[size];
    std::map<std::string, Location::PtrConst > prev;
    std::string * intToName = new std::string[size];
    std::map<std::string, unsigned int> nameToInt;
    std::map<std::string, Location::PtrConst >::const_iterator it =
            graphLocation_->begin();
    std::set<unsigned int> Q;
    for (unsigned int i = 0; i < size; ++i, ++it) {
        Q.insert(i);
        intToName[i] = it->second->name();
        nameToInt[it->second->name()] = i;
        prev[it->second->name()] = NULL;
        if (it->second->name() == source)
            dist[i] = 0;
        else
            dist[i] = Miles::max();
    }

    while (!Q.empty()) {
        Miles minDist = Miles::max();
        unsigned int u;
        for (unsigned int i = 0; i < size; ++i) {
            if (dist[i] < minDist) {
                u = i;
                minDist = dist[u];
            }
        }
        if (minDist == Miles::max()) break;
        Q.erase(u);
        Location::PtrConst loc = graphLocation_->operator [](intToName[u]);
        Location::OutSegmentIteratorConst it = loc->outSegmenterIterConst();
        unsigned int outSegs = loc->outSegments();
        for (unsigned int i = 0; i < outSegs; ++i, ++it) {
            std::string returnStr = (*it)->returnSegment();
            std::string neighborLocStr =
                    graphSegment_->operator [](returnStr)->name();
            if (graphLocation_->find(neighborLocStr) !=graphLocation_->end() ) {
                Miles alt = dist[u].value() + (*it)->length().value();
               unsigned int v = nameToInt[neighborLocStr];
                if (alt < dist[v]){
                    dist[v] = alt;
                    prev[neighborLocStr] = loc;
                }
            }
        }
    }

    for (unsigned int i = 0; i < size; ++i, ++it) {
        if (dist[i] == Miles::max()) continue;
        std::string name = intToName[i];

        Location::PtrConst p = prev[name];
        Location::PtrConst old = graphLocation_->operator [](name);
        while (p->name() != source) {
            old = p;
            p = prev[p->name()];
        }
        s->next[name] = old;
        std::cout << "SOURCE: " << source << " DEST: " << name << " NEXT: " << old->name() << std::endl;
    }

    return s;
};


