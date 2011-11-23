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
        total_(_packages), dest_(_dest)
{

};

void Shipment::transferedPackagesInc(PackageCount p)
{
    transfered_ = transfered_.value() + p.value();
    if (transfered_ == total_){
        transfered_ = 0;
    }
}
