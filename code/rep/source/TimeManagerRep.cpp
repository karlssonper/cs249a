#include "TimeManagerRep.h"
#include "VirtualTimeActivityManager.h"
#include "RealTimeActivityManager.h"
#include "Engine.h"

using namespace Shipping;

TimeManagerRep::TimeManagerRep(const string &_name, Ptr<EngineManager> _engineManager) :
    DeletableInstance(_name), engineManager_(_engineManager) {}

string TimeManagerRep::attribute(const string &_attributename) {
    return "";
}

void TimeManagerRep::attributeIs(const string &_attributeName, const string &_value) {
}

