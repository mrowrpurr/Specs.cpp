cmake_minimum_required(VERSION 3.21)
project(MySpecs)

find_package(specs CONFIG REQUIRED)
find_package(specs_snowhouse CONFIG REQUIRED)

file(GLOB SOURCES "*.cpp")
add_executable(MySpecs ${SOURCES})

target_link_libraries(MySpecs PRIVATE specs::specs specs::specs_snowhouse)

# Use snowhouse assertions
find_path(SNOWHOUSE_INCLUDE_DIRS "snowhouse/assert.h")
target_include_directories(
    MySpecs PRIVATE
    ${SNOWHOUSE_INCLUDE_DIRS}
)
