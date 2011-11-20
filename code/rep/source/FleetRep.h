#ifndef FLEETREP_H_
#define FLEETREP_H_

#include "DeletableInstance.h"
#include "Fleet.h"

namespace Shipping {
class EngineManager;
class FleetRep : public DeletableInstance {
public:
    FleetRep(const string&, Ptr<EngineManager>);
    virtual ~FleetRep();
    virtual string attribute(const string& attribute);
    virtual void attributeIs(const string& name, const string& v);
protected:
    virtual void del(){};
private:
    FleetRep();
    FleetRep(const FleetRep&);
    Ptr<EngineManager> engineManager_;
    struct FleetAttribute{
        Fleet::Vehicle vehicle;
        string prop;
    };
    FleetAttribute parseFleetAttribute(const string &);
};

};//end namespace


#endif /* FLEETREP_H_ */
