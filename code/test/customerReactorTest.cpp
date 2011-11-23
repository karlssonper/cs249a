#include <string>
#include <ostream>
#include <iostream>
#include <string>
#include "Location.h"
#include "CustomerReactor.h"
#include "Engine.h"

using namespace Shipping;

int main() {

    EngineManager::Ptr engineManager = EngineManager::EngineManagerNew("engineManager");
    Customer::Ptr someCustomer = Customer::CustomerNew("someCustomer");
    engineManager->entityManager()->locationIs("someCustomer", someCustomer);

    engineManager->entityManager()->customerDestinationIs("someCustomer","someDestination");



    return 0;
}
