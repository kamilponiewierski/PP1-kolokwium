CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

project(KolokwiumWlasciwe)

SET(VERSION_MAJOR "1")
SET(VERSION_MINOR "0")
SET(VERSION_PATCH "0")
SET(VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_C_STANDARD 11)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(MAIN_PROJECT_DIR ${PROJECT_SOURCE_DIR})

if (NOT CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    set(COMPILER_FLAGS "--std=c++17")
    set(COMPILER_DEBUG_FLAGS "-D_DEBUG")
    set(COMPILER_RELEASE_FLAGS "-O3 -DNDEBUG")
    set(LINKER_FLAGS "--std=c++17")
endif()

message("Binary tree path: ${PROJECT_BINARY_DIR}")


# downloading GTest if not installed:
set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(dima)
find_or_download_and_compile_gtest()

add_subdirectory(src/Kolokwium)
#add_subdirectory(src/probne) # tutaj jest probne kolokwium
add_subdirectory(src/utils)
