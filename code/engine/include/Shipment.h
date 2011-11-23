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


namespace Shipping {
class Location;
class Shipment : public Fwk::PtrInterface<Shipment> {
public:
    typedef Fwk::Ptr<Shipment const> PtrConst;
    typedef Fwk::Ptr<Shipment> Ptr;
    Shipment(PackageCount _packages, Fwk::Ptr<Location const> _dest);
    PackageCount waitingPackages() const { return waiting_; } ;
    PackageCount transferedPackages() const { return transfered_; } ;
    PackageCount totalPackages() const { return total_; } ;
    void transferedPackagesInc(PackageCount p);
protected:
    PackageCount waiting_;
    PackageCount transfered_;
    const PackageCount total_;
    Fwk::Ptr<Location const> dest_;
};
} //end namespace Shipping

#endif /* SHIPMENT_H_ */
