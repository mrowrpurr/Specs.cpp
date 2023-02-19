project(NoDSL.Spec)
add_executable(${PROJECT_NAME} Core.Spec.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE Specs)
