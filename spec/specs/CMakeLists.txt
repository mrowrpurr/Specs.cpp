project(Spec.Specs)

find_path(SNOWHOUSE_INCLUDE_DIRS "snowhouse/assert.h")

add_executable(${PROJECT_NAME} Specs.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE Spec)
target_include_directories(${PROJECT_NAME} PRIVATE ${SNOWHOUSE_INCLUDE_DIRS})
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_23)
