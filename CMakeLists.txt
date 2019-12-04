cmake_minimum_required (VERSION 3.0)

project("HotLoadingModules")

if(UNIX)
    SET ( CMAKE_C_FLAGS "-fPIC -O3" CACHE STRING "C compile flags" FORCE)
    SET ( CMAKE_CXX_FLAGS "-std=c++11 -fPIC -O3 -ldl"
        CACHE STRING "C++ compile flags" FORCE
    )
endif(UNIX)

include_directories("include")

add_subdirectory("src")