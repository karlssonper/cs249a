#ifndef FLEET_H
#define FLEET_H

#include <string>
#include "Ptr.h"
#include "NamedInterface.h"
#include "Utils.h"
#include "BaseNotifiee.h"

namespace Shipping {

using std::string;

class EngineManager;
class VirtualTimeActivityManager;

class Fleet : public Fwk::NamedInterface {
public:
    typedef Fwk::Ptr<Fleet const> PtrConst;
    typedef Fwk::Ptr<Fleet> Ptr;

    struct Data {
        MilesPerHour speed_;
        DollarsPerMile cost_;
        PackageCount capacity_;
    };

    enum Vehicle {
        boat_ = 0,
        truck_ = 1,
        plane_ = 2,
        undefined_ = 3
    };

    static Vehicle boat() { return boat_; }
    static Vehicle truck() { return truck_; }
    static Vehicle plane() { return plane_; }
    static Vehicle undefined() { return undefined_; }

    MilesPerHour speed(Vehicle _vehicle) const {
        return vehicleData_[_vehicle].speed_; }
    MilesPerHour speedBuffer(Vehicle _vehicle) const {
        return vehicleBufferData_[_vehicle].speed_; }
    void speedIs(Vehicle _vehicle, MilesPerHour _speed);
    void speedBufferIs(Vehicle _vehicle, MilesPerHour _speed);
    DollarsPerMile cost(Vehicle _vehicle) const {
        return vehicleData_[_vehicle].cost_; }
    DollarsPerMile costBuffer(Vehicle _vehicle) const {
        return vehicleBufferData_[_vehicle].cost_; }
    void costIs(Vehicle _vehicle, DollarsPerMile _cost);
    void costBufferIs(Vehicle _vehicle, DollarsPerMile _cost);
    PackageCount capacity(Vehicle _vehicle) const {
        return vehicleData_[_vehicle].capacity_; }
    PackageCount capacityBuffer(Vehicle _vehicle) const {
        return vehicleBufferData_[_vehicle].capacity_; }
    void capacityIs(Vehicle _vehicle, PackageCount capacity_);
    void capacityBufferIs(Vehicle _vehicle, PackageCount capacity_);

    TimeOfDay bufferStart() { return bufferStart_; }
    void bufferIs(TimeOfDay _start, TimeOfDay _end);
    TimeOfDay bufferEnd() { return bufferEnd_; }

    virtual ~Fleet();
    static Fleet::Ptr FleetNew(const string &_name,
                               Fwk::Ptr<VirtualTimeActivityManager> _vtam);

    class Notifiee : public Fwk::BaseNotifiee<Fleet> {
    public:
        typedef Fwk::Ptr<Fleet::Notifiee const> PtrConst;
        typedef Fwk::Ptr<Fleet::Notifiee> Ptr;

        virtual void onTimeChange() {};

        virtual ~Notifiee() {}
        Notifiee(const std::string &_name, Fleet *_notifier);
    };

    void notifieeIs(const string &_name, Notifiee::Ptr _notifiee);
    void swapData();
   
protected:
     Fleet();
     Fleet(const Fleet &);
     Fleet(const string &_name, Fwk::Ptr<VirtualTimeActivityManager> _vtam);

     Data vehicleData_[3];
     Data vehicleBufferData_[3];

     // times between which 'buffered' data becomes active
     TimeOfDay bufferStart_;
     TimeOfDay bufferEnd_;

     Fwk::Ptr<VirtualTimeActivityManager> virtualTimeActivityManager_;

     Notifiee::Ptr notifiee_;
};

} // end namespace

#endif
