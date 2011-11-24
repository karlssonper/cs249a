#ifndef INJECTACTIVITYREACTOR_H
#define INJECTACTIVITYREACTOR_H

#include "Location.h"
#include "VirtualManager.h"

namespace Shipping {

    class InjectActivityReactor : public Fwk::Activity::Notifiee {
    public:
        InjectActivityReactor(
            const string &_name,
            Fwk::Activity::Manager::Ptr _virtualManager, 
            Fwk::Activity::Ptr _activity,
            const string &_destination,
            Shipping::TransferRate _transferRate,
            Shipping::PackageCount _shipmentSize);

        void onStatus();

        Shipping::VirtualManager::Ptr manager() { return virtualManager_; }
        Fwk::Activity::Ptr activity() { return activity_; }
        string destination() { return destination_; }
        Shipping::TransferRate transferRate() { return transferRate_; }
        Shipping::PackageCount shipmentSize() { return shipmentSize_; }

        void managerIs(Shipping::VirtualManager::Ptr _virtualManager);
        void activityIs(Fwk::Activity::Ptr _activity);
        void destinationIs(const string &_destination);
        void transferRateIs(Shipping::TransferRate _transferRate);
        void shipmentSizeIs(Shipping::PackageCount _shipmentSize);

    protected:
        string destination_;
        Shipping::TransferRate transferRate_;
        Shipping::PackageCount shipmentSize_;
        Fwk::Activity::Ptr activity_;
        Shipping::VirtualManager::Ptr virtualManager_;
    };

}

#endif