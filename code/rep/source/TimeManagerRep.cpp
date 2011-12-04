#include "TimeManagerRep.h"
#include "VirtualTimeActivityManager.h"
#include "RealTimeActivityManager.h"
#include "Engine.h"
#include <sstream>

using namespace Shipping;

TimeManagerRep::TimeManagerRep(const string &_name, Ptr<EngineManager> _engineManager) :
DeletableInstance(_name), engineManager_(_engineManager) {}

string TimeManagerRep::attribute(const string &_attributeName) {
    if (_attributeName == "now" ) {
        return "";
    } else if (_attributeName == "time scale") {
        return "";
    }
}

void TimeManagerRep::attributeIs(const string &_attributeName, const string &_value) {
    ostringstream s;
    if (_attributeName == "now" ) {
        float t = atof(_value.c_str());
        Fwk::Time time(t);
        engineManager_->virtualTimeActivityManager()->nowIs(time);
    } else if (_attributeName == "time scale") {
    } else {
        cerr << "TimeManagerRep::attributeIs unknown attribute name" << endl;
    }
}

