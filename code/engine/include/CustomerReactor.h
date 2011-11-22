#ifndef CUSTOMERREACTOR_H
#define CUSTOMERREACTOR_H

#include "Location.h"
#include "Activity.h"

class CustomerReactor : public Customer::Notifiee {
public:
    typedef Fwk::Ptr<CustomerReactor const> PtrConst;
    typedef Fwk::Ptr<CustomerReactor> Ptr;
    
    CustomerReactor(Fwk::Activity::Manager* _activityManager);
    ~CustomerReactor();

    virtual void onAttributeUpdate(Customer::PtrConst);

protected:
    CustomerReactor(const CustomerReactor&);
    const Fwk::Activity::Manager* activityManager_;
};

#endif