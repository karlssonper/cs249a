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

namespace Shipping {
class Shipment;
class SegmentReactor : public Segment::Notifiee {
public:
    typedef Fwk::Ptr<SegmentReactor> Ptr;
    typedef Fwk::Ptr<SegmentReactor const> PtrConst;
    virtual void onShipmentEnq(Fwk::Ptr<Shipment>) ;
    virtual void onShipmentDeq();
    virtual void onActivePackageInc(PackageCount);
    virtual void onActivePackageDec(PackageCount);
    virtual ~SegmentReactor();
    static SegmentReactor::Ptr SegmentReactorNew(std::string _name, Segment * _owner) {
        Ptr p = new SegmentReactor(_name, _owner);
        return p;
    };
protected:
    SegmentReactor(std::string _name, Segment * seg);
    SegmentReactor();
    SegmentReactor(const SegmentReactor&);
    Segment * owner_;
};
};
#endif /* SEGMENTREACTOR_H_ */
