#include "InjectActivityReactor.h"
#include "Location.h"


Shipping::InjectActivityReactor::InjectActivityReactor(
    const string &_name,
    Shipping::VirtualManager::Ptr _virtualManager, 
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

    void Shipping::InjectActivityReactor::managerIs(Shipping::VirtualManager::Ptr _virtualManager) {
    virtualManager_ = _virtualManager;
}

void Shipping::InjectActivityReactor::activityIs(Fwk::Activity::Ptr _activity) {
    activity_ = _activity;
}

void Shipping::InjectActivityReactor::destinationIs(const string &_destination) {
    if (destination_ == _destination) return;
    destination_ = _destination;
}

void Shipping::InjectActivityReactor::transferRateIs(Shipping::TransferRate _transferRate) {
    if (transferRate_ == _transferRate) return;
    transferRate_ = _transferRate;
}

void Shipping::InjectActivityReactor::shipmentSizeIs(Shipping::PackageCount _shipmentSize) {
    if (shipmentSize_ == _shipmentSize) return;
    shipmentSize_ = _shipmentSize;
}

void Shipping::InjectActivityReactor::onStatus() {

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
        virtualManager_->lastActivityIs(activity_);
        break;
    default:
        break;
    }

}

