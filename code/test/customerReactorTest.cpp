#include <string>
#include <ostream>
#include <iostream>
#include <string>
#include "Location.h"
#include "CustomerReactor.h"
#include "Engine.h"
#include "Activity.h"

using namespace Shipping;

int main() {

    EngineManager::Ptr engineManager = EngineManager::EngineManagerNew("engineManager");
    Customer::Ptr someCustomer = Customer::CustomerNew("someCustomer");
    engineManager->entityManager()->locationIs("someCustomer", someCustomer);

    engineManager->entityManager()->customerDestinationIs("someCustomer","someDestination");
    engineManager->entityManager()->customerShipmentSizeIs("someCustomer", Shipping::PackageCount(100));
    engineManager->entityManager()->customerTransferRateIs("someCustomer", Shipping::TransferRate(24));

    Fwk::Activity::Manager::Ptr mgr = Fwk::activityManagerInstance();
    mgr->nowIs(20.0);


    engineManager->entityManager()->customerTransferRateIs("someCustomer", Shipping::TransferRate(0));






    return 0;
}
