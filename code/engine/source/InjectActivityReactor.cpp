#include "InjectActivityReactor.h"
#include "Location.h"


InjectActivityReactor::InjectActivityReactor(
    const string &_name,
    Fwk::Activity::Manager::Ptr _manager, 
    Fwk::Activity::Ptr _activity,
    const string &_destination,
    Shipping::TransferRate _transferRate,
    Shipping::PackageCount _shipmentSize) :
Notifiee(_name, _activity.ptr()),
    destination_(_destination),
    transferRate_(_transferRate),
    shipmentSize_(_shipmentSize),
    activity_(_activity),
    manager_(_manager) {
        FWK_DEBUG("InjectActivityReactor " << name() << " constructor");
}

void InjectActivityReactor::managerIs(Fwk::Activity::Manager::Ptr _manager) {
    manager_ = _manager;
}

void InjectActivityReactor::activityIs(Fwk::Activity::Ptr _activity) {
    activity_ = _activity;
}

void InjectActivityReactor::destinationIs(const string &_destination) {
    if (destination_ == _destination) return;
    destination_ = _destination;
}

void InjectActivityReactor::transferRateIs(Shipping::TransferRate _transferRate) {
    if (transferRate_ == _transferRate) return;
    transferRate_ = _transferRate;
}

void InjectActivityReactor::shipmentSizeIs(Shipping::PackageCount _shipmentSize) {
    if (shipmentSize_ == _shipmentSize) return;
    shipmentSize_ = _shipmentSize;
}

void InjectActivityReactor::onStatus() {

    switch(activity_->status()) {

    case Fwk::Activity::executing:
        FWK_DEBUG(name() << " executing");
        FWK_DEBUG(name() << " d: " << destination_ << " sz: " << shipmentSize_.value() << " tr: " << transferRate_.value());
        break;
    case Fwk::Activity::free:
        FWK_DEBUG(name() << " enqueueing itself");
        activity_->nextTimeIs(Fwk::Time(activity_->nextTime().value() + 24.0/double(transferRate_.value())));
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

