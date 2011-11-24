#ifndef CUSTOMERREACTOR_H
#define CUSTOMERREACTOR_H

#include "Location.h"
#include "Activity.h"
#include "InjectActivityReactor.h"

using namespace Shipping;

class CustomerReactor : public Customer::Notifiee {
public:
    typedef Fwk::Ptr<CustomerReactor const> PtrConst;
    typedef Fwk::Ptr<CustomerReactor> Ptr;

    enum Status {
        notActive_ = 0,
        active_ = 1
    };

    static CustomerReactor::Status notActive() { return notActive_; }
    static CustomerReactor::Status active() { return active_; }
    
    static CustomerReactor::Ptr CustomerReactorNew(const string& _name, Customer *_notifier);

    ~CustomerReactor();

    virtual void onAttributeUpdate();

protected:
    Status status_;
    CustomerReactor(const string &_name, Customer* _notifier);
    CustomerReactor(const CustomerReactor&);
    Fwk::Activity::Manager::Ptr activityManager_;
    Fwk::Activity::Ptr activity_;
    InjectActivityReactor* injectReactor_;
};

#endif
