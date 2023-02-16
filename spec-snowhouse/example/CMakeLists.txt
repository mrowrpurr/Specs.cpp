project(spec-snowhouse.example)

add_executable(${PROJECT_NAME} SnowhouseSpecExample.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE spec spec-snowhouse)
target_include_directories(${PROJECT_NAME} PRIVATE ${SNOWHOUSE_INCLUDE_DIRS})
