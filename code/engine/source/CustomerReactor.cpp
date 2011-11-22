#include "CustomerReactor.h"
#include "Location.h"


using namespace Shipping;

CustomerReactor::CustomerReactor(const string &_name, Customer* _notifier) 
    : Customer::Notifiee(_name, _notifier), activityManager_(Fwk::activityManagerInstance().ptr()) {
    FWK_DEBUG("CustomerReactor constructor, name(): " << name() << " notifier_: " << notifier_->name());  
}

void CustomerReactor::onAttributeUpdate() {
    FWK_DEBUG("CustomerReactor onAttributeUpdate");  
}
