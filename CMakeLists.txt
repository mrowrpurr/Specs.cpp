cmake_minimum_required(VERSION 3.21)

project(spec-project)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(spec)
add_subdirectory(spec-snowhouse)
