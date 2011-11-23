#ifndef FLEET_H
#define FLEET_H

#include <string>
#include "Ptr.h"
#include "NamedInterface.h"
#include "Utils.h"

namespace Shipping {

using std::string;

class EngineManager;

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

    MilesPerHour speed(Vehicle _vehicle) const { return vehicleData_[_vehicle].speed_; }
    void speedIs(Vehicle _vehicle, MilesPerHour _speed);
    DollarsPerMile cost(Vehicle _vehicle) const { return vehicleData_[_vehicle].cost_; }
    void costIs(Vehicle _vehicle, DollarsPerMile _cost);
    PackageCount capacity(Vehicle _vehicle) const { return vehicleData_[_vehicle].capacity_; }
    void capacityIs(Vehicle _vehicle, PackageCount capacity_);

    virtual ~Fleet();
    static Fleet::Ptr FleetNew(const string &_name);
   
private:
     Fleet();
     Fleet(const Fleet &);
     Fleet(const string &_name);
     Data vehicleData_[3];
};

} // end namespace

#endif
