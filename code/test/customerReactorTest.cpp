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
    Customer::Ptr someCustomer = Customer::CustomerNew("someCustomer", engineManager->entityManager());
    engineManager->entityManager()->locationIs("someCustomer", someCustomer);

    engineManager->entityManager()->customerDestinationIs("someCustomer","someDestination");
    engineManager->entityManager()->customerShipmentSizeIs("someCustomer", Shipping::PackageCount(100));
    engineManager->entityManager()->customerTransferRateIs("someCustomer", Shipping::TransferRate(24));
    Shipping::VirtualTimeActivityManager::Ptr mgr = engineManager->virtualTimeActivityManager();
    mgr->nowIs(20.0);
    engineManager->entityManager()->customerTransferRateIs("someCustomer", Shipping::TransferRate(0));
    mgr->nowIs(40.0);
    engineManager->entityManager()->customerTransferRateIs("someCustomer", Shipping::TransferRate(12));
    mgr->nowIs(60.0);
    engineManager->entityManager()->customerTransferRateIs("someCustomer", Shipping::TransferRate(2));
    mgr->nowIs(80.0);






    return 0;
}
