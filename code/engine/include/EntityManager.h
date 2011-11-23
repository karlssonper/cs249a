#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include "NamedInterface.h"
#include "BaseNotifiee.h"
#include "Ptr.h"
#include "Segment.h"
#include "Location.h"
#include "CustomerReactor.h"
#include <string>
#include <map>

using std::map;
using std::string;
using std::list;

namespace Shipping {
    class EngineManager;
    class EntityManager : public Fwk::NamedInterface {
    public:

        typedef Fwk::Ptr<EntityManager const> PtrConst;
        typedef Fwk::Ptr<EntityManager> Ptr;

        class Notifiee : public Fwk::BaseNotifiee<EntityManager> {
        public:
            typedef Fwk::Ptr<EntityManager::Notifiee const> PtrConst;
            typedef Fwk::Ptr<EntityManager::Notifiee> Ptr;

            virtual void onSegmentNew(Segment::PtrConst) {};
            virtual void onSegmentDel(Segment::PtrConst) {};
            virtual void onLocationNew(Location::PtrConst) {};
            virtual void onLocationDel(Location::PtrConst) {};
            virtual void onSegmentUpdate(Segment::PtrConst) {};
            virtual void onLocationUpdate(Location::PtrConst) {};
            virtual void onSegmentExpUpdate(Segment::PtrConst) {};

            virtual ~Notifiee();
            Notifiee(std::string _name, EntityManager* em);
        };
        void notifieeIs(string name_, Notifiee*);

        // accessors
        Segment::PtrConst segment(string _name) const { 
            map<string, Segment::Ptr>::const_iterator it = segment_.find(_name);
            if (it != segment_.end()) {
                const Segment * segPtr = it->second.ptr();
                return Segment::PtrConst(segPtr); 
            }
            return NULL;
        }
        Location::PtrConst location(string _name) const { 
            map<string, Location::Ptr>::const_iterator it = location_.find(_name);
            if (it != location_.end()) {
                const Location * locPtr = it->second.ptr();
                return Location::PtrConst(locPtr);  
            }
            return NULL;
        }
        unsigned int segments() { return segment_.size(); }

        // mutators
        void segmentIs(string _name, Segment::Ptr _segment);
        void locationIs(string _name, Location::Ptr _location);
        void customerReactorIs(const string &_name, CustomerReactor::Ptr _customerReactor);
        void locationDel(const string &_name);
        void segmentDel(const string &_name);
        void segmentSourceIs(const string &_segmentName, const string &_sourceName);
        void segmentReturnSegmentIs(const string &_segmentName, const string &_returnSegmentName);
        void segmentDifficultyIs(const string &_segmentName, SegmentDifficulty _sd);
        void segmentLengthIs(const string &_segmentName, Miles _length);
        void segmentExpediteSupportIs(const string &_segmentName,Segment::ExpediteSupport _exp);
        void customerTransferRateIs(const string &_customerName, TransferRate _transferRate);
        void customerShipmentSizeIs(const string &_customerName, PackageCount _shipmentSize);
        void customerDestinationIs(const string &_customerName, const string &_destination);
        void customerRecievedShipmentsIs(const string &_customerName, ShipmentCount _recievedShipments);
        void customerRecievedShipmentsInc(const string &_customerName);
        void customerAverageLatencyIs(const string &_customerName, Latency _averageLatency);
        void customerTotalCostIs(const string &_customerName, Dollars _totalCost);

        virtual ~EntityManager();
        static EntityManager::Ptr EntityManagerNew(std::string _name) {
            Ptr p = new EntityManager(_name);
            return p;
        };

    protected:
        EntityManager();
        EntityManager(const EntityManager&);
        EntityManager(std::string &);
        map<string, Segment::Ptr> segment_;
        map<string, Location::Ptr> location_;
        map<string, CustomerReactor::Ptr> customerReactor_;
        map<string, EntityManager::Notifiee::Ptr> notifiee_;
    };
}

#endif
