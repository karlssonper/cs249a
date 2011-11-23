#ifndef INJECTACTIVITYREACTOR_H
#define INJECTACTIVITYREACTOR_H

#include "ActivityImpl.h"
#include "Activity.h"
#include "Location.h"

class InjectActivityReactor : public Fwk::Activity::Notifiee {
public:
    InjectActivityReactor(
        const string &_name,
        Fwk::Activity::Manager::Ptr _manager, 
        Fwk::Activity::Ptr _activity,
        const string &_destination,
        Shipping::TransferRate _transferRate,
        Shipping::PackageCount _shipmentSize);

    void onStatus();

    Fwk::Activity::Manager::Ptr manager() { return manager_; }
    Fwk::Activity::Ptr activity() { return activity_; }
    string destination() { return destination_; }
    Shipping::TransferRate transferRate() { return transferRate_; }
    Shipping::PackageCount shipmentSize() { return shipmentSize_; }

    void managerIs(Fwk::Activity::Manager::Ptr _manager);
    void activityIs(Fwk::Activity::Ptr _activity);
    void destinationIs(const string &_destination);
    void transferRateIs(Shipping::TransferRate _transferRate);
    void shipmentSizeIs(Shipping::PackageCount _shipmentSize);

protected:
    string destination_;
    Shipping::TransferRate transferRate_;
    Shipping::PackageCount shipmentSize_;
    Fwk::Activity::Ptr activity_;
    Fwk::Activity::Manager::Ptr manager_;
};

#endif