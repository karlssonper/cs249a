#ifndef CONN_H
#define CONN_H

#include "Utils.h"
#include "Ptr.h"
#include "Location.h"
#include "EntityManager.h"
#include "Path.h"

namespace Shipping {
class Conn : public EntityManager::Notifiee {
public:
    typedef Fwk::Ptr<Conn const> PtrConst;
    typedef Fwk::Ptr<Conn> Ptr;
    PathTree::Ptr explore(string loc, ExploreData);
    PathTree::Ptr connect(string loc0, string loc1);

    virtual void onSegmentDel(Segment::PtrConst);
    virtual void onLocationDel(Location::PtrConst);
    virtual void onSegmentUpdate(Segment::PtrConst);
    virtual void onLocationUpdate(Location::PtrConst);

    virtual ~Conn();
    static Conn::Ptr ConnNew(std::string _name, const EngineManager * _owner,
            EntityManager * _entityManager){
        Ptr p = new Conn(_name, _owner, _entityManager);
        return p;
    };

private:
    Conn();
    Conn(const Conn & );
    Conn(std::string &, const EngineManager *, EntityManager *);
    const EngineManager * owner_;
    map<string, Segment::PtrConst> graphSegment_;
    map<string, Location::PtrConst> graphLocation_;
    void removeGraphSegment(Segment::PtrConst);
    void removeGraphLocation(Location::PtrConst);
    enum Insertable{
        insertable_ = 0,
        missingReturn_ = 1,
        missingSource_ = 2,
        missingReturnSource_ = 3
    };
    Insertable isInsertable(Segment::PtrConst);
    friend class PathTree;
};

}; // end namespace
#endif
