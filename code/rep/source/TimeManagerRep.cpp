#include "TimeManagerRep.h"
#include "VirtualTimeActivityManager.h"
#include "RealTimeActivityManager.h"
#include "Engine.h"
#include <sstream>

using namespace Shipping;

TimeManagerRep::TimeManagerRep(const string &_name,
        Ptr<EngineManager> _engineManager) :
DeletableInstance(_name), engineManager_(_engineManager) {}

string TimeManagerRep::attribute(const string &_attributeName) {
    if (_attributeName == "simulation end" ) {
        Fwk::Time simEnd =
                engineManager_->virtualTimeActivityManager()->simluationEnd();
        std::stringstream ss;
        ss << simEnd.value();
        return ss.str();
    } else if (_attributeName == "time scale") {
        RealTimeActivityManager::TimeScale ts =
                engineManager_->realTimeActivityManager()->scale();
        std::stringstream ss;
        ss << ts.value();
        return ss.str();
    }
}

void TimeManagerRep::attributeIs(const string &_attributeName,
        const string &_value) {
    ostringstream s;
    if (_attributeName == "simulation end" ) {
        float t = atof(_value.c_str());
        Fwk::Time time(t);
        engineManager_->virtualTimeActivityManager()->simluationEndIs(time);
    } else if (_attributeName == "time scale") {
        float t = atof(_value.c_str());
        RealTimeActivityManager::TimeScale time(t);
        engineManager_->realTimeActivityManager()->scaleIs(t);
    } else {
        cerr << "TimeManagerRep::attributeIs unknown attribute name" << endl;
    }
}

