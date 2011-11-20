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
    Ptr<Instance> conn = manager->instanceNew("myConn", "Conn");
    Ptr<Instance> fleet = manager->instanceNew("myFleet", "Fleet");
    fleet->attributeIs("Boat, speed", "20");
    fleet->attributeIs("Boat, capacity", "1000");
    fleet->attributeIs("Boat, cost", "30");
    fleet->attributeIs("Truck, speed", "60");
    fleet->attributeIs("Truck, capacity", "50");
    fleet->attributeIs("Truck, cost", "20");
    fleet->attributeIs("Plane, speed", "700");
    fleet->attributeIs("Plane, capacity", "200");
    fleet->attributeIs("Plane, cost", "60");

    Ptr<Instance> customer1 = manager->instanceNew("customer1", "Customer");
    Ptr<Instance> port1 = manager->instanceNew("port1", "Port");
    Ptr<Instance> port2 = manager->instanceNew("port2", "Port");
    Ptr<Instance> port3 = manager->instanceNew("port3", "Port");

    Ptr<Instance> planeTerminal1 = manager->instanceNew("planeTerminal1", "Plane terminal");
    Ptr<Instance> truckTerminal1 = manager->instanceNew("truckTerminal1", "Truck terminal");
    Ptr<Instance> boatTerminal1 = manager->instanceNew("boatTerminal1", "Boat terminal");

    Ptr<Instance> planeSegA = manager->instanceNew("planeSegA", "Plane segment");
    Ptr<Instance> planeSegB = manager->instanceNew("planeSegB", "Plane segment");
    Ptr<Instance> planeSegC = manager->instanceNew("planeSegC", "Plane segment");
    Ptr<Instance> planeSegD = manager->instanceNew("planeSegD", "Plane segment");
    Ptr<Instance> planeSegE = manager->instanceNew("planeSegE", "Plane segment");
    Ptr<Instance> planeSegF = manager->instanceNew("planeSegF", "Plane segment");
    Ptr<Instance> planeSegG = manager->instanceNew("planeSegG", "Plane segment");
    Ptr<Instance> planeSegH = manager->instanceNew("planeSegH", "Plane segment");
    Ptr<Instance> planeSegX = manager->instanceNew("planeSegX", "Plane segment");

    Ptr<Instance> truckSegA = manager->instanceNew("truckSegA", "Truck segment");
    Ptr<Instance> truckSegB = manager->instanceNew("truckSegB", "Truck segment");
    Ptr<Instance> truckSegC = manager->instanceNew("truckSegC", "Truck segment");
    Ptr<Instance> truckSegD = manager->instanceNew("truckSegD", "Truck segment");

    Ptr<Instance> truckSegX = manager->instanceNew("truckSegX", "Truck segment");

    Ptr<Instance> boatSegA = manager->instanceNew("boatSegA", "Boat segment");
    Ptr<Instance> boatSegB = manager->instanceNew("boatSegB", "Boat segment");
    Ptr<Instance> boatSegC = manager->instanceNew("boatSegC", "Boat segment");
    Ptr<Instance> boatSegD = manager->instanceNew("boatSegD", "Boat segment");
    Ptr<Instance> boatSegX = manager->instanceNew("boatSegX", "Boat segment");
    Ptr<Instance> boatSegY = manager->instanceNew("boatSegY", "Boat segment");

    planeSegA->attributeIs("return segment", "planeSegB");
    planeSegA->attributeIs("source", "customer1");
    planeSegB->attributeIs("source", "planeTerminal1");
    planeSegA->attributeIs("expedite support", "yes");
    planeSegA->attributeIs("length", "300.0");
    planeSegA->attributeIs("difficulty", "4.0");
    planeSegB->attributeIs("expedite support", "yes");
    planeSegB->attributeIs("length", "400.0");
    planeSegB->attributeIs("difficulty", "2.0");
    
    planeSegC->attributeIs("return segment", "planeSegD");
    planeSegC->attributeIs("source", "planeTerminal1");
    planeSegD->attributeIs("source", "port1");
    planeSegC->attributeIs("length", "800");
    planeSegD->attributeIs("length", "800");

    planeSegE->attributeIs("return segment", "planeSegF");
    planeSegE->attributeIs("source", "planeTerminal1");
    planeSegF->attributeIs("source", "port2");
    planeSegE->attributeIs("length", "1000");
    planeSegF->attributeIs("length", "1200");
    planeSegE->attributeIs("expedite support", "yes");
    planeSegF->attributeIs("expedite support", "yes");

    planeSegG->attributeIs("return segment", "planeSegH");
    planeSegG->attributeIs("source", "port1");
    planeSegH->attributeIs("source", "port2");
    planeSegG->attributeIs("length", "2000");
    planeSegH->attributeIs("length", "2000");

    planeSegX->attributeIs("return segment", "");
    planeSegX->attributeIs("source", "planeTerminal1");

    planeSegX->attributeIs("length", "1337");

    truckSegA->attributeIs("return segment", "truckSegB");
    truckSegA->attributeIs("source", "customer1");
    truckSegA->attributeIs("length", "250");
    truckSegA->attributeIs("difficulty", "4.0");
    truckSegB->attributeIs("length", "250.0");
    truckSegB->attributeIs("difficulty", "4.0");

    truckSegB->attributeIs("source", "truckTerminal1");

    truckSegC->attributeIs("return segment", "truckSegD");
    truckSegC->attributeIs("source", "truckTerminal1");
    truckSegC->attributeIs("expedite support", "yes");
    truckSegD->attributeIs("source", "port1");
    truckSegC->attributeIs("length", "200");
    truckSegD->attributeIs("length", "200");

    truckSegX->attributeIs("source", "port3");
    truckSegX->attributeIs("length", "500");

    boatSegA->attributeIs("return segment", "boatSegB");
    boatSegA->attributeIs("source", "port1");
    boatSegB->attributeIs("source", "boatTerminal1");
    boatSegA->attributeIs("length", "1300");
    boatSegB->attributeIs("length", "1400");

    boatSegC->attributeIs("return segment", "boatSegD");
    boatSegC->attributeIs("source", "boatTerminal1");
    boatSegD->attributeIs("source", "port2");
    boatSegC->attributeIs("length", "900");
    boatSegD->attributeIs("length", "900");

    boatSegX->attributeIs("return segment", "boatSegY");
    boatSegX->attributeIs("source", "customer1");
    boatSegY->attributeIs("source", "");
    boatSegX->attributeIs("length", "200");
    boatSegY->attributeIs("length", "200");

    cout << "LOCATIONS:" << endl;
    cout << "Customers: " << stats->attribute("Customer") << endl;
    cout << "Ports: " << stats->attribute("Port") << endl;
    cout << "Truck terminals: " << stats->attribute("Truck terminal") << endl;
    cout << "Boat terminals: " << stats->attribute("Boat terminal") << endl;
    cout << "Plane terminals: " << stats->attribute("Plane terminal") << endl;
    cout << endl;
    cout << "SEGMENTS:" << endl;
    cout << "Truck segments: " << stats->attribute("Truck segment") << endl;
    cout << "Boat segments: " << stats->attribute("Boat segment") << endl;
    cout << "Plane segments: " << stats->attribute("Plane segment") << endl;
    cout << endl;
    cout << "EXPEDITE SUPPORT:" << endl;
    cout << "Exp %: " << stats->attribute("expedite percentage") << endl;
    cout << endl;
    cout << "FLEET STATS:" << endl;
    cout << "Boat speed: " << fleet->attribute("Boat, speed") << endl;
    cout << "Boat cost: " << fleet->attribute("Boat, cost") << endl;
    cout << "Boat capacity: " << fleet->attribute("Boat, capacity") << endl;
    cout << "Plane speed: " << fleet->attribute("Plane, speed") << endl;
    cout << "Plane cost: " << fleet->attribute("Plane, cost") << endl;
    cout << "Plane capacity: " << fleet->attribute("Plane, capacity") << endl;
    cout << "Truck speed: " << fleet->attribute("Truck, speed") << endl;
    cout << "Truck cost: " << fleet->attribute("Truck, cost") << endl;
    cout << "Truck capacity: " << fleet->attribute("Truck, capacity") << endl;
    
    cout << endl;
    cout << "explore customer1 : expedited " << endl;
    cout << conn->attribute("explore customer1 : expedited");
    cout << endl;
    cout << "explore customer1 : cost 150000 time 1000" << endl;
    cout << conn->attribute("explore customer1 : cost 150000 time 1000");
    cout << endl;
    cout << "connect customer1 : port2" << endl;
    cout << conn->attribute("connect customer1 : port2");
    cout << endl;
    cout << "Removing myConn" << endl;
    manager->instanceDel("myConn");
    cout << "Making secondConn" << endl;
    Ptr<Instance> secondConn = manager->instanceNew("secondConn", "Conn");
    cout << "connect customer1 : port2" << endl;
    cout << secondConn->attribute("connect customer1 : port2");

    cout << "Done!" << endl;

    return 0;
}