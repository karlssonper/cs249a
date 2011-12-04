#ifndef INJECTACTIVITYREACTOR_H
#define INJECTACTIVITYREACTOR_H

#include "Activity.h"
#include "Utils.h"
#include "VirtualTimeActivityManager.h"

namespace Shipping {
    class Location;
    class EntityManager;
    class InjectActivityReactor : public Fwk::Activity::Notifiee {
    public:
        InjectActivityReactor(
            const string &_name,
            const string &_customer,
            Fwk::Ptr<VirtualTimeActivityManager> _virtualManager,
            Fwk::Activity::Ptr _activity,
            const string &_destination,
            Shipping::TransferRate _transferRate,
            Shipping::PackageCount _shipmentSize,
            Fwk::Ptr<EntityManager> _entityManager);

        void onStatus();

        Fwk::Ptr<VirtualTimeActivityManager> virtualManager() const { return virtualManager_; }
        Fwk::Activity::Ptr activity() { return activity_; }
        string destination() { return destination_; }
        TransferRate transferRate() { return transferRate_; }
        PackageCount shipmentSize() { return shipmentSize_; }

        void virtualManagerIs(Fwk::Ptr<VirtualTimeActivityManager> _virtualManager);
        void activityIs(Fwk::Activity::Ptr _activity);
        void destinationIs(const string &_destination);
        void transferRateIs(TransferRate _transferRate);
        void shipmentSizeIs(PackageCount _shipmentSize);

    protected:
        string destination_;
        string customer_;
        TransferRate transferRate_;
        PackageCount shipmentSize_;
        Fwk::Activity::Ptr activity_;
        Fwk::Ptr<VirtualTimeActivityManager> virtualManager_;
        Fwk::Ptr<EntityManager> entityManager_;
    };

}

#endif
