project(CLI.Stuff)
add_executable(${PROJECT_NAME} CLI.Stuff.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE Specs)

find_path(SNOWHOUSE_INCLUDE_DIRS "snowhouse/assert.h")
target_include_directories(CLI.Stuff PRIVATE ${SNOWHOUSE_INCLUDE_DIRS})
