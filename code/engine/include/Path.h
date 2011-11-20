#ifndef PATH_H
#define PATH_H

#include "Utils.h"
#include "Location.h"
#include "Segment.h"
#include <queue>
#include <list>

namespace Shipping {
    class Conn;
    class ExploreData {
    public:
        ExploreData() :
          distance_(Miles::max()),
              cost_(Dollars::max()),
              time_(Hours::max()),
              expedited_(Segment::noExpediteSupport()) {};

          Miles distance() const { return distance_;};
          Dollars cost() const { return cost_;};
          Hours time() const { return time_;};
          Segment::ExpediteSupport expedited() const { return expedited_;};

          void distanceIs(Miles m) { distance_ = m;};
          void costIs(Dollars d) { cost_ = d;};
          void timeIs(Hours h) { time_ = h;};
          void expeditedIs(Segment::ExpediteSupport e) { expedited_ = e;};

    private:
        Miles distance_;
        Dollars cost_;
        Hours time_;
        Segment::ExpediteSupport expedited_;
    };
    struct PathItem{
        Segment::PtrConst seg; //segment _TO_ 'loc'
        Segment::PtrConst returnSeg; //segment _FROM_ 'loc'
        Location::PtrConst loc;
    };
    class Path : public Fwk::PtrInterface<Path> {
    public:
        typedef Fwk::Ptr<Path const> PtrConst;
        typedef Fwk::Ptr<Path> Ptr;
        Path();
        Ptr cloneIs();
        void nextPathItemIs(PathItem p);
        PathItem lastPathItem() const { return traversedItems_.back();}
        Dollars cost() const {return cost_;};
        void costIs(Dollars);
        Hours time() const { return time_; };
        void timeIs(Hours);
        typedef list<PathItem>::iterator PathItemIterator;
        typedef list<PathItem>::const_iterator PathItemIteratorConst;
        PathItemIterator pathItemIter() { return traversedItems_.begin(); };
        PathItemIteratorConst pathItemIterConst() const{ return traversedItems_.begin(); };
        unsigned int pathItems() const { return traversedItems_.size(); };
        void expediteSupportIs(Segment::ExpediteSupport);
        Segment::ExpediteSupport expediteSupport() const { return expediteSupport_;};
        PathItem pathItem(PathItemIterator it) const { return *it; };
    private:
        Path(const Path&);
        list<PathItem> traversedItems_;
        Dollars cost_;
        Hours time_;
        Segment::ExpediteSupport expediteSupport_;
    };
    class PathTree : public Fwk::PtrInterface<PathTree>{
    public:
        typedef Fwk::Ptr<PathTree const> PtrConst;
        typedef Fwk::Ptr<PathTree> Ptr;
        typedef list<Path::Ptr>::iterator PathIterator;
        typedef list<Path::Ptr>::const_iterator PathIteratorConst;
        PathIteratorConst pathIterConst() const{ return path_.begin(); };
        PathIterator pathIter() { return path_.begin(); };
        Path::Ptr path(PathIterator it) const { return *it; };
        unsigned int paths() const { return path_.size();};
    protected:
        PathTree(Location::PtrConst, Conn *);
        PathTree();
        PathTree(const PathTree &);
        queue<Path::Ptr> queue_;
        list<Path::Ptr> path_;
        Conn * owner_;
        enum Addable {
            addable_ = 0,
            locAlreadyExists_ = 1,
            expeditedNotMatching_ = 2,
            moneyLimitReached_ = 3,
            timeLimitReached_ = 4
        };
        PathItem pathItem(Segment::PtrConst) ;
        Path::Ptr addChildren(unsigned int, Path::Ptr, Path::Ptr, PathItem);
        MilesPerHour speed(Segment::SegmentType st) const;
        DollarsPerMile cost(Segment::SegmentType st) const;
        float segmentCost(Segment::PtrConst, Segment::ExpediteSupport) const;
        float segmentTime(Segment::PtrConst, Segment::ExpediteSupport) const;
        Segment::PtrConst seg(const string & _name);
        bool segExists(const string & _name);
        Location::PtrConst loc(const string & _name);
        bool locExists(const string & _name);
    };

    class ExplorePathTree : public PathTree {
    public:
        ExplorePathTree(ExploreData, Location::PtrConst, Conn *);
    private:
        void processQueueFront();
        Addable isAddable(Path::Ptr, PathItem);
        ExploreData exploreData_;
    };

    class ConnectPathTree : public PathTree {
    public:
        ConnectPathTree(Location::PtrConst, Location::PtrConst, Conn *);
    private:
        Location::PtrConst end_;
        void processQueueFront();
        Addable isAddable(Path::Ptr, PathItem);
    };

}; // end namespace
#endif
