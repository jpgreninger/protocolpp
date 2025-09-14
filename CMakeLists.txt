# cmake_minimum_required(VERSION 3.0.10)
project(protocolpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    include/jarray.h
    include/jip.h
    include/jprotocol.h
    include/jrand.h
    include/jstuff.h
    include/jtcp.h
    include/judp.h
    include/mtrand.h
    src/jbuilder.cpp
    src/jip.cpp
    src/jprotocol.cpp
    src/jtcp.cpp
    src/judp.cpp
    src/mtrand.cpp)

add_executable(protocolpp ${SOURCE_FILES})
