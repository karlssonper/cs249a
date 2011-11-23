# Project name
PROJECT (CS249A_ASSIGNMENT_2_CODE_ENGINE)

INCLUDE_DIRECTORIES(include source)

SET(SOURCE source/Location 
           source/Segment
           source/Path 
           source/EntityManager 
           source/Engine 
           source/Fleet 
           source/Stats 
           source/Conn
           source/ActivityImpl
           source/Shipment
           source/ForwardActivityReactor
           source/CustomerReactor)

ADD_LIBRARY(engine_shared SHARED ${SOURCE})
ADD_LIBRARY(engine STATIC ${SOURCE})

TARGET_LINK_LIBRARIES(engine)
TARGET_LINK_LIBRARIES(engine_shared)

INSTALL (TARGETS engine DESTINATION lib)
INSTALL (TARGETS engine_shared DESTINATION lib)
INSTALL (TARGETS engine_shared DESTINATION bin)