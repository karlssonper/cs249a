#include <string>
#include <ostream>
#include <iostream>
#include <string>
#include "Location.h"
#include "CustomerReactor.h"

using namespace Shipping;

int main() {

    Customer::Ptr someCustomer = Customer::CustomerNew("someCustomer");
    CustomerReactor::Ptr someCustomerReactor = new CustomerReactor("someCustomerReactor", someCustomer.ptr());


    return 0;
}
