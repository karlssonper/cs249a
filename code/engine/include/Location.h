#ifndef LOCATION_H_
#define LOCATION_H_

#include "NamedInterface.h"
#include "Ptr.h"
#include "Segment.h"
#include <string>
#include <list>
#include "Activity.h"

using std::string;
using std::list;

namespace Shipping {
    class Location : public Fwk::NamedInterface {

    public:
        typedef Fwk::Ptr<Location const> PtrConst;
        typedef Fwk::Ptr<Location> Ptr;
        virtual ~Location();

        enum LocationType {
            customer_ = 0,
            port_ = 1,
            truckTerminal_ = 2,
            boatTerminal_ = 3,
            planeTerminal_ = 4
        };

        static inline LocationType customer() { return customer_; }
        static inline LocationType port() { return port_; }
        static inline LocationType truckTerminal() { return truckTerminal_; }
        static inline LocationType boatTerminal() { return boatTerminal_; }
        static inline LocationType planeTerminal() { return planeTerminal_; }

        LocationType type() const { return type_; }

        void outSegmentNew(Segment::Ptr);
        void outSegmentDel(Segment::Ptr); 

        unsigned int outSegments() const { return outSegment_.size(); }
        typedef list<Segment::Ptr>::iterator OutSegmentIterator;
        typedef list<Segment::Ptr>::const_iterator OutSegmentIteratorConst;

        OutSegmentIteratorConst outSegmenterIterConst() const { return outSegment_.begin(); };
        OutSegmentIteratorConst outSegmenterIterConst(const unsigned int) const;

        OutSegmentIterator outSegmenterIter() { return outSegment_.begin(); };
        OutSegmentIterator outSegmenterIter(const unsigned int) ;

        Segment::Ptr outSegment(OutSegmentIteratorConst) const;

    protected:
        Location(const string &_name, LocationType _type);
        Location(const Location & );
        Location();
        list<Segment::Ptr> outSegment_;
        LocationType type_;
        
    };   

    class Customer : public Location {
    public:
        typedef Fwk::Ptr<Customer const> PtrConst;
        typedef Fwk::Ptr<Customer> Ptr;
        virtual ~Customer();
        static Ptr CustomerNew(const string &_name);

        class Notifiee : public Fwk::BaseNotifiee<Customer> {
        public:
            typedef Fwk::Ptr<Customer::Notifiee const> PtrConst;
            typedef Fwk::Ptr<Customer::Notifiee> Ptr;

            virtual void onAtttributeUpdate() {}

            virtual ~Notifiee() {}
            Notifiee(std::string _name, Customer* _notifier) 
            : BaseNotifiee<Customer>(_name, _notifier) {}
        };

        void notifieeIs(const string &_name, Notifiee* _notifiee);

        // accessors
        TransferRate transferRate() const { return transferRate_; }
        PackageCount shipmentSize() const { return shipmentSize_; }
        string destination() const { return destination_; }
        PackageCount recievedPackages() const { return recievedPackages_; }
        Latency averageLatency() const { return averageLatency_; }
        Dollars totalCost() const { return totalCost_; }

        // mutators
        void transferRateIs(TransferRate _transferRate);
        void shipmentSizeIs(PackageCount _shipmentSize);
        void destinationIs(const string &_destination);
        void recievedPackagesIs(PackageCount _recievedPackages);
        void averageLatencyIs(Latency _averageLatency);
        void totalCostIs(Dollars _totalCost);

    protected:
        Customer(const string &_name);
        Customer();
        Customer(const Customer&);

        // for producing customers
        TransferRate transferRate_;
        PackageCount shipmentSize_;
        string destination_;

        // for recieving customers
        PackageCount recievedPackages_;
        Latency averageLatency_;
        Dollars totalCost_;

        Notifiee* notifiee_;
    };

    class Port : public Location {
    public:
        typedef Fwk::Ptr<Port const> PtrConst;
        typedef Fwk::Ptr<Port> Ptr;
        virtual ~Port();
        static Ptr PortNew(const string &_name);
    protected:
        Port(const string &_name);
        Port();
        Port(const Port&);
    };

    class TruckTerminal : public Location {
    public:
        typedef Fwk::Ptr<TruckTerminal const> PtrConst;
        typedef Fwk::Ptr<TruckTerminal> Ptr;
        virtual ~TruckTerminal();
        static Ptr TruckTerminalNew(const string &_name);
    protected:
        TruckTerminal(const string &_name);
        TruckTerminal();
        TruckTerminal(const TruckTerminal&);
    };

    class BoatTerminal : public Location {
    public:
        typedef Fwk::Ptr<BoatTerminal const> PtrConst;
        typedef Fwk::Ptr<BoatTerminal> Ptr;
        virtual ~BoatTerminal();
        static Ptr BoatTerminalNew(const string &_name);
    protected:
        BoatTerminal(const string &_name);
        BoatTerminal();
        BoatTerminal(const BoatTerminal&);
    };

    class PlaneTerminal : public Location {
    public:
        typedef Fwk::Ptr<PlaneTerminal const> PtrConst;
        typedef Fwk::Ptr<PlaneTerminal> Ptr;
        virtual ~PlaneTerminal();
        static Ptr PlaneTerminalNew(const string &_name);
    protected:
        PlaneTerminal(const string &_name);
        PlaneTerminal();
        PlaneTerminal(const PlaneTerminal&);
    };

} // end namespace Shipping
#endif /* LOCATION_H_ */
