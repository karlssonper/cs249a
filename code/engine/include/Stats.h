#ifndef STATS_H
#define STATS_H

#include "Utils.h"
#include "Location.h"
#include "Nominal.h"
#include "EntityManager.h"

namespace Shipping {
    class EngineManager;
    using std::string;
    
    class Stats : public EntityManager::Notifiee {
    public:
        typedef Fwk::Ptr<Stats const> PtrConst;
        typedef Fwk::Ptr<Stats> Ptr;

        class ExpeditedPercentage : public Ordinal<ExpeditedPercentage, double> {
        public:
            ExpeditedPercentage() : Ordinal<ExpeditedPercentage, double>(0.f) {}
            ExpeditedPercentage(double value) : Ordinal<ExpeditedPercentage, double>(value) {
                if (value < 0.0 || value > 100.0)
                {
                    std::cerr << "ExpeditedPercentage out of range, setting default value (0.0)" << std::endl;
                    value = 0.0;
                }
            };
        };

        typedef unsigned int LocationCount;
        typedef unsigned int SegmentCount;

        LocationCount customerCount() const {
            return customerCount_;
        }
        LocationCount portCount() const {
            return portCount_;
        }
        LocationCount planeTerminalCount() const {
            return planeTerminalCount_;
        }
        LocationCount boatTerminalCount() const {
            return boatTerminalCount_;
        }
        LocationCount truckTerminalCount() const {
            return truckTerminalCount_;
        }
        SegmentCount truckSegmentCount() const {
            return truckSegmentCount_;
        }
        SegmentCount boatSegmentCount() const {
            return boatSegmentCount_;
        }
        SegmentCount planeSegmentCount() const {
            return planeSegmentCount_;
        }
        ExpeditedPercentage expeditedPercentage() const {
            return expeditedPercentage_;
        }

        virtual void onSegmentNew(Segment::PtrConst);
        virtual void onSegmentDel(Segment::PtrConst);
        virtual void onLocationNew(Location::PtrConst);
        virtual void onLocationDel(Location::PtrConst);
        virtual void onSegmentExpUpdate(Segment::PtrConst);

        virtual ~Stats();
        static Stats::Ptr StatsNew(std::string _name, 
                                   const EngineManager * _owner,
                                   EntityManager * _entityManager);
    protected:
        Stats();
        Stats(const Stats & );
        Stats(std::string &, const EngineManager *, EntityManager *);
        const EngineManager * owner_;

        void updateExpPercentage();

        LocationCount customerCount_;
        LocationCount portCount_;
        LocationCount boatTerminalCount_;
        LocationCount planeTerminalCount_;
        LocationCount truckTerminalCount_;
        SegmentCount truckSegmentCount_;
        SegmentCount boatSegmentCount_;
        SegmentCount planeSegmentCount_;
        SegmentCount totalSegmentCount_;
        SegmentCount expeditedSupportCount_;
        ExpeditedPercentage expeditedPercentage_;

    };

}; // end namespace


#endif
