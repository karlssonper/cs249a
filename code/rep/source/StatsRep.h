#ifndef STATSREP_H_
#define STATSREP_H_

#include "DeletableInstance.h"

namespace Shipping {
class EngineManager;
class StatsRep : public DeletableInstance {
public:
    StatsRep(const string&, Ptr<EngineManager>);
    virtual ~StatsRep();
    virtual string attribute(const string& attributeName);
    virtual void attributeIs(const string& name, const string& v);
protected:
    virtual void del(){};
private:
    StatsRep();
    StatsRep(const StatsRep&);
    Ptr<EngineManager> engineManager_;
};

};//end namespace

#endif /* STATSREP_H_ */
