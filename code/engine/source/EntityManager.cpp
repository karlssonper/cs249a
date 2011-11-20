
// TODO: notifieeIs deletion case

#include "EntityManager.h"
#include "Debug.h"
#include <iostream>

using namespace std;

using namespace Shipping;

EntityManager::Notifiee::~Notifiee(){
    FWK_DEBUG("Notifiee::~Notifiee() with name: " << name());
};

EntityManager::Notifiee::Notifiee(std::string _name, EntityManager* em) :
Fwk::BaseNotifiee<EntityManager>(_name, em) {
    FWK_DEBUG("Notifiee::Notifiee() with name: " << name());
}

EntityManager::EntityManager(std::string & _name) :
Fwk::NamedInterface(_name) {
    FWK_DEBUG("EntityManager::EntityManager with name " << _name);
}

EntityManager::~EntityManager(){
    FWK_DEBUG("EntityManager::~EntityManager() with name: " << name());
};

void EntityManager::locationIs(string _name, Location::Ptr _location) {
    FWK_DEBUG("EntityManager::locationIs with name " << _name);

    if (location_.find(_name) != location_.end()) {
        cerr << "EntityManager::locationIs: " << _name << " is already a location." << endl;
        return;
    }

    FWK_DEBUG("EntityManager::locationIs inserting " << _name);
    location_.insert(make_pair(_name, _location));

    map<string, EntityManager::Notifiee::Ptr>::iterator i;
    for (i=notifiee_.begin(); i!=notifiee_.end(); i++) {
        FWK_DEBUG("EntityManager::locationIs notifying " << i->second->name());
        i->second->onLocationNew(_location);
    }
}

void EntityManager::segmentSourceIs(const string &_segmentName, 
    const string &_sourceName) {

        Location::Ptr lp;
        Segment::Ptr sp;

        map<string, Segment::Ptr>::iterator segIt = segment_.find(_segmentName);
        if (segIt == segment_.end()) {
            cerr << "EntityManager::segmentSourceIs: " <<  _segmentName << " was not found. " << endl;
            return;
        }

        sp = segIt->second;

        // deletion
        if (_sourceName == "" ) {
            FWK_DEBUG("EntityManager::segmentSourceIs, removing source from " << _segmentName);

            // find out if the segment has a source
            if (sp->source() != "") {
                map<string, Location::Ptr>::iterator locIt = location_.find(sp->source());
                if (locIt != location_.end()) {
                    lp = locIt->second;
                    lp->outSegmentDel(sp.ptr());
                }
            }

            sp->sourceIs("");

        } else { // not deletion

            map<string, Location::Ptr>::iterator locIt = location_.find(_sourceName);
            if (locIt == location_.end()) {
                FWK_DEBUG("EntityManager::segmentSourceIs, " << _sourceName << " not found in location_");
                cerr << _sourceName << " was not found. " << endl;
                return;
            } 

            lp = locIt->second;

            if (sp->source() == lp->name()) {
                FWK_DEBUG("EntityManager::segmentSourceIs, " << sp->source() << " is already source to " << lp->name());
                return;
            }

            Location::LocationType locType = lp->type();
            Segment::SegmentType segType = sp->type();

            if (locType == Location::truckTerminal()) {
                if (segType != Segment::truckSegment()) {
                    cerr << "EntityManager::segmentSourceIs: " << "segment/location types do not match" << endl;
                    return;
                } 
            } else if (locType == Location::boatTerminal()) {
                if (segType != Segment::boatSegment()) {
                    cerr << "EntityManager::segmentSourceIs: " << "segment/location types do not match" << endl;
                    return;
                }
            } else if (locType == Location::planeTerminal()) {
                if (segType != Segment::planeSegment()) {
                    cerr << "EntityManager::segmentSourceIs: " << "segment/location types do not match" << endl;
                    return;
                }
            }

            sp->sourceIs(_sourceName);
            lp->outSegmentNew(sp);

        }

        map<string, EntityManager::Notifiee::Ptr>::iterator it;
        for (it=notifiee_.begin(); it!=notifiee_.end(); it++) {
            FWK_DEBUG("EntityManager::segmentSourceIs notifying " << it->second->name());
            if (lp) it->second->onLocationUpdate(lp.ptr());


            if (sp) {
                FWK_DEBUG(sp->name());
                it->second->onSegmentUpdate(sp.ptr());
            }
        }
}

void EntityManager::segmentReturnSegmentIs(const string &_segmentName,
    const string &_returnSegmentName) {

        // make sure _segmentName exists
        map<string, Segment::Ptr>::iterator segIt = segment_.find(_segmentName);
        if (segIt == segment_.end()) {
            cerr << "EntityManager::segmentReturnSegmentIs: " << _segmentName << " invalid." << endl;
            return;
        }

        Segment::Ptr sp, rsp;

        // handle deletion case
        if (_returnSegmentName == "" ) {

            FWK_DEBUG("EntityManager::segmentReturnSegmentIs detaching returnSegment");

            // if there is a returnSegment specified for _segmentName,
            // remove that first and then remove for _segmentName
            sp = segIt->second;
            if (sp->returnSegment() != "") {
                FWK_DEBUG("EntityManager::segmentSourceIs, deleting returnSegments returnSegment");
                map<string, Segment::Ptr>::iterator returnIt = segment_.find(sp->returnSegment());
                // make sure the return segment exists 
                if (returnIt == segment_.end()) {
                    FWK_DEBUG("EntityManager::segmentSourceIs, " << sp->returnSegment() << " not found in segment_");
                    return;
                }
                rsp = returnIt->second;
                // remove the returns segments returnsegment
                rsp->returnSegmentIs("");
            }
            // delete the returnsegment for _segmentName
            sp->returnSegmentIs("");

        } else if (_segmentName == _returnSegmentName) { // self loop

            // in the case of self loop, detach returnsegment if there is one and set 
            // return segment to self
            sp = segIt->second;
            if (sp->returnSegment() != "") {
                FWK_DEBUG("EntityManager::segmentSourceIs, deleting returnSegments returnSegment");
                map<string, Segment::Ptr>::iterator returnIt = segment_.find(sp->returnSegment());
                // make sure the return segment exists 
                if (returnIt == segment_.end()) {
                    FWK_DEBUG("EntityManager::segmentSourceIs, " << sp->returnSegment() << " not found in segment_");
                    return;
                }
                rsp = returnIt->second;
                // remove the returns segments returnsegment
                rsp->returnSegmentIs("");
            }
            // make the self loop
            sp->returnSegmentIs(_segmentName);

        } else { // not deletion or self loop

            // make sure _returnSegmentName exists
            map<string, Segment::Ptr>::iterator returnIt = segment_.find(_returnSegmentName);
            FWK_DEBUG("Looking up _returnSegmentName");
            if (returnIt == segment_.end()) {
                cerr << "EntityManager::segmentReturnSegmentIs: " << _returnSegmentName << " invalid." << endl;
                return;
            }

            sp = segIt->second;
            rsp = returnIt->second;

            if (sp->returnSegment() == rsp->name() &&
                rsp->returnSegment() == sp->name()) {
                    FWK_DEBUG("EntityManager::segmentSourceIs, return segments already in place");
                    return;
            }

            if (sp->type() != rsp->type()) {
                cerr << "EntityManager::segmentReturnSegmentIs: " << "Segment types do not match." << endl;
                return;
            }

            // if _returnSegmentName has another return segment, this needs to be removed
            string rsrs = segment_.find(_returnSegmentName)->second->returnSegment();
            if (rsrs != "") {
                FWK_DEBUG("EntityManager::segmentReturnSegmentIs: return segment has return segment");
                Segment::Ptr rsrsp = segment_.find(rsrs)->second;
                rsrsp->returnSegmentIs("");
                map<string, EntityManager::Notifiee::Ptr>::iterator it;
                for (it=notifiee_.begin(); it!=notifiee_.end(); it++) {
                    FWK_DEBUG("EntityManager::segmentReturnSegmentIs rsrs notifying " << it->second->name());
                    if (rsrsp) it->second->onSegmentUpdate(rsrsp.ptr());
                }
            }

            sp->returnSegmentIs(_returnSegmentName);
            rsp->returnSegmentIs(_segmentName);
        }

        map<string, EntityManager::Notifiee::Ptr>::iterator it;
        for (it=notifiee_.begin(); it!=notifiee_.end(); it++) {
            FWK_DEBUG("EntityManager::segmentReturnSegmentIs notifying " << it->second->name());
            if (sp) it->second->onSegmentUpdate(sp.ptr());
            if (rsp) it->second->onSegmentUpdate(rsp.ptr());
        }
}

void EntityManager::segmentDifficultyIs(const string &_segmentName,
    SegmentDifficulty _sd) {

        map<string, Segment::Ptr>::iterator segIt = segment_.find(_segmentName);
        if (segIt == segment_.end()) {
            cerr << "EntityManager::segmentDifficultyIs: " << _segmentName << " not found." << endl;
            return;
        }

        Segment::Ptr s = segIt->second;

        if (s->difficulty() == _sd) {
            FWK_DEBUG("EntityManager::segmentDifficultyIs, " << s->name() <<
                " already has difficulty " << _sd.value());
            return;
        }

        s->difficultyIs(_sd);

        map<string, EntityManager::Notifiee::Ptr>::iterator i;
        for (i=notifiee_.begin(); i!=notifiee_.end(); i++) {
            FWK_DEBUG("EntityManager::segmentDifficultyIs notifying " << i->second->name());
            i->second->onSegmentUpdate(s.ptr());
        }
}

void EntityManager::segmentLengthIs(const string &_segmentName,
    Miles _length) {

        map<string, Segment::Ptr>::iterator segIt = segment_.find(_segmentName);
        if (segIt == segment_.end()) {
            cerr << "EntityManager::segmentLengthIs: " << _segmentName << " not found." << endl;
            return;
        }

        Segment::Ptr s = segIt->second;

        if (s->length() == _length) {
            FWK_DEBUG("EntityManager::segmentLengthIs, " << _segmentName <<
                " already has length " << _length.value());
            return;
        }

        s->lengthIs(_length);

        map<string, EntityManager::Notifiee::Ptr>::iterator i;
        for (i=notifiee_.begin(); i!=notifiee_.end(); i++) {
            FWK_DEBUG("EntityManager::segmentLengthIs notifying " << i->second->name());
            i->second->onSegmentUpdate(s.ptr());
        }
}

void EntityManager::segmentExpediteSupportIs(const string &_segmentName,
    Segment::ExpediteSupport _exp) {

        map<string, Segment::Ptr>::iterator segIt = segment_.find(_segmentName);
        if (segIt == segment_.end()) {
            cerr << "EntityManager::segmentExpediteSupportIs: " << _segmentName << " not found." << endl;
            return;
        }

        Segment::Ptr s = segIt->second;

        if (s->expediteSupport() == _exp) {
            FWK_DEBUG("EntityManager::segmentExpediteSupportIs, " << _segmentName <<
                " already has that exp support value");
            return;
        }

        s->expediteSupportIs(_exp);

        map<string, EntityManager::Notifiee::Ptr>::iterator i;
        for (i=notifiee_.begin(); i!=notifiee_.end(); i++) {
            FWK_DEBUG("EntityManager::segmentExpediteSupportIs notifying " << i->second->name());
            i->second->onSegmentExpUpdate(s.ptr());
        }
}

void EntityManager::segmentIs(string _name, Segment::Ptr _segment) {

    FWK_DEBUG("EntityManager::segmentIs with name " << _name);

    if (segment_.find(_name) != segment_.end()) {
        cerr << "EntityManager::segmentIs: " << _name << " already exists.";
        return;
    }

    FWK_DEBUG("EntityManager::segmentIs inserting " << _name);
    segment_.insert(make_pair(_name, _segment));

    map<string, EntityManager::Notifiee::Ptr>::iterator i;
    for (i=notifiee_.begin(); i!=notifiee_.end(); i++) {
        FWK_DEBUG("EntityManager::segmentIs notifying " << i->second->name());
        i->second->onSegmentNew(_segment.ptr());
    }
}

void EntityManager::notifieeIs(string _name, Notifiee* _p) {
    FWK_DEBUG("EntityManager::notifieeIs, name " << _name );

    if (!_p) {
        //notifiee_.erase(notifiee_.find(_name));
        return;
    }

    if (notifiee_.find(_name) != notifiee_.end()) {
        cerr << "EntityManager::notifieeIs: " << _name << " already exists" << endl;
        return;
    }

    Notifiee::Ptr p = _p;
    notifiee_.insert(make_pair(_name, p));
}

void EntityManager::locationDel(const string& _name) {

    map<string, Location::Ptr>::iterator it;
    it = location_.find(_name);
    if (it == location_.end()) {
        FWK_DEBUG("EntityManager::locationDel: " << _name << " not found, nothing to do.");
        return;
    }

    Location::Ptr locPtr = it->second;
    Location::OutSegmentIterator segIt = locPtr->outSegmenterIter();
    map<string, EntityManager::Notifiee::Ptr>::iterator notIt;

    for (unsigned int i=0; i<locPtr->outSegments(); ++i, ++segIt) {
        FWK_DEBUG("EntityManager::locationDel: " << _name << ": del " << (*segIt)->name() << " from outsegs");

        (*segIt)->sourceIs("");

        for (notIt=notifiee_.begin(); notIt!=notifiee_.end(); notIt++) {
            FWK_DEBUG("EntityManager::locationDel notifying " << notIt->second->name());
            notIt->second->onSegmentUpdate((*segIt).ptr());
        }

    }

    for (notIt=notifiee_.begin(); notIt!=notifiee_.end(); notIt++) {
        FWK_DEBUG("EntityManager::locationDel notifying " << notIt->second->name());
        notIt->second->onLocationDel(locPtr.ptr());
    }

    location_.erase(it);
}

void EntityManager::segmentDel(const string& _name) {

    map<string, Segment::Ptr>::iterator it;
    it = segment_.find(_name);
    if (it == segment_.end()) {
        FWK_DEBUG("EntityManager::segmentDel: " << _name << " not found, nothing to do.");
        return;
    }

    segmentReturnSegmentIs(_name, "");
    segmentSourceIs(_name, "");

    Segment::Ptr segPtr = it->second;

    map<string, EntityManager::Notifiee::Ptr>::iterator notIt;
    for (notIt=notifiee_.begin(); notIt!=notifiee_.end(); notIt++) {
        FWK_DEBUG("EntityManager::segmentDel notifying " << notIt->second->name());
        notIt->second->onSegmentDel(segPtr.ptr());
    }

    segment_.erase(it);
}



