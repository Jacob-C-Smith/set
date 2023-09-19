# Need CMake 3.20
cmake_minimum_required (VERSION 3.20)

# This is the name of the repository
project ("set")

# Set the correct paths
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR}/extern/)

# Comment out for Debug mode
set(IS_DEBUG_BUILD CMAKE_BUILD_TYPE STREQUAL "Debug")

# Set debug mode
if (${IS_DEBUG_BUILD})
    add_compile_definitions(NDEBUG)
endif()

# Find the sync module
if ( NOT "${HAS_SYNC}")

    # Log
    message("[set] Adding sync project")

    # Add the sync directory
    add_subdirectory(${CMAKE_SOURCE_DIR}/extern/sync ${CMAKE_SOURCE_DIR}/build/sync)

    # Let any parent project know that this project has sync
    set(HAS_SYNC true PARENT_SCOPE)
endif()

# Add the set project
if ( NOT "${HAS_SET}")

    # Log
    message("[set] Adding set project")

    # Let any parent project know that it has the set project
    set(HAS_SET true PARENT_SCOPE)
endif()

# Add source to this project's executable.
add_executable(set_example "main.c" "set.c")
add_dependencies(set_example sync)
target_include_directories(set_example PUBLIC include include/set ${CMAKE_SOURCE_DIR}/extern/sync/include/)
target_link_libraries(set_example sync)

# TODO: Implement tester
# Add source to the tester
#add_executable (set_test "set_test.c" "set.c")
#add_dependencies(set_test sync)
#target_include_directories(set_test PUBLIC include include/set ${CMAKE_SOURCE_DIR}/extern/sync/include/)
#target_link_libraries(set_test sync)

# Add source to the library
add_library(set SHARED "set.c")
add_dependencies(set sync)
target_include_directories(set PUBLIC include include/set ${CMAKE_SOURCE_DIR}/extern/sync/include/)
target_link_libraries(set sync)
