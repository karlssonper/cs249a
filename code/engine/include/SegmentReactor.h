/*
 * SegmentReactor.h
 *
 *  Created on: Nov 23, 2011
 *      Author: per
 */

#ifndef SEGMENTREACTOR_H_
#define SEGMENTREACTOR_H_

#include "Segment.h"
#include "Ptr.h"
#include "Fleet.h"

namespace Shipping {
class VirtualTimeActivityManager;
class Shipment;
class Fleet;
class SegmentReactor : public Segment::Notifiee {
public:
    typedef Fwk::Ptr<SegmentReactor> Ptr;
    typedef Fwk::Ptr<SegmentReactor const> PtrConst;
    virtual void onShipmentEnq(Fwk::Ptr<Shipment>) ;
    virtual void onShipmentDeq();
    virtual void onActivePackageInc(PackageCount);
    virtual void onActivePackageDec(PackageCount);
    virtual ~SegmentReactor();
    static SegmentReactor::Ptr SegmentReactorNew(std::string _name,
            Segment * _owner, Fwk::Ptr<VirtualTimeActivityManager>,
            Fwk::Ptr<Fleet const>);
protected:
    SegmentReactor(std::string _name, Segment * seg,
            Fwk::Ptr<VirtualTimeActivityManager>, Fwk::Ptr<Fleet const>);
    SegmentReactor();
    SegmentReactor(const SegmentReactor&);
    Segment * owner_;
    Fwk::Ptr<VirtualTimeActivityManager> activityManager_;
    Fwk::Ptr<Fleet const> fleet_;
    void createActivity(Fwk::Ptr<Shipment>);
    void addShipmentFromQueue();
    Fleet::Vehicle segTypeToFleetVehicle(Segment::SegmentType);
};
};
#endif /* SEGMENTREACTOR_H_ */
