#include "CustomerReactor.h"
#include "Location.h"
#include "Activity.h"
#include "ActivityReactor.h"

using namespace Shipping;

CustomerReactor::CustomerReactor(const string &_name, Customer* _notifier) 
    : Customer::Notifiee(_name, _notifier),
    activityManager_(Fwk::activityManagerInstance().ptr()),
    status_(notActive()) {
        FWK_DEBUG("CustomerReactor constructor, name(): " << name() << " notifier: " << notifier()->name());  
}

CustomerReactor::Ptr CustomerReactor::CustomerReactorNew(const string &_name, Customer *_notifier) {
    FWK_DEBUG("CustomerReactorNew " << _name);
    CustomerReactor::Ptr p = new CustomerReactor(_name, _notifier);
    return p;
    FWK_DEBUG("CustomerReactorNew returning p");
}

void CustomerReactor::onAttributeUpdate() {
    FWK_DEBUG("CustomerReactor onAttributeUpdate");  
    if (status_ == notActive()) {
        FWK_DEBUG("CustomerReactor not active");
        if (notifier()->transferRate().value() != 0 &&
            notifier()->destination() != "" &&
            notifier()->shipmentSize().value() != 0) {
                FWK_DEBUG("All three attribs set, setting CustomerReactor to active");

                status_ = active();
                string injectorName = name();
                injectorName.append("Injector");
                activity_ = activityManager_->activityNew(injectorName);
                injectorName.append("Reactor");
                injectReactor_ = new InjectActivityReactor(injectorName, activityManager_, activity_, 2.0);
                activity_->notifieeIs(injectorName, injectReactor_);
                activity_->statusIs(Fwk::Activity::nextTimeScheduled);


        } else {
            FWK_DEBUG("All three attribs not set");
        }
    } else if (status_ == active()) {
        FWK_DEBUG("CustomerReactor active");
        if (notifier()->transferRate().value() == 0 ||
            notifier()->destination() == "" ||
            notifier()->shipmentSize().value() == 0) {
                FWK_DEBUG("All three attribs not set, setting CustomerReactor to notActive");
                status_ = notActive();
                //stop injecting
        } else {
            FWK_DEBUG("All three attribs still set");
            // update injection
        }
    }
}

CustomerReactor::~CustomerReactor() {
    FWK_DEBUG("~CustomerReactor() " << name());
}
