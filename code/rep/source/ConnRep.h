/*
 * ConnRep.h
 *
 *  Created on: Nov 4, 2011
 *      Author: per
 */

#ifndef CONNREP_H_
#define CONNREP_H_

#include "DeletableInstance.h"

namespace Shipping {
class EngineManager;
class Path;
class ConnRep : public DeletableInstance {
public:
    ConnRep(const string& name, Ptr<EngineManager>);
    virtual ~ConnRep();
    virtual string attribute(const string& attributeName);
    virtual void attributeIs(const string& name, const string& v);
protected:
    virtual void del(){};
private:
    ConnRep();
    ConnRep(const ConnRep&);
    Ptr<EngineManager> engineManager_;
    string pathStr(Ptr<const Path>);
    static inline string notFound() { return string("\n");};
};

};//end namespace


#endif /* CONNREP_H_ */
