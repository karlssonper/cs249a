/*
* Shipment.h
*
*  Created on: Nov 22, 2011
*      Author: per
*/

#ifndef SHIPMENT_H_
#define SHIPMENT_H_

#include "Utils.h"
#include "PtrInterface.h"
#include "Ptr.h"
#include "Activity.h"

namespace Fwk {
    class Time;
}

namespace Shipping {
    class Location;
    class Shipment : public Fwk::PtrInterface<Shipment> {
    public:
        typedef Fwk::Ptr<Shipment const> PtrConst;
        typedef Fwk::Ptr<Shipment> Ptr;
        Shipment(PackageCount _packages, Fwk::Ptr<Location const> _dest);
        PackageCount waitingPackages() const { 
            return total_.value() - transfered_.value() - queued_.value(); 
        } ;
        PackageCount transferedPackages() const { return transfered_; } ;
        PackageCount queuedPackages() const { return queued_; } ;
        PackageCount packages() const { return total_; } ;
        Fwk::Ptr<Location const> destination() const;
        void transferedPackagesInc(PackageCount p);
        void transferedPackagesDec(PackageCount p);
        PackageCount arrivedPackages() const {return arrived_;};
        void arrivedPackagesIs(PackageCount c);
        void queuedPackagesInc(PackageCount p);
        void queuedPackagesDec(PackageCount p);
        void transferedIs() {transferedComp_ = false;};
        bool transfered() const { return transferedComp_;};
        void timeStampSentIs(Fwk::Time sent_);
        void timeStampArrivedIs(Fwk::Time arrived_);
        Fwk::Time timeStampSent() const { return timeStampSent_; }
        Fwk::Time timeStampArrived() const { return timeStampArrived_; }
    protected:
        bool transferedComp_;
        PackageCount transfered_;
        PackageCount arrived_;
        PackageCount queued_;
        const PackageCount total_;
        Fwk::Ptr<Location const> dest_;
        Fwk::Time timeStampSent_;
        Fwk::Time timeStampArrived_;
    };
} //end namespace Shipping

#endif /* SHIPMENT_H_ */
