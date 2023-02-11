add_executable(ExampleSpecs RunSpecs.cpp)
target_link_libraries(ExampleSpecs PRIVATE Spec)
target_include_directories(ExampleSpecs PRIVATE .)
