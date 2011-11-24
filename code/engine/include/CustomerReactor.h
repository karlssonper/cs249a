#ifndef CUSTOMERREACTOR_H
#define CUSTOMERREACTOR_H

#include "Ptr.h"
#include "Location.h"

namespace Fwk {class Activity; };
namespace Shipping {
class InjectActivityReactor;
class VirtualTimeActivityManager;
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
    
    static CustomerReactor::Ptr CustomerReactorNew(const string& _name,
            Customer *_notifier,
            Fwk::Ptr<VirtualTimeActivityManager> _virtualTimeActivityManager );
    ~CustomerReactor();

    virtual void onAttributeUpdate();

protected:
    Status status_;
    CustomerReactor(const string &_name, Customer* _notifier,
            Fwk::Ptr<VirtualTimeActivityManager> _virtualTimeActivityManager);
    CustomerReactor(const CustomerReactor&);
    Fwk::Ptr<VirtualTimeActivityManager> activityManager_;
    Fwk::Ptr<Fwk::Activity> activity_;
    InjectActivityReactor* injectReactor_;
};
};//end of namespace

#endif
