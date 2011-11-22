#ifndef CUSTOMERREACTOR_H
#define CUSTOMERREACTOR_H

#include "Location.h"
#include "Activity.h"

using namespace Shipping;

class CustomerReactor : public Customer::Notifiee {
public:
    typedef Fwk::Ptr<CustomerReactor const> PtrConst;
    typedef Fwk::Ptr<CustomerReactor> Ptr;
    
    CustomerReactor(const string &_name, Customer* _notifier);
    ~CustomerReactor();

    virtual void onAttributeUpdate();

protected:
    CustomerReactor(const CustomerReactor&);
    const Customer *notifier_;
};

#endif