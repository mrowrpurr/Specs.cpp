project(spec-snowhouse VERSION 0.1.0 LANGUAGES CXX)

find_path(SNOWHOUSE_INCLUDE_DIRS "snowhouse/snowhouse.h")

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE include)
target_include_directories(${PROJECT_NAME} INTERFACE ${SNOWHOUSE_INCLUDE_DIRS})

add_subdirectory(example)
