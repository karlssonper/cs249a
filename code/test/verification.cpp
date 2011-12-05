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

using std::cout;
using std::cerr;
using std::endl;
using std::string;

int main(int argc, char *argv[]) {

    try {

        Ptr<Instance::Manager> manager = shippingInstanceManager();
        Ptr<Instance> stats = manager->instanceNew("myStats", "Stats");
        Ptr<Instance> conn = manager->instanceNew("myConn", "Conn");
        Ptr<Instance> fleet = manager->instanceNew("myFleet", "Fleet");
        Ptr<Instance> timeManager = manager->instanceNew("myTimeManager", "Time manager");

        // make one virtual hour run in a 10 000th of the time
        timeManager->attributeIs("time scale", "0.0001");

        fleet->attributeIs("Boat, speed", "20");
        fleet->attributeIs("Boat, speedAlt", "20");
        fleet->attributeIs("Boat, capacity", "1000");
        fleet->attributeIs("Boat, capacity", "1000");
        fleet->attributeIs("Boat, cost", "30");
        fleet->attributeIs("Boat, costAlt", "50");
        fleet->attributeIs("Truck, speed", "60");
        fleet->attributeIs("Truck, speedAlt", "90");
        fleet->attributeIs("Truck, capacity", "50");
        fleet->attributeIs("Truck, capacityAlt", "30");
        fleet->attributeIs("Truck, costAlt", "50");
        fleet->attributeIs("Truck, cost", "20");
        fleet->attributeIs("Plane, speed", "700");
        fleet->attributeIs("Plane, capacity", "200");
        fleet->attributeIs("Plane, cost", "60");
        fleet->attributeIs("Plane, speedAlt", "600");
        fleet->attributeIs("Plane, capacityAlt", "200");
        fleet->attributeIs("Plane, costAlt", "100");

        // switch fleet attributes at virtual time 10 and 22
        // (and then with 24 hour intervals)
        fleet->attributeIs("alt time", "10 22");

        Ptr<Instance> timmernabben = manager->instanceNew("Timmernabben", "Customer");
        Ptr<Instance> oskarshamn = manager->instanceNew("Oskarshamn", "Port");
        Ptr<Instance> gotland = manager->instanceNew("Gotland", "Customer");
        Ptr<Instance> goteborg = manager->instanceNew("Goteborg", "Port");
        Ptr<Instance> hyssna = manager->instanceNew("Hyssna", "Customer");
        Ptr<Instance> jonkoping = manager->instanceNew("Jonkoping", "Truck terminal");
        Ptr<Instance> vaxjo = manager->instanceNew("Vaxjo", "Truck terminal");
        Ptr<Instance> dh = manager->instanceNew("DH", "Customer");

        timmernabben->attributeIs("transfer rate", "10");
        timmernabben->attributeIs("shipment size", "100");
        timmernabben->attributeIs("destination", "DH");

        //hyssna->attributeIs("transfer rate", "20");
        //hyssna->attributeIs("shipment size", "50");
        //hyssna->attributeIs("destination", "Gotland");

        Ptr<Instance> tim_osk = manager->instanceNew("tim_osk", "Truck segment");
        Ptr<Instance> osk_tim = manager->instanceNew("osk_tim", "Truck segment");
        tim_osk->attributeIs("return segment", "osk_tim");
        tim_osk->attributeIs("source", "Timmernabben");
        osk_tim->attributeIs("source", "Oskarshamn");
        tim_osk->attributeIs("length", "50");
        osk_tim->attributeIs("length", "50");
        tim_osk->attributeIs("capacity", "2");
        osk_tim->attributeIs("capacity", "2");

        Ptr<Instance> osk_gotl = manager->instanceNew("osk_gotl", "Boat segment");
        Ptr<Instance> gotl_osk = manager->instanceNew("gotl_osk", "Boat segment");
        osk_gotl->attributeIs("return segment", "gotl_osk");
        osk_gotl->attributeIs("source", "Oskarshamn");
        gotl_osk->attributeIs("source", "Gotland");
        osk_gotl->attributeIs("length", "130");
        gotl_osk->attributeIs("length", "130");
        osk_gotl->attributeIs("capacity", "2");
        gotl_osk->attributeIs("capacity", "2");

        Ptr<Instance> osk_jon = manager->instanceNew("osk_jon", "Truck segment");
        Ptr<Instance> jon_osk = manager->instanceNew("jon_osk", "Truck segment");
        osk_jon->attributeIs("return segment", "jon_osk");
        osk_jon->attributeIs("source", "Oskarshamn");
        jon_osk->attributeIs("source", "Jonkoping");
        osk_jon->attributeIs("length", "180");
        jon_osk->attributeIs("length", "180");
        osk_jon->attributeIs("capacity", "5");
        jon_osk->attributeIs("capacity", "5");
        
        Ptr<Instance> tim_vax = manager->instanceNew("tim_vax", "Truck segment");
        Ptr<Instance> vax_tim = manager->instanceNew("vax_tim", "Truck segment");
        tim_vax->attributeIs("return segment", "vax_tim");
        tim_vax->attributeIs("source", "Timmernabben");
        vax_tim->attributeIs("source", "Vaxjo");
        tim_vax->attributeIs("length", "120");
        vax_tim->attributeIs("length", "120");
        tim_vax->attributeIs("capacity", "3");
        vax_tim->attributeIs("capacity", "3");

        Ptr<Instance> vax_jon = manager->instanceNew("vax_jon", "Truck segment");
        Ptr<Instance> jon_vax = manager->instanceNew("jon_vax", "Truck segment");
        jon_vax->attributeIs("return segment", "vax_jon");
        jon_vax->attributeIs("source", "Jonkoping");
        vax_jon->attributeIs("source", "Vaxjo");
        jon_vax->attributeIs("length", "120");
        vax_jon->attributeIs("length", "120");
        jon_vax->attributeIs("capacity", "3");
        vax_jon->attributeIs("capacity", "3");

        Ptr<Instance> jon_dh = manager->instanceNew("jon_dh", "Truck segment");
        Ptr<Instance> dh_jon = manager->instanceNew("dh_jon", "Truck segment");
        jon_dh->attributeIs("return segment", "dh_jon");
        jon_dh->attributeIs("source", "Jonkoping");
        dh_jon->attributeIs("source", "DH");
        jon_dh->attributeIs("length", "5");
        dh_jon->attributeIs("length", "5");
        jon_dh->attributeIs("capacity", "2");
        dh_jon->attributeIs("capacity", "2");

        Ptr<Instance> jon_gote = manager->instanceNew("jon_gote", "Truck segment");
        Ptr<Instance> gote_jon = manager->instanceNew("gote_jon", "Truck segment");
        jon_gote->attributeIs("return segment", "gote_jon");
        jon_gote->attributeIs("source", "Jonkoping");
        gote_jon->attributeIs("source", "Goteborg");
        jon_gote->attributeIs("length", "150");
        gote_jon->attributeIs("length", "150");
        jon_gote->attributeIs("capacity", "6");
        gote_jon->attributeIs("capacity", "6");

        Ptr<Instance> gote_hys = manager->instanceNew("gote_hys", "Truck segment");
        Ptr<Instance> hys_gote = manager->instanceNew("hys_gote", "Truck segment");
        gote_hys->attributeIs("return segment", "hys_gote");
        gote_hys->attributeIs("source", "Goteborg");
        hys_gote->attributeIs("source", "Hyssna");
        gote_hys->attributeIs("length", "50");
        hys_gote->attributeIs("length", "50");
        gote_hys->attributeIs("capacity", "2");
        hys_gote->attributeIs("capacity", "2");

        Ptr<Instance> gote_gotl = manager->instanceNew("gote_gotl", "Plane segment");
        Ptr<Instance> gotl_gote = manager->instanceNew("gotl_gote", "Plane segment");
        gote_gotl->attributeIs("return segment", "gotl_gote");
        gote_gotl->attributeIs("source", "Goteborg");
        gotl_gote->attributeIs("source", "Gotland");
        gote_gotl->attributeIs("length", "400");
        gotl_gote->attributeIs("length", "400");
        gote_gotl->attributeIs("capacity", "1");
        gotl_gote->attributeIs("capacity", "1");

        conn->attributeIs("djikstras", "bfs");

        // runs the simulation until the virtual time is 100
        timeManager->attributeIs("simulation end", "100");

        std::cout << std::endl;
        std::cout << " -- STATS -- " << std::endl;
        std::cout << "Gotland recieved shipments: " << gotland->attribute("shipments recieved") << std::endl;
        std::cout << "Gotland average latency: " << gotland->attribute("average latency") << std::endl;
        std::cout << std::endl;
        std::cout << "DH recieved shipments: " << dh->attribute("shipments recieved") << std::endl;
        std::cout << "DH average latency: " << dh->attribute("average latency") << std::endl;
        std::cout << std::endl;


        std::cout << "Done!" << std::endl;
        
    } catch (Fwk::Exception e) {
        std::cerr << "Exception in main: " << e.what() << std::endl;
    }
    return 0;
}