/*
 * Shipment.cpp
 *
 *  Created on: Nov 22, 2011
 *      Author: per
 */

#include "Shipment.h"
#include "Location.h"

using namespace Shipping;

Shipment::Shipment(PackageCount _packages, Location::PtrConst _dest) :
        packages_(_packages), dest_(_dest)
{

};

void Shipment::transferedPackagesInc(PackageCount p)
{
    transfered_ += p;
    waiting -= p;
    if (transfered_ >= total_){
        waiting_ = total_;
        transfered_ = 0;
    }
}
