#include <string>
#include <ostream>
#include <iostream>
#include <string>
#include "Debug.h"
#include "Instance.h"

using std::cout;
using std::cerr;
using std::endl;
using std::string;

int main(int argc, char *argv[]) {
    FWK_DEBUG("Example.cpp LIVE");
    Ptr<Instance::Manager> manager = shippingInstanceManager();

    if (manager == NULL) {
        cerr << "Unexpected NULL manager." << endl;
        return 1;
    }

    Ptr<Instance> stats = manager->instanceNew("myStats", "Stats");

    if (stats == NULL) {
        cerr << "Unexpected NULL stats." << endl;
        return 1;
    }

    Ptr<Instance> fleet = manager->instanceNew("myFleet", "Fleet");

    if (fleet == NULL) {
        cerr << "Unexpected NULL." << endl;
        return 1;
    }

    fleet->attributeIs("Boat, speed", "60");
    FWK_DEBUG("");
    fleet->attributeIs("Truck, capacity", "50");
    FWK_DEBUG("");
    fleet->attributeIs("Plane, cost", "20");
    FWK_DEBUG("");
    cout << "fleet->attribute('Boat, speed'): " << fleet->attribute("Boat, speed") << endl;
    FWK_DEBUG("");
    // --- Create instances
    // -- Locations
    // customers
    Ptr<Instance> customer1 = manager->instanceNew("customer1", "Customer");  
    FWK_DEBUG("");
    Ptr<Instance> customer2 = manager->instanceNew("customer2", "Customer");  
    FWK_DEBUG("");
    // ports
    Ptr<Instance> port1 = manager->instanceNew("port1", "Port");  
    FWK_DEBUG("");

    if (customer1 == NULL || customer2 == NULL || port1 == NULL) {
        cerr << "Unexpected NULL customer or port." << endl;
	return 1;
    }

    // -- Segments
    // boat
    Ptr<Instance> boatSeg1 = manager->instanceNew("boatSeg1", "Boat segment");  FWK_DEBUG("");
    Ptr<Instance> boatSeg2 = manager->instanceNew("boatSeg2", "Boat segment");  FWK_DEBUG("");
    // truck
    Ptr<Instance> truckSeg1 = manager->instanceNew("truckSeg1", "Truck segment");  FWK_DEBUG("");
    Ptr<Instance> truckSeg2 = manager->instanceNew("truckSeg2", "Truck segment");  FWK_DEBUG("");

    if (boatSeg1 == NULL || boatSeg2 == NULL || truckSeg1 == NULL || truckSeg2 == NULL) {
        cerr << "Unexpected NULL segment." << endl; FWK_DEBUG("");
        return 1;
    }

    // connections
    // customer1 <---> port1
    truckSeg1->attributeIs("source", "customer1"); FWK_DEBUG("");
    truckSeg2->attributeIs("source", "port1"); FWK_DEBUG("");
    truckSeg1->attributeIs("return segment", "truckSeg2"); FWK_DEBUG("");
    cout << "truckSeg1->attribute('source'): " << truckSeg1->attribute("source") << endl; FWK_DEBUG("");
    
    // customer2 <---> port1
    boatSeg1->attributeIs("source", "customer2"); FWK_DEBUG("");
    boatSeg2->attributeIs("source", "port1"); FWK_DEBUG("");
    boatSeg1->attributeIs("return segment", "boatSeg2"); FWK_DEBUG("");
    cout << "boatSeg1->attribute('return segment'): " << boatSeg1->attribute("return segment") << endl; FWK_DEBUG("");

    // -- Segment lengths
    boatSeg1->attributeIs("length", "400"); FWK_DEBUG("");
    boatSeg2->attributeIs("length", "400"); FWK_DEBUG("");
    truckSeg1->attributeIs("length", "900"); FWK_DEBUG("");
    truckSeg2->attributeIs("length", "900"); FWK_DEBUG("");

    // -- Segment difficulties
    boatSeg1->attributeIs("difficulty", "1"); FWK_DEBUG("");
    boatSeg2->attributeIs("difficulty", "1"); FWK_DEBUG("");
    truckSeg1->attributeIs("difficulty", "1"); FWK_DEBUG("");
    truckSeg2->attributeIs("difficulty", "1"); FWK_DEBUG("");
    
    // -- Segment expedite support
    boatSeg1->attributeIs("expedite support", "yes"); FWK_DEBUG("");
    boatSeg2->attributeIs("expedite support", "yes"); FWK_DEBUG("");
    truckSeg1->attributeIs("expedite support", "yes"); FWK_DEBUG("");
    truckSeg2->attributeIs("expedite support", "yes"); FWK_DEBUG("");

    // -- Connectivity queries
    Ptr<Instance> conn = manager->instanceNew("myConn", "Conn"); FWK_DEBUG("");

    if (conn == NULL) {
        cerr << "Unexpected NULL conn." << endl;
        return 1;
    }

    cout << "**** explore customer1 : distance 1500 ****" << endl; FWK_DEBUG("");
    cout << conn->attribute("explore customer1 : distance 1500") << endl; FWK_DEBUG("");
    FWK_DEBUG("");

    cout << "*** connect customer2 : customer1 ****" << endl; FWK_DEBUG("");
    cout << conn->attribute("connect customer2 : customer1") << endl; FWK_DEBUG("");
    FWK_DEBUG("");

    // -- Statistics queries
    cout << "===== Stats attributes =====" << endl; 
    cout << " --- Segments --- " << endl;
    cout << "# Truck segments : " << stats->attribute("Truck segment") << endl; 
    cout << "Expediting %     : " << stats->attribute("expedite percentage") << endl;
    cout << " --- Terminals --- " << endl; FWK_DEBUG("");
    cout << "# Plane terminals: " << stats->attribute("Plane terminal") << endl; 
    cout << " --- Ports and customers --- " << endl;
    cout << "# Ports          : " << stats->attribute("Port") << endl;

    cerr << "Done!" << endl; 

    return 0;

}