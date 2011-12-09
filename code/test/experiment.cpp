#include <string>
#include <ostream>
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include "Debug.h"
#include "Instance.h"
#include "Exception.h"
#include <vector>
#include <stdlib.h>

using std::cout;
using std::cerr;
using std::endl;
using std::string;

int main(int argc, char *argv[]) {
    try {

        /*
        Construct a shipping network with at least four locations, 
        and confirm that shipments move between them as expected. 
        Run tests with different segment capacity values to compare 
        your network under light and heavy congestion. Add a diagram 
        of this network to your README file, and discuss the tests performed. 
        The code for this client should be named verification.cpp.

        In addition, set up a shipping network with 100 sources and 1 destination. 
        The destination should be connected to a terminal, which is in turn connected 
        to 10 terminals, each of which is connected to 10 sources. All connections are 
        via truck segments. Have each source send shipments holding 100 packages to the 
        destination at the normal truck speed. Run the simulation for a while.

        Now, reset the simulation and do the same thing, but vary the shipment sizes 
        (use a randomly chosen shipment size for each source) from 1 package to 1,000 
        packages. Record the results for each case.

        Discuss in your README file the level of shipment delivery 
        refusal observed in each case. The client implementing this test 
        should be submitted as experiment.cpp. We would like you to include 
        whatever statistics you think are relevant to your specific implementation, 
        but at a bare minimum please provide us with the destination's shipments 
        received and average latency, as well as some sort of measure of segment
        performance (an average for each of shipments received and refused, for example).

        */


        Ptr<Instance::Manager> manager = shippingInstanceManager();
        Ptr<Instance> stats = manager->instanceNew("myStats", "Stats");
        Ptr<Instance> conn = manager->instanceNew("myConn", "Conn");
        Ptr<Instance> fleet = manager->instanceNew("myFleet", "Fleet");
        Ptr<Instance> timeManager = manager->instanceNew("timeManager", "Time manager");

        timeManager->attributeIs("time scale", "0.00000001");

        fleet->attributeIs("Boat, speed", "20");
        fleet->attributeIs("Boat, capacity", "1000");
        fleet->attributeIs("Boat, cost", "30");
        fleet->attributeIs("Truck, speed", "60");
        fleet->attributeIs("Truck, capacity", "50");
        fleet->attributeIs("Truck, cost", "20");
        fleet->attributeIs("Plane, speed", "700");
        fleet->attributeIs("Plane, capacity", "200");
        fleet->attributeIs("Plane, cost", "60");

        std::map<string, Ptr<Instance> > terminals;
        std::map<string, Ptr<Instance> > segments;
        std::map<string, Ptr<Instance> > sources;

        Ptr<Instance> destination = manager->instanceNew("destination", "Customer");
        terminals["firstTerminal"] = manager->instanceNew("firstTerminal", "Truck terminal");

        segments["destTermSegA"] = manager->instanceNew("destTermSegA", "Truck segment");
        segments["destTermSegB"] = manager->instanceNew("destTermSegB", "Truck segment");
        segments["destTermSegA"]->attributeIs("source", "destination");
        segments["destTermSegB"]->attributeIs("source", "firstTerminal");
        segments["destTermSegA"]->attributeIs("return segment", "destTermSegB");
        segments["destTermSegA"]->attributeIs("length", "10");
        segments["destTermSegB"]->attributeIs("length", "10");
        segments["destTermSegA"]->attributeIs("capacity", "300");
        segments["destTermSegB"]->attributeIs("capacity", "300");

        // create the first layer of terminals
        std::ostringstream s;
        for (int i=0; i<10; ++i) {
            s.str("");
            string terminalName = "truckTerminal";
            s << i;
            terminalName.append(s.str());
            terminals[terminalName] = manager->instanceNew(terminalName, "Truck terminal");
            string segmentNameA = "firstLayerSegA";
            segmentNameA.append(s.str());
            string segmentNameB = "firstLayerSegB";
            segmentNameB.append(s.str());
            segments[segmentNameA] = manager->instanceNew(segmentNameA, "Truck segment");
            segments[segmentNameB] = manager->instanceNew(segmentNameB, "Truck segment");
            segments[segmentNameA]->attributeIs("source", "firstTerminal");
            segments[segmentNameB]->attributeIs("source", terminalName);
            segments[segmentNameA]->attributeIs("return segment", segmentNameB);
            segments[segmentNameA]->attributeIs("length", "10");
            segments[segmentNameB]->attributeIs("length", "10");
            segments[segmentNameA]->attributeIs("capacity", "300");
            segments[segmentNameB]->attributeIs("capacity", "300");

            // 10 sources for each terminal
            for (int j=0; j<10; ++j) {

                s.str("");
                int rate = 20;
                s << rate;
                string transferRate = s.str();

                s.str("");
                int size = rand() % 1000 + 1;
                cout << "size: " << size << endl;
                s << size;
                string shipmentSize = s.str();

                s.str("");
                s << i;
                string index = s.str();
                s.str("");
                s << j;
                index.append(s.str());

                string sourceName = "source";
                sourceName.append(index);
                sources[sourceName] = manager->instanceNew(sourceName, "Customer");
                sources[sourceName]->attributeIs("transfer rate", transferRate);
                sources[sourceName]->attributeIs("shipment size", shipmentSize);
                sources[sourceName]->attributeIs("destination", "destination");

                string segmentNameA = "secondLayerSegA";
                segmentNameA.append(index);
                string segmentNameB = "secondLayerSegB";
                segmentNameB.append(index);
                segments[segmentNameA] = manager->instanceNew(segmentNameA, "Truck segment");
                segments[segmentNameB] = manager->instanceNew(segmentNameB, "Truck segment");
                segments[segmentNameA]->attributeIs("source", terminalName);
                segments[segmentNameB]->attributeIs("source", sourceName);
                segments[segmentNameA]->attributeIs("return segment", segmentNameB);
                segments[segmentNameA]->attributeIs("length", "10");
                segments[segmentNameB]->attributeIs("length", "10");
                segments[segmentNameA]->attributeIs("capacity", "300");
                segments[segmentNameB]->attributeIs("capacity", "300");
            }
        }

        timeManager->attributeIs("simulation end", "10");

        // print some stats
        cout << endl;
        cout << "STATS:" << endl;
        cout << "Destination shipments recieved: " << destination->attribute("shipments recieved") << endl;
        cout << "Destination average latency: " << destination->attribute("average latency") << endl;

        float averageRefused = 0;
        std::map<string, Ptr<Instance> >::iterator segIt;
        for (segIt = segments.begin(); segIt != segments.end(); segIt++) {
            float refused = atof(segIt->second->attribute("shipments refused").c_str());
            averageRefused += refused;
        }

        cout << "Average refused shipments: " << averageRefused << endl;
        

    } catch (Fwk::Exception e) {
        std::cerr << "Exception in main: " << e.what() << std::endl;
    }
    return 0;
}