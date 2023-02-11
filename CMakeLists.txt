cmake_minimum_required(VERSION 3.21)

project(Spec VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(Spec INTERFACE)
target_include_directories(Spec INTERFACE include)

add_subdirectory(Example)
