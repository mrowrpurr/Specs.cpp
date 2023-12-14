set(LIBRARY_NAME specs)

add_library(${LIBRARY_NAME} INTERFACE)

add_library(specs_main STATIC ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

# Note: C++17 would be ok if `fmt` is used, but this library relies on <string_format.h>
# which requires EITHER fmt OR C++20 (for the <format> header)
target_compile_features(specs_main PRIVATE cxx_std_20)

target_link_libraries(specs_main PUBLIC ${LIBRARY_NAME})

target_include_directories(${LIBRARY_NAME} INTERFACE
    # The C++ interfaces
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Specs.API/include>

    # Support for shared DLLs
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Specs.DLL/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Specs.DllLoader/include>

    # Core implementation classes for main interfaces
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Specs.Implementations/include>

    # Available Runners and Reporters
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Specs.Runners/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Specs.Reporters/include>

    # main() entrypoint
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Specs.Main/include>

    # DSLs for defining specs
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Specs.DSLs/include>

    # Provides <Specs.h> helper header
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Specs/include>

    $<INSTALL_INTERFACE:include>
)

find_package(function_pointer CONFIG REQUIRED)
find_package(global_macro_functions CONFIG REQUIRED)
find_package(collections CONFIG REQUIRED)
find_package(_Log_ CONFIG REQUIRED)
find_package(string_format CONFIG REQUIRED)
find_package(cxxopts CONFIG REQUIRED)

target_link_libraries(
    ${LIBRARY_NAME} INTERFACE
    function_pointer::function_pointer
    global_macro_functions::global_macro_functions
    collections::collections
    _Log_::_Log_
    string_format::string_format
    cxxopts::cxxopts
)

include(GNUInstallDirs)

install(TARGETS specs_main
    EXPORT ${LIBRARY_NAME}Targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(TARGETS ${LIBRARY_NAME}
    EXPORT ${LIBRARY_NAME}Targets
    INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

if(NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
    # The C++ interfaces
    install(DIRECTORY Specs.API/include/ DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")

    # Support for shared DLLs
    install(DIRECTORY Specs.DLL/include/ DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")
    install(DIRECTORY Specs.DllLoader/include/ DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")

    # Core implementation classes for main interfaces
    install(DIRECTORY Specs.Implementations/include/ DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")

    # Available Runners and Reporters
    install(DIRECTORY Specs.Runners/include/ DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")
    install(DIRECTORY Specs.Reporters/include/ DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")

    # main() entrypoint
    install(DIRECTORY Specs.Main/include/ DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")

    # DSLs for defining specs
    install(DIRECTORY Specs.DSLs/include/ DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")

    # Provides <Specs.h> helper header
    install(DIRECTORY Specs/include/ DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")
endif()

install(EXPORT ${LIBRARY_NAME}Targets
    FILE ${LIBRARY_NAME}Targets.cmake
    NAMESPACE ${namespace}::
    DESTINATION share/${LIBRARY_NAME}
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    ${LIBRARY_NAME}ConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

string(CONCAT config_cmake_in
    "@PACKAGE_INIT@\n"
    "include(CMakeFindDependencyMacro)\n"
    "find_dependency(function_pointer CONFIG)\n"
    "find_dependency(global_macro_functions CONFIG)\n"
    "find_dependency(collections CONFIG)\n"
    "find_dependency(_Log_ CONFIG)\n"
    "find_dependency(string_format CONFIG)\n"
    "find_dependency(cxxopts CONFIG)\n"
    "include(\"\${CMAKE_CURRENT_LIST_DIR}/${LIBRARY_NAME}Targets.cmake\")\n"
)
file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/${LIBRARY_NAME}Config.cmake.in" "${config_cmake_in}")

configure_package_config_file(
    "${CMAKE_CURRENT_BINARY_DIR}/${LIBRARY_NAME}Config.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/${LIBRARY_NAME}Config.cmake"
    INSTALL_DESTINATION share/${LIBRARY_NAME}
    PATH_VARS CMAKE_INSTALL_PREFIX
    NO_CHECK_REQUIRED_COMPONENTS_MACRO
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/${LIBRARY_NAME}Config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/${LIBRARY_NAME}ConfigVersion.cmake"
    DESTINATION share/${LIBRARY_NAME}
)
