# Project name
PROJECT (CS249A_ASSIGNMENT_2_CODE_TEST)

INCLUDE_DIRECTORIES(../rep/include)

ADD_EXECUTABLE(test_cases test_cases)
TARGET_LINK_LIBRARIES(test_cases rep engine)
INSTALL (TARGETS test_cases DESTINATION bin)

ADD_EXECUTABLE(experiment experiment)
TARGET_LINK_LIBRARIES(experiment rep engine)
INSTALL (TARGETS experiment DESTINATION bin)

ADD_EXECUTABLE(verification verification)
TARGET_LINK_LIBRARIES(verification rep engine)
INSTALL (TARGETS verification DESTINATION bin)
