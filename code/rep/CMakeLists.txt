# Project name
PROJECT (CS249A_ASSIGNMENT_2_CODE_REP)

INCLUDE_DIRECTORIES(../engine/include include source ../fwk)

LINK_DIRECTORIES(LIB_PATH)

SET(SOURCE source/Instance 
           source/ManagerImpl 
           source/LocationRep
           source/SegmentRep
           source/StatsRep
           source/ConnRep
           source/FleetRep
           source/TimeManagerRep)

ADD_LIBRARY(rep STATIC ${SOURCE})
ADD_LIBRARY(rep_shared SHARED ${SOURCE})

TARGET_LINK_LIBRARIES(rep engine)
TARGET_LINK_LIBRARIES(rep_shared engine_shared)

INSTALL (TARGETS rep DESTINATION lib)
INSTALL (TARGETS rep_shared DESTINATION lib)
INSTALL (TARGETS rep_shared DESTINATION bin)