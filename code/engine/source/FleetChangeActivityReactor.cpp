#include "FleetChangeActivityReactor.h"
#include "Fleet.h"

using namespace Shipping;

FleetChangeActivityReactor::FleetChangeActivityReactor(const string &_name, 
                                  Fwk::Ptr<VirtualTimeActivityManager> _virtualManager,
                                  Fwk::Ptr<Fwk::Activity> _activity,
                                  Fleet* _fleet,
                                  TimeOfDay _timeToSwap) :
                                  Notifiee(_name, _activity.ptr()),
                                  fleet_(_fleet),
                                  timeToSwap_(_timeToSwap) {}

void FleetChangeActivityReactor::onStatus() {

    switch(activity_->status()) {

    case Fwk::Activity::executing:
        fleet_->swapData();
        break;
    case Fwk::Activity::free:
        // run again in 24 hours
        activity_->nextTimeIs(Fwk::Time(activity_->nextTime().value() + 24.0));
        activity_->statusIs(Fwk::Activity::nextTimeScheduled);
        break;
    case Fwk::Activity::nextTimeScheduled:
        virtualManager_->lastActivityIs(activity_);
        break;
    default: 
        std::cerr << "FleetChangeActivityReator::onStatus out of range" << std::endl;
        throw(Fwk::RangeException("FleetChangeActivityReactor"));
    }

}