project(Assert.Spec)
add_executable(${PROJECT_NAME} Assert.Spec.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE spec)
