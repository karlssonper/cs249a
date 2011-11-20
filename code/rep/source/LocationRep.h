#ifndef LOCATIONREP_H_
#define LOCATIONREP_H_

#include "DeletableInstance.h"

namespace Shipping {
class EngineManager;
class LocationRep : public DeletableInstance {
public: 
    LocationRep(const string& name, Ptr<EngineManager>);
    virtual ~LocationRep();
    virtual string attribute(const string& attributeName);
    virtual void attributeIs(const string& name, const string& v);
protected:
    virtual void del();
    Ptr<EngineManager> engineManager_;
    string locationName_;
    static const string segmentStr;
    static const int segmentStrlen;
    static unsigned int segmentNumber(const string&);
};

class CustomerRep : public LocationRep {
public:
    CustomerRep(const string &, Ptr<EngineManager>);
    virtual ~CustomerRep();
protected:
    CustomerRep();
    CustomerRep(const CustomerRep&);
};

class PortRep : public LocationRep {
public:
    PortRep(const string& name, Ptr<EngineManager>);
    virtual ~PortRep();
protected:
    PortRep();
    PortRep(const PortRep&);
};

class TruckTerminalRep : public LocationRep {
public:
    TruckTerminalRep(const string& name, Ptr<EngineManager>);
    virtual ~TruckTerminalRep();
protected:
    TruckTerminalRep();
    TruckTerminalRep(const TruckTerminalRep&);
};

class BoatTerminalRep : public LocationRep {
public:
    BoatTerminalRep(const string& name, Ptr<EngineManager>);
    virtual ~BoatTerminalRep();
protected:
    BoatTerminalRep();
    BoatTerminalRep(const BoatTerminalRep&);
};

class PlaneTerminalRep : public LocationRep {
public:
    PlaneTerminalRep(const string& name, Ptr<EngineManager>);
    virtual ~PlaneTerminalRep();
protected:
    PlaneTerminalRep();
    PlaneTerminalRep(const PlaneTerminalRep&);
};

};



#endif /* LOCATIONREP_H_ */
