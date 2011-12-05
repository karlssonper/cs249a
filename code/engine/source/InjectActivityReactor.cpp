#include "InjectActivityReactor.h"
#include "Location.h"
#include "Exception.h"
#include "Shipment.h"
#include "EntityManager.h"

using namespace Shipping;

InjectActivityReactor::InjectActivityReactor(
    const string &_name,
    const string &_customer,
    VirtualTimeActivityManager::Ptr _virtualManager,
    Fwk::Activity::Ptr _activity,
    const string &_destination,
    TransferRate _transferRate,
    PackageCount _shipmentSize,
    Fwk::Ptr<EntityManager> _entityManager) :
    Notifiee(_name, _activity.ptr()),
    customer_(_customer),
    destination_(_destination),
    transferRate_(_transferRate),
    shipmentSize_(_shipmentSize),
    activity_(_activity),
    virtualManager_(_virtualManager),
    entityManager_(_entityManager) {
        FWK_DEBUG("InjectActivityReactor " << name() << " constructor");
}

    void InjectActivityReactor::virtualManagerIs(VirtualTimeActivityManager::Ptr _virtualManager) {
    virtualManager_ = _virtualManager;
}

void InjectActivityReactor::activityIs(Fwk::Activity::Ptr _activity) {
    activity_ = _activity;
}

void InjectActivityReactor::destinationIs(const string &_destination) {
    if (destination_ == _destination) return;
    destination_ = _destination;
}

void InjectActivityReactor::transferRateIs(TransferRate _transferRate) {
    if (transferRate_ == _transferRate) return;
    transferRate_ = _transferRate;
}

void InjectActivityReactor::shipmentSizeIs(PackageCount _shipmentSize) {
    if (shipmentSize_ == _shipmentSize) return;
    shipmentSize_ = _shipmentSize;
}

void InjectActivityReactor::onStatus() {

    Shipment::Ptr shipment;
    switch(activity_->status()) {

    case Fwk::Activity::executing:
        SIM(customer_ << " creating shipment, size " << shipmentSize_.value() << ", destinaton " << destination_);
        shipment = new Shipment(shipmentSize_, entityManager_->location(destination_));
        entityManager_->locationShipmentNew(customer_, shipment);
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
        std::cerr << "InjectActivityReactor::onStatus out of range" << std::endl;
        throw(Fwk::RangeException("InjectActivityReactor"));
    }

}

