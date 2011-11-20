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

    Ptr<Instance> port1 = manager->instanceNew("port1","Port");
    Ptr<Instance> port2 = manager->instanceNew("port2","Port");
    Ptr<Instance> port3 = manager->instanceNew("port3","Port");

    Ptr<Instance> ts1 = manager->instanceNew("ts1","Truck segment");
    Ptr<Instance> ts2 = manager->instanceNew("ts2","Truck segment");
    Ptr<Instance> ts3 = manager->instanceNew("ts3","Truck segment");
    Ptr<Instance> ts4 = manager->instanceNew("ts4","Truck segment");
    Ptr<Instance> ts5 = manager->instanceNew("ts5","Truck segment");
    Ptr<Instance> ts6 = manager->instanceNew("ts6","Truck segment");

    ts1->attributeIs("source","port1");
    ts2->attributeIs("source","port2");
    ts1->attributeIs("return segment","ts2");

    ts3->attributeIs("source","port2");
    ts4->attributeIs("source","port3");
    ts3->attributeIs("return segment","");

    cout << "ts1 return: " << ts1->attribute("return segment") << endl;
    cout << "ts2 return: " << ts2->attribute("return segment") << endl;
    cout << "ts3 return: " << ts3->attribute("return segmet") << endl;

    cout << "port1 segment4" << port1->attribute("segment-1");

    cout << conn->attribute("explore port1");

    return 0;
}