project(CLI.Stuff)
add_executable(${PROJECT_NAME} CLI.Stuff.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE Specs)
