find_path(SNOWHOUSE_INCLUDE_DIRS "snowhouse/assert.h")
find_path(BANDIT_INCLUDE_DIRS "bandit/adapters.h")

# add_subdirectory() isn't used to keep the spec directories nice and clean
# and easy to navigate.
#
# Only *.Spec.h files are found in the subdirectories for each test suite.

add_executable(Core.Specs AddSpecsToThisList.cpp)
target_compile_definitions(Core.Specs PRIVATE CORE_SPECS)
target_include_directories(Core.Specs PRIVATE ${SNOWHOUSE_INCLUDE_DIRS})
target_include_directories(Core.Specs PRIVATE ${BANDIT_INCLUDE_DIRS})
target_include_directories(Core.Specs PRIVATE Helpers Core)
