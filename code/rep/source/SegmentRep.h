#ifndef SEGMENTREP_H_
#define SEGMENTREP_H_

#include "DeletableInstance.h"

namespace Shipping {
    class EngineManager;
    class SegmentRep : public DeletableInstance {
    public:
        SegmentRep(const string &_name, Ptr<EngineManager> _engineManager);
        virtual ~SegmentRep();
        virtual string attribute(const string &_attributeName);
        virtual void attributeIs(const string& name, const string& v);
    protected:
        virtual void del();
        Ptr<EngineManager> engineManager_;
    };

    class TruckSegmentRep : public SegmentRep {
    public:
        TruckSegmentRep(const string &_name, Ptr<EngineManager> _engineManager);
        virtual ~TruckSegmentRep();
    };

    class BoatSegmentRep : public SegmentRep {
    public:
        BoatSegmentRep(const string &_name, Ptr<EngineManager> _engineManager);
        virtual ~BoatSegmentRep();
    };

    class PlaneSegmentRep : public SegmentRep {
    public:
        PlaneSegmentRep(const string &_name, Ptr<EngineManager> _engineManager);
        virtual ~PlaneSegmentRep();
    };
}

#endif /* SEGMENTREP_H_ */
