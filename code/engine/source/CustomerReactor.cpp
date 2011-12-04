#include "CustomerReactor.h"
#include "Location.h"
#include "InjectActivityReactor.h"
#include "VirtualTimeActivityManager.h"
#include "Exception.h"
#include "EntityManager.h"

using namespace Shipping;

CustomerReactor::CustomerReactor(const string &_name, 
                                 Customer* _notifier,
                                 VirtualTimeActivityManager::Ptr _virtualTimeActivityManager,
                                 Fwk::Ptr<EntityManager> _entityManager)
    : Customer::Notifiee(_name, _notifier),
    activityManager_(_virtualTimeActivityManager),
    entityManager_(_entityManager),
    activity_(NULL),
    status_(notActive()) {
        FWK_DEBUG("CustomerReactor constructor, name(): " << name() << " notifier: " << notifier()->name());  
}

CustomerReactor::Ptr CustomerReactor::CustomerReactorNew(const string &_name,
                                                         Customer *_notifier,
                                                         VirtualTimeActivityManager::Ptr _virtualTimeActivityManager,
                                                         Fwk::Ptr<EntityManager> _entityManager) {
        FWK_DEBUG("CustomerReactorNew " << _name);
        CustomerReactor::Ptr p = new CustomerReactor(_name,  _notifier,
            _virtualTimeActivityManager, _entityManager);
        if (!p) {
            std::cerr << "CustomerReactorNew new() failed" << std::endl;
            throw(Fwk::MemoryException("CustomerReactor::CustomerReactorNew"));
        }
        return p;
}

void CustomerReactor::onAttributeUpdate() {
    try {
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
                    if (!activity_) {
                        FWK_DEBUG("Creating new Activity");
                        activity_ = activityManager_->activityNew(injectorName);
                    }
                    injectorName.append("Reactor");
                    FWK_DEBUG("Creating new InjectActivityReactor");
                    injectReactor_ = new InjectActivityReactor(
                        injectorName,
                        notifier()->name(),
                        activityManager_,
                        activity_, 
                        notifier()->destination(),
                        notifier()->transferRate(),
                        notifier()->shipmentSize(),
                        entityManager_);
                    activity_->nextTimeIs(activityManager_->now());
                    activity_->notifieeIs(injectorName, injectReactor_);
                    activity_->statusIs(Fwk::Activity::nextTimeScheduled);
            } else {
                FWK_DEBUG("All three attribs not set, doing nothing");
            }
        } else if (status_ == active()) {
            FWK_DEBUG("CustomerReactor active");
            if (notifier()->transferRate().value() == 0 ||
                notifier()->destination() == "" ||
                notifier()->shipmentSize().value() == 0) {
                    FWK_DEBUG("All three attribs not set, setting CustomerReactor to notActive");
                    status_ = notActive();
                    activity_->notifieeIs("",0);
                    activityManager_->activityDel(activity_->name());
                    activity_ = NULL;
                    injectReactor_ = NULL;
            } else {
                FWK_DEBUG("All three attribs still set, updating values");
                injectReactor_->destinationIs(notifier()->destination());
                injectReactor_->shipmentSizeIs(notifier()->shipmentSize());
                injectReactor_->transferRateIs(notifier()->transferRate());
            }
        }
    } // try 
    catch(Fwk::Exception e) {
        std::cerr << "Exception in CustomerReactor::onAttributeUpdate(): " << e.what() << std::endl;
        onNotificationException();
    }
}

CustomerReactor::~CustomerReactor() {
    FWK_DEBUG("~CustomerReactor() " << name());
}
