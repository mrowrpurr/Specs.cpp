find_path(SNOWHOUSE_INCLUDE_DIRS "snowhouse/snowhouse.h")

add_executable(ExampleSpecs RunSpecs.cpp)
target_link_libraries(ExampleSpecs PRIVATE Spec)
target_include_directories(ExampleSpecs PRIVATE .)
target_include_directories(ExampleSpecs PRIVATE ${SNOWHOUSE_INCLUDE_DIRS})
