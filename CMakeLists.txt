cmake_minimum_required(VERSION 3.21)
project(specs VERSION 0.1.0 LANGUAGES CXX)
set(namespace specs)

option(BUILD_SPECS "Build the primary specs library" OFF)
option(BUILD_SNOWHOUSE_ADAPTER "Build the snowhouse adapter" OFF)
option(BUILD_LIBASSERT_ADAPTER "Build the libassert adapter" OFF)

if(BUILD_SPECS)
    include("cmake/Specs.cmake")
endif()

if(BUILD_SNOWHOUSE_ADAPTER)
    include("cmake/SnowhouseAdapter.cmake")
endif()

if(BUILD_LIBASSERT_ADAPTER)
    include("cmake/LibAssertAdapter.cmake")
endif()
