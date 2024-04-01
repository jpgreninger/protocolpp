cmake_minimum_required(VERSION 3.20.2)

# project variables
set(META_PROJECT_NAME        "PMIC-JESD301-2")
set(META_VERSION_MAJOR       "0")
set(META_VERSION_MINOR       "0")
set(META_VERSION_PATCH       "1")
set(META_VERSION             "${META_VERSION_MAJOR}.${META_VERSION_MINOR}.${META_VERSION_PATCH}")
set(META_NAME_VERSION        "${META_PROJECT_NAME} v${META_VERSION}")

set(PROTOCOLPP_VERSION ${META_VERSION})

message("=> Project : ${META_NAME_VERSION}")

# set compiler
#if(CMAKE_CXX_COMPILER STREQUAL "clang")
#    set(CMAKE_C_COMPILER "/usr/bin/clang")
#    set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
#    message("C_COMPILER: ${CMAKE_C_COMPILER}")
#    message("CXX_COMPILER: ${CMAKE_CXX_COMPILER}")
#else()
#    set(CMAKE_C_COMPILER "/usr/bin/gcc")
#    set(CMAKE_CXX_COMPILER "/usr/bin/g++")
#    message("C_COMPILER: ${CMAKE_C_COMPILER}")
#    message("CXX_COMPILER: ${CMAKE_CXX_COMPILER}")
#endif()

# define project
project(${META_PROJECT_NAME}
        VERSION ${META_VERSION}
        LANGUAGES CXX C)

# set CXX flags
if(CMAKE_BUILD_TYPE STREQUAL "Debug32")
    set(CMAKE_CXX_FLAGS "-std=c++17 -fPIC -pipe -m32 -O0 -g -Wall")
    message("CXX_FLAGS_DEBUG_32: ${CMAKE_CXX_FLAGS}")
elseif(CMAKE_BUILD_TYPE STREQUAL "Coverage32")
    set(CMAKE_CXX_FLAGS "-std=c++17 -fPIC -pipe -m32 -O2 -coverage")
    message("CXX_FLAGS_COVERAGE: ${CMAKE_CXX_FLAGS}")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release32")
    set(CMAKE_CXX_FLAGS "-std=c++17 -fPIC -pipe -m32 -O2")
    message("CXX_FLAGS_RELEASE_32: ${CMAKE_CXX_FLAGS}")
elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "-std=c++17 -fPIC -pipe -O0 -g -Wall")
    message("CXX_FLAGS_DEBUG: ${CMAKE_CXX_FLAGS}")
elseif(CMAKE_BUILD_TYPE STREQUAL "Coverage")
    set(CMAKE_CXX_FLAGS "-std=c++17 -fPIC -pipe -O2 -coverage")
    message("CXX_FLAGS_COVERAGE: ${CMAKE_CXX_FLAGS}")
else()
    set(CMAKE_CXX_FLAGS "-std=c++17 -fPIC -pipe -O2")
    message("CXX_FLAGS_RELEASE: ${CMAKE_CXX_FLAGS}")
endif()

# list the source files
set(INCLUDE_DIRS
    ./systemc-2.3.3/include
    ../include)

message("BUILD: ${CMAKE_BUILD_TYPE}")

if(COMMAND cmake_policy)
    cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

# add include directories
include_directories(${INCLUDE_DIRS})

ADD_LIBRARY(libsystemc STATIC IMPORTED)
SET_TARGET_PROPERTIES(libsystemc PROPERTIES IMPORTED_LOCATION libsystemc.a)

# build testrail
add_executable(testrail
    ./tb_rail.cpp
    ../src/jrail.cpp
    ./testrail.cpp)

TARGET_LINK_LIBRARIES(testrail libsystemc)

# build testdac
add_executable(testdac
    ./tb_dac.cpp
    ../src/jrail.cpp
    ../src/jdac.cpp
    ./testdac.cpp)

TARGET_LINK_LIBRARIES(testdac libsystemc)

# build testpmic
add_executable(testpmic
        ./tb.cpp
        ../src/jlogger.cpp
        ../src/jrail.cpp
        ../src/jdac.cpp
        ../src/jpmic.cpp
        ./testpmic.cpp)

TARGET_LINK_LIBRARIES(testpmic libsystemc)
