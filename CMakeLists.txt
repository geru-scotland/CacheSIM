cmake_minimum_required(VERSION 3.23)
project(CacheSIM)

include_directories(include)

set(CMAKE_CXX_STANDARD 20)


add_executable(CacheSIM main.cpp
        src/CacheMemory/CacheMap.cpp
        include/CacheMap.h
        src/CacheMemory/CacheMgr.cpp
        include/CacheMgr.h
        src/Simulator.cpp
        include/Simulator.h include/SharedDefines.h src/DataMgr.cpp include/DataMgr.h)
