#include "InjectActivityReactor.h"


InjectActivityReactor::InjectActivityReactor(
    const string &_name,
    Fwk::Activity::Manager::Ptr _manager, 
    Fwk::Activity::Ptr _activity,
    double _rate) :
    Notifiee(_name, _activity.ptr()),
    rate_(_rate),
    activity_(_activity),
    manager_(_manager) {
        FWK_DEBUG("InjectActivityReactor " << name() << " constructor");
    }

void InjectActivityReactor::onStatus() {

    switch(activity_->status()) {

    case Fwk::Activity::executing:
        FWK_DEBUG(name() << " executing");
        break;
    case Fwk::Activity::free:
        FWK_DEBUG(name() << " enqueueing itself");
        activity_->nextTimeIs(Fwk::Time(activity_->nextTime().value() + rate_));
        activity_->statusIs(Fwk::Activity::nextTimeScheduled);
        break;
    case Fwk::Activity::nextTimeScheduled:
        FWK_DEBUG(name() << " adding itself to be scheduled");
        manager_->lastActivityIs(activity_);
        break;
    default:
        break;
    }

}

