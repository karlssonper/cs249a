#include "Instance.h"
#include "ManagerImpl.h"
/*
* This is the entry point for your library.
* The client program will call this function to get a handle
* on the Instance::Manager object, and from there will use
* that object to interact with the middle layer (which will
* in turn interact with the engine layer).
*/
Ptr<Instance::Manager> shippingInstanceManager() {
    // hardwired name since Instance.h cannot be changed
    return new Shipping::ManagerImpl("engMgr");
};

