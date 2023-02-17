project(Spec.Specs)

find_path(SNOWHOUSE_INCLUDE_DIRS "snowhouse/assert.h")

add_executable(${PROJECT_NAME} Spec.Specs.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE spec spec-snowhouse)
target_include_directories(${PROJECT_NAME} PRIVATE ${SNOWHOUSE_INCLUDE_DIRS})
