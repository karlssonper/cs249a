#include "Path.h"
#include "Debug.h"
#include "Conn.h"
#include "Engine.h"
#include "Fleet.h"
using namespace Shipping;

Path::Ptr Path::cloneIs() {
    FWK_DEBUG("Conn::Path::cloneIs()");
    Path::Ptr clonedPath = new Path();
    clonedPath->traversedItems_ = traversedItems_;
    clonedPath->costIs(cost());
    clonedPath->timeIs(time());
    clonedPath->distanceIs(distance());
    return clonedPath;
};

void Path::nextPathItemIs(PathItem pI) {
    if (pI.seg && pI.loc) {
        FWK_DEBUG("Conn::Path::nextPathItemIs() with : " << pI.seg->source() << "->" <<
            pI.seg->name() << "->" << pI.loc->name());
    } else {
        FWK_DEBUG("Conn::Path::nextPathItemIs() with : " << "" << "->" <<
            "" << "->" << pI.loc->name());
    }
    traversedItems_.push_back(pI);

#ifdef DEBUG_OUTPUT
    std::cout << "New Path is: ";
    PathItemIterator pIIt = pathItemIter();
    for (unsigned int j = 0; j < pathItems(); ++j, ++pIIt) {
        std::cout << pIIt->loc->name() << "->";
    }
    std::cout <<std::endl;
#endif
}

void Path::costIs(Dollars d){
    FWK_DEBUG("Conn::Path::costIs() with cost: " << d.value());
    if (cost() == d) return;
    else cost_ = d;
}

void Path::timeIs(Hours h){
    FWK_DEBUG("Conn::Path::timeIs() with time: " << h.value());
    if (time() == h) return;
    else time_ = h;
}

PathTree::PathTree(Location::PtrConst _root, Conn * _owner) : owner_(_owner)
{
    FWK_DEBUG("Conn::PathTree::PathTree() with root: " << _root->name());
    PathItem pI;
    pI.loc = _root;
    Path::Ptr p = new Path();
    p->nextPathItemIs(pI);
    path_.push_back(p);
    queue_.push(path_.back());
};

ExplorePathTree::ExplorePathTree(ExploreData _ed, 
    Location::PtrConst _root, Conn * _owner) : 
PathTree(_root, _owner) , exploreData_(_ed)   
{
    FWK_DEBUG("Conn::ExplorePathTree::ExplorePathTree() with root: " << _root->name());
    while(!queue_.empty()){
        FWK_DEBUG("Conn::ExplorePathTree::ExplorePathTree() queue size: " << queue_.size());
        processQueueFront();
        queue_.pop();
    }
    if (path_.front()->pathItems() == 1) path_.clear(); //if only starter root
};

ConnectPathTree::ConnectPathTree(Location::PtrConst _root, Location::PtrConst _end, 
    Conn * _owner) : PathTree(_root, _owner), end_(_end)
{
    FWK_DEBUG("Conn::ConnectPathTree::ConnectPathTree() with root: " << _root->name());
    while(!queue_.empty()){
        FWK_DEBUG("Conn::ConnectPathTree::ConnectPathTree() queue size: " << queue_.size());
        processQueueFront();
        queue_.pop();
    }
    PathIterator it = pathIter();
    unsigned int i = 0;
    unsigned int n =paths();
    while (i < n){
        PathIterator curIt = path_.end();
        //std::cout << (*it)->lastPathItem().loc->name() << " " << end_->name();
        if ((*it)->lastPathItem().loc->name() != end_->name()) {// || (*curIt)->pathItems() == 1)
            curIt = it;
            //std::cout << " DELETE";
        }
        //std::cout << std::endl;
        ++it; ++i;
        if (curIt != path_.end())
            path_.erase(curIt);
    }
};

void ExplorePathTree::processQueueFront() {
    Path::Ptr frontPath = queue_.front();
    FWK_DEBUG("Conn::ExplorePathTree::processQueueFront() with path: " << frontPath->lastPathItem().loc->name() );
    unsigned int children = 0;
    Location::PtrConst curLoc = frontPath->lastPathItem().loc;
    Location::OutSegmentIteratorConst it = curLoc->outSegmenterIterConst();
    Path::Ptr curPath = frontPath->cloneIs();
    for (unsigned int i = 0; i < curLoc->outSegments(); ++it, ++i){
        if (!segExists((*it)->name())) continue; 
        PathItem pI = pathItem(*it);
        if (isAddable(frontPath, pI) == addable_) {
            ++children;
            addChildren(children, curPath, frontPath, pI);
        }
    }
    if (children != 0 && curPath->pathItems() > 1){
        path_.push_back(curPath->cloneIs());//add current
    }
};

void Path::distanceIs(Miles m) {
    if (distance_ != m) {
        distance_ = m;
    }
};

PathTree::Addable ExplorePathTree::isAddable(Path::Ptr p, PathItem pI) {
    Path::PathItemIterator it = p->pathItemIter();
    for (unsigned int i= 0 ; i < p->pathItems(); ++i, ++it){
        if (it->loc->name() == pI.loc->name()){
            FWK_DEBUG("Conn::isAddable() with curLoc: " << pI.loc->name() << " returns false(locAlreadyExists_)");
            return locAlreadyExists_;
        }
    }
    if (!pI.seg){
        FWK_DEBUG("Conn::isAddable() with curLoc: " << pI.loc->name() << " returns true");
        return addable_;//root
    }
    if ((exploreData_.expedited() == Segment::fullExpediteSupport()) &&
        pI.seg->expediteSupport() == Segment::noExpediteSupport()){
            FWK_DEBUG("Conn::isAddable() with curLoc: " << pI.loc->name() << " returns false(expeditedNotMatching_)");
            return expeditedNotMatching_;
    }
    if (p->cost() + segmentCost(pI.seg, p->expediteSupport()) > exploreData_.cost()){
        FWK_DEBUG("Conn::isAddable() with curLoc: " << pI.loc->name() << " returns false(moneyLimitReached_)");
        return moneyLimitReached_;
    }
    if (p->time() + segmentTime(pI.seg, p->expediteSupport()) > exploreData_.time()){
        FWK_DEBUG("Conn::isAddable() with curLoc: " << pI.loc->name() << " returns false(timeLimitReached_)");
        return timeLimitReached_;
    }
    if (p->distance() + pI.seg->length() > exploreData_.distance()) {
        FWK_DEBUG("Conn::isAddable() with curLoc: " << pI.loc->name() << " returns false(lengthMaxReached)");
        return lengthMaxReached_;
    }
    FWK_DEBUG("Conn::isAddable() with curLoc: " << pI.loc->name() << " returns true");
    return addable_;
};

void ConnectPathTree::processQueueFront() {
    Path::Ptr frontPath = queue_.front();
    if (frontPath->lastPathItem().loc->name() == end_->name()) return;
    FWK_DEBUG("Conn::ExplorePathTree::processQueueFront() with path: " << frontPath->lastPathItem().loc->name() );
    unsigned int children = 0;
    Location::PtrConst curLoc = frontPath->lastPathItem().loc;
    Location::OutSegmentIteratorConst it = curLoc->outSegmenterIterConst();
    Path::Ptr curPath = frontPath->cloneIs();
    for (unsigned int i = 0; i < curLoc->outSegments(); ++it, ++i){
        if (!segExists((*it)->name())) continue; 
        PathItem pI = pathItem(*it);
        if (isAddable(frontPath, pI) == addable_) {
            ++children;
            Path::Ptr newPath = addChildren(children, curPath, frontPath, pI);
            if (queue_.back()->lastPathItem().seg->expediteSupport() == Segment::noExpediteSupport() &&
                queue_.back()->expediteSupport() == Segment::fullExpediteSupport()) {
                queue_.back()->expediteSupportIs( Segment::noExpediteSupport());
            } 
            
            if (queue_.back()->expediteSupport() == Segment::fullExpediteSupport() &&
                queue_.back()->lastPathItem().loc->name() == end_->name()) {
                ++children;
                addChildren(children, curPath, frontPath, pI);
                queue_.back()->expediteSupportIs( Segment::noExpediteSupport());
                queue_.back()->costIs(Dollars(queue_.back()->cost().value() * (2.0/3.0)));
                queue_.back()->timeIs(Hours(queue_.back()->time().value()  * 1.3));
            }
        }
    }
};

void Path::expediteSupportIs(Segment::ExpediteSupport es){
    expediteSupport_ = es;
};

Path::Ptr PathTree::addChildren(unsigned int children, 
    Path::Ptr curPath, Path::Ptr frontPath, PathItem pI) {
        if (children > 1){
            FWK_DEBUG("Conn::ExplorePathTree::processQueueFront() adding new Path to queue");
            Path::Ptr newPath = curPath->cloneIs();
            newPath->costIs(Dollars(newPath->cost().value() + segmentCost(pI.seg, newPath->expediteSupport())));
            newPath->timeIs(Hours(newPath->time().value() + segmentTime(pI.seg, newPath->expediteSupport())));
            newPath->distanceIs(Miles(newPath->distance().value() + pI.seg->length().value()));
            path_.push_back(newPath);
            queue_.push(path_.back());
        } else {
            FWK_DEBUG("Conn::ExplorePathTree::processQueueFront() adding same Path to queue");
            frontPath->costIs(Dollars(frontPath->cost().value() + segmentCost(pI.seg, frontPath->expediteSupport())));
            frontPath->timeIs(Hours(frontPath->time().value() + segmentTime(pI.seg, frontPath->expediteSupport())));
            queue_.push(frontPath);
        }
        queue_.back()->nextPathItemIs(pI);
        return queue_.back();
};

Path::Path() : cost_(0), time_(0), distance_(0), expediteSupport_(Segment::fullExpediteSupport()){};

PathItem PathTree::pathItem(Segment::PtrConst p) {
    Segment::PtrConst retSeg = seg(p->returnSegment());
    PathItem pI;
    pI.loc = loc(retSeg->source());
    pI.seg = p ;
    pI.returnSeg = seg(p->returnSegment());
    return pI;
}

PathTree::Addable ConnectPathTree::isAddable(Path::Ptr p, PathItem pI) {
    Path::PathItemIterator it = p->pathItemIter();
    for (unsigned int i= 0 ; i < p->pathItems(); ++i, ++it){
        if (it->loc->name() == pI.loc->name()){
            FWK_DEBUG("Conn::isAddable() with curLoc: " << pI.loc->name() << " returns false(locAlreadyExists_)");
            return locAlreadyExists_;
        }
    }
    FWK_DEBUG("Conn::isAddable() with curLoc: " << pI.loc->name() << " returns true");
    return addable_;
};

MilesPerHour PathTree::speed(Segment::SegmentType st) const{
    switch(st) {
    case Segment::truckSegment_:
        return owner_->owner_->fleet()->speed(Shipping::Fleet::truck());                
    case Segment::boatSegment_:
        return owner_->owner_->fleet()->speed(Shipping::Fleet::boat());
    case Segment::planeSegment_:
        return owner_->owner_->fleet()->speed(Shipping::Fleet::plane());
    default:
        cerr << "PathTree:: speed out of range" << endl;
        throw(Fwk::RangeException("PathTree::speed"));
    }
};

DollarsPerMile PathTree::cost(Segment::SegmentType st) const{
    switch(st){
    case Segment::truckSegment_:
        return owner_->owner_->fleet()->cost(Shipping::Fleet::truck());                
    case Segment::boatSegment_:
        return owner_->owner_->fleet()->cost(Shipping::Fleet::boat());
    case Segment::planeSegment_:
        return owner_->owner_->fleet()->cost(Shipping::Fleet::plane());
    default:
        cerr << "PathTree::cost out of range" << endl;
        throw(Fwk::RangeException("PathTree::cost"));
    }
};

float PathTree::segmentCost(Segment::PtrConst s, Segment::ExpediteSupport expediteSupport) const{
    Segment::SegmentType st = s->type();
    float newCost = s->length().value() * cost(st).value() * s->difficulty().value();
    if (s->expediteSupport() == Segment::fullExpediteSupport() && expediteSupport == Segment::fullExpediteSupport()){
        newCost*= 1.5;
    };
    return newCost;
};
float PathTree::segmentTime(Segment::PtrConst s,Segment::ExpediteSupport expediteSupport) const{
    Segment::SegmentType st = s->type();
    float tSpeed = speed(st).value();
    if (s->expediteSupport() == Segment::fullExpediteSupport() && expediteSupport == Segment::fullExpediteSupport()){
        tSpeed *= 1.3;
    };
    return s->length().value() / tSpeed;
};

Segment::PtrConst PathTree::seg(const string & _name) {
    if (!segExists(_name)) {
        cerr << "PathTree::seg segment does not exist" << endl;
        throw(Fwk::EntityNotFoundException("PathTree::seg"));
    }
    return owner_->graphSegment_[_name];
};

bool PathTree::segExists(const string & _name) {
    return owner_->graphSegment_.find(_name) != 
        owner_->graphSegment_.end();
};
Location::PtrConst PathTree::loc(const string & _name)
{
    if (!locExists(_name)) {
        cerr << " PathTree::loc location does not exist" << endl;
        throw(Fwk::EntityNotFoundException("PathTree::loc"));
    }
    return owner_->graphLocation_[_name];
};

bool PathTree::locExists(const string & _name) {
    return owner_->graphLocation_.find(_name) != 
        owner_->graphLocation_.end();
};



