#include "Shipment.h"
#include "Location.h"

using namespace Shipping;

Shipment::Shipment(PackageCount _packages, Location::PtrConst _dest) :
        total_(_packages), dest_(_dest), transferedComp_(false), arrived_(0)
{

};

Location::PtrConst Shipment::destination() const {
    return dest_;
};

void Shipment::transferedPackagesInc(PackageCount p)
{
    transfered_ = transfered_.value() + p.value();
    /*if (transfered_ == total_){
        transfered_ = 0;
    }*/
}

void Shipment::transferedPackagesDec(PackageCount p)
{
    transfered_ = transfered_.value() - p.value();
    transferedComp_ = true;
}

void Shipment::queuedPackagesInc(PackageCount p)
{
    queued_ = queued_.value() + p.value();
    if (queued_ > waitingPackages()){
        //error
    }
}

void Shipment::queuedPackagesDec(PackageCount p)
{
    queued_ = queued_.value() - p.value();
    if (queued_ < 0){
        //error
    }
}

void Shipment::arrivedPackagesIs(PackageCount c) {
    if (arrived_ != c)
        arrived_ = c;
}