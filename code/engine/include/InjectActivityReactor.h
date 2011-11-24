#ifndef INJECTACTIVITYREACTOR_H
#define INJECTACTIVITYREACTOR_H

#include "Activity.h"
#include "VirtualTimeActivityManager.h"

namespace Shipping {
    class VirtualTimeActivityManager;
    class Location;
    class InjectActivityReactor : public Fwk::Activity::Notifiee {
    public:
        InjectActivityReactor(
            const string &_name,
            Fwk::Ptr<VirtualTimeActivityManager> _virtualManager,
            Fwk::Activity::Ptr _activity,
            const string &_destination,
            Shipping::TransferRate _transferRate,
            Shipping::PackageCount _shipmentSize);

        void onStatus();

        Fwk::Ptr<VirtualTimeActivityManager> virtualManager() const { return virtualManager_; }
        Fwk::Activity::Ptr activity() { return activity_; }
        string destination() { return destination_; }
        Shipping::TransferRate transferRate() { return transferRate_; }
        Shipping::PackageCount shipmentSize() { return shipmentSize_; }

        void virtualManagerIs(Fwk::Ptr<VirtualTimeActivityManager> _virtualManager);
        void activityIs(Fwk::Activity::Ptr _activity);
        void destinationIs(const string &_destination);
        void transferRateIs(Shipping::TransferRate _transferRate);
        void shipmentSizeIs(Shipping::PackageCount _shipmentSize);

    protected:
        string destination_;
        TransferRate transferRate_;
        PackageCount shipmentSize_;
        Fwk::Activity::Ptr activity_;
        Fwk::Ptr<VirtualTimeActivityManager> virtualManager_;
    };

}

#endif
