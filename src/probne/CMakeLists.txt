project(Probne)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COMPILER_FLAGS}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${COMPILER_RELEASE_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${COMPILER_DEBUG_FLAGS}")

file(GLOB_RECURSE ${PROJECT_NAME}_headers *.h *.hpp)
file(GLOB_RECURSE ${PROJECT_NAME}_sources *.cpp *.cc *.c)

include_directories("${MAIN_PROJECT_DIR}/src")

GTEST_ADD_TESTS(KolokwiumProbneTests "" fileNumbersTests.cpp)

add_executable (${PROJECT_NAME} ${${PROJECT_NAME}_headers} ${${PROJECT_NAME}_sources})

if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    target_link_libraries(${PROJECT_NAME} Utils gtest)
else()
    target_link_libraries(${PROJECT_NAME} Utils gtest pthread)
endif()

