#include <string>
#include <ostream>
#include <iostream>
#include <string>
#include "Location.h"
#include "CustomerReactor.h"
#include "Engine.h"
#include "Activity.h"
#include "VirtualTimeActivityManager.h"

using namespace Shipping;

int main() {

    EngineManager::Ptr engineManager = EngineManager::EngineManagerNew("engineManager");
    Customer::Ptr someCustomer = Customer::CustomerNew("someCustomer", engineManager->virtualTimeActivityManager());
    engineManager->entityManager()->locationIs("someCustomer", someCustomer);

    engineManager->entityManager()->customerDestinationIs("someCustomer","someDestination");
    engineManager->entityManager()->customerShipmentSizeIs("someCustomer", Shipping::PackageCount(100));
    engineManager->entityManager()->customerTransferRateIs("someCustomer", Shipping::TransferRate(24));
    Shipping::RealTimeActivityManager::Ptr mgr = engineManager->realTimeActivityManager();
    cout << "test RTAM is " << mgr->name() <<endl;
    cout << "NOWIS" << endl;
    mgr->nowIs(100.0);

    return 0;
}
