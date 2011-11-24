#ifndef SEGMENT_H
#define SEGMENT_H

#include <string>
#include <iostream>
#include <list>
#include <limits>

#include "Ptr.h"
#include "Nominal.h"
#include "BaseNotifiee.h"
#include "NamedInterface.h"
#include "Utils.h"
#include <queue>

//#include "Shipment.h"

namespace Shipping {
    class Shipment;
    class SegmentDifficulty : public Ordinal<SegmentDifficulty, float> {
    public:
        SegmentDifficulty() : Ordinal<SegmentDifficulty, float>(1.f) {}
        SegmentDifficulty(float value) : Ordinal<SegmentDifficulty, float>(value) {
            if (value < 1.0 || value > 5.0 )
            {
                std:cerr << "SegmentDifficulty out of range, using default value (1.0) " << std::endl;
                value = 1.0;
            }
        };
    };

    class Segment : public Fwk::NamedInterface {
    public:
        typedef Fwk::Ptr<Segment const> PtrConst;
        typedef Fwk::Ptr<Segment> Ptr;
        virtual ~Segment();
        enum ExpediteSupport {
            noExpediteSupport_ = 0,
            fullExpediteSupport_ = 1
        };

        static inline ExpediteSupport noExpediteSupport() {
            return noExpediteSupport_;
        }
        static inline ExpediteSupport fullExpediteSupport() {
            return fullExpediteSupport_;
        }

        enum SegmentType {
            truckSegment_ = 0,
            boatSegment_ = 1,
            planeSegment_ = 2
        };

        static inline SegmentType truckSegment() { return truckSegment_; }
        static inline SegmentType boatSegment() { return boatSegment_; }
        static inline SegmentType planeSegment() { return planeSegment_; }

        // accessors
        string source() const { return source_; }
        Miles length() const { return length_; }
        string returnSegment() const { return returnSegment_; }
        SegmentDifficulty difficulty() const { return difficulty_;};
        ExpediteSupport expediteSupport() const { return expediteSupport_; }
        SegmentType type() const { return type_; }
        PackageCount activePackages() const { return activePackages_;};
        PackageCount capacity() const { return capacity_;};

        // mutators
        void sourceIs(const string &_source);
        void lengthIs(Miles _length);
        void returnSegmentIs(const string &_returnSegment);
        void difficultyIs(SegmentDifficulty _difficulty) ;
        void expediteSupportIs(ExpediteSupport _expediteSupport);
        void capacityIs(PackageCount c);
        void activePackageInc(PackageCount c);
        void activePackageDec(PackageCount c);
        void shipmentEnq(Fwk::Ptr<Shipment>);
        void shipmentDeq();

        class Notifiee : public Fwk::BaseNotifiee<Segment> {
        public:
            typedef Fwk::Ptr<Segment::Notifiee const> PtrConst;
            typedef Fwk::Ptr<Segment::Notifiee> Ptr;

            virtual void onShipmentEnq(Fwk::Ptr<Shipment>);
            virtual void onShipmentDeq();
            virtual void onActivePackageInc(PackageCount);
            virtual void onActivePackageDec(PackageCount);

            virtual ~Notifiee();
            Notifiee(std::string _name, Segment * seg);
        };
        void notifieeIs(string name_, Notifiee*);

    protected:
        Segment(const string &_name, SegmentType _st);
        Segment();
        Segment(const Segment&);
        Notifiee::Ptr notifiee_;
        std::queue<Fwk::Ptr<Shipment> > shipment_;
        string source_;
        Miles length_;
        string returnSegment_;
        SegmentDifficulty difficulty_;
        PackageCount capacity_;
        PackageCount activePackages_;
        ExpediteSupport expediteSupport_;
        SegmentType type_;
    };

    class TruckSegment : public Segment {
    public:
        typedef Fwk::Ptr<TruckSegment const> PtrConst;
        typedef Fwk::Ptr<TruckSegment> Ptr;
        virtual ~TruckSegment();
        static Ptr TruckSegmentNew(const string &_name);
    protected:
        TruckSegment(const string &_name);
        TruckSegment();
        TruckSegment(const TruckSegment&);
    };

    class BoatSegment : public Segment {
    public:
        typedef Fwk::Ptr<BoatSegment const> PtrConst;
        typedef Fwk::Ptr<BoatSegment> Ptr;
        virtual ~BoatSegment();
        static Ptr BoatSegmentNew(const string &_name);
    protected:
        BoatSegment(const string &_name);
        BoatSegment();
        BoatSegment(const BoatSegment&);

    };

    class PlaneSegment : public Segment {
    public:
        typedef Fwk::Ptr<PlaneSegment const> PtrConst;
        typedef Fwk::Ptr<PlaneSegment> Ptr;
        virtual ~PlaneSegment();
        static Ptr PlaneSegmentNew(const string &name);
    protected:
        PlaneSegment(const string &_name);
        PlaneSegment();
        PlaneSegment(const PlaneSegment&);
    };

} // end namespace
#endif
