#ifndef MANAGERIMPL_H
#define MANAGERIMPL_H

#include "Instance.h"
#include <map>
using std::map;
namespace Shipping {
class EngineManager;
class StatsRep;
class ConnRep;
class FleetRep;
class ManagerImpl : public Instance::Manager {
public:
    ManagerImpl(string name);
    virtual ~ManagerImpl();
    virtual Ptr<Instance> instanceNew(const string& name, const string& type);
    virtual Ptr<Instance> instance(const string& name);
    virtual void instanceDel(const string& name);
private:
    ManagerImpl();
    ManagerImpl(const ManagerImpl&);
    map<string,Ptr<Instance> > instance_;
    StatsRep* stats_;
    ConnRep* conn_;
    FleetRep* fleet_;
    Ptr<EngineManager> engineManager_;
};
}

#endif
