#include "FleetChangeActivityReactor.h"
#include "Fleet.h"
#include "Debug.h"

using namespace Shipping;

FleetChangeActivityReactor::FleetChangeActivityReactor(const string &_name, 
    Fwk::Ptr<VirtualTimeActivityManager> _virtualManager,
    Fwk::Ptr<Fwk::Activity> _activity,
    Fleet* _fleet,
    TimeOfDay _timeToSwap) :
    Notifiee(_name, _activity.ptr()),
    virtualManager_(_virtualManager),
    activity_(_activity),
    fleet_(_fleet),
    timeToSwap_(_timeToSwap) {}

void FleetChangeActivityReactor::onStatus() {
    try {
        switch(activity_->status()) {

        case Fwk::Activity::executing:
            FWK_DEBUG("FleetChangeActivityReactor executing: " << activity_->name());
            fleet_->swapData();
            break;
        case Fwk::Activity::free:
            FWK_DEBUG("FleetChangeActivityReactor free");
             //run again in 24 hours
            activity_->nextTimeIs(Fwk::Time(activity_->nextTime().value() + 24.0));
            activity_->statusIs(Fwk::Activity::nextTimeScheduled);
            break;
        case Fwk::Activity::nextTimeScheduled:
            FWK_DEBUG("FleetChangeActivityReactor nextTimeScheduled: " << activity_->nextTime().value());
            virtualManager_->lastActivityIs(activity_);
            break;
        default: 
            std::cerr << "FleetChangeActivityReator::onStatus out of range" << std::endl;
            throw(Fwk::RangeException("FleetChangeActivityReactor"));
        }
    } // try
    catch(Fwk::Exception e) {
        std::cerr << "FleetChangeActivityReactor::onStatus(): " << e.what() << std::endl;
        onNotificationException();
    }
}