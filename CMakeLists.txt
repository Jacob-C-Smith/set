# Need CMake 3.16
cmake_minimum_required (VERSION 3.16.0)

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

    # Add the sync directory
    add_subdirectory(${CMAKE_SOURCE_DIR}/extern/sync ${CMAKE_SOURCE_DIR}/build/sync)

    # Let any parent project know that this project has sync
    if(NOT PROJECT_IS_TOP_LEVEL)
        set(HAS_SYNC true PARENT_SCOPE)
        set(SYNC_INCLUDE_DIR ${SYNC_INCLUDE_DIR} PARENT_SCOPE)
    endif()
endif()

# Find the log module
if ( NOT "${HAS_LOG}")

    # Add the log directory
    add_subdirectory(${CMAKE_SOURCE_DIR}/extern/log ${CMAKE_SOURCE_DIR}/build/log)

    # Let any parent project know that this project has log
    if(NOT PROJECT_IS_TOP_LEVEL)
        set(HAS_LOG true PARENT_SCOPE)
        set(LOG_INCLUDE_DIR ${LOG_INCLUDE_DIR} PARENT_SCOPE)
    endif()
endif()

# Find the SET module
if ( NOT "${HAS_SET}")

    # Log
    message("[set] Adding set project")

    # Set the set include
    set(SET_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/include)

    # Let any parent project know that it has the set project
    if(NOT PROJECT_IS_TOP_LEVEL)
        set(HAS_SET true PARENT_SCOPE)
        set(SET_INCLUDE_DIR ${SET_INCLUDE_DIR} PARENT_SCOPE)
    endif()
endif()

# Add source to this project's executable.
add_executable(set_example "main.c")
add_dependencies(set_example set)
target_include_directories(set_example PUBLIC ${SET_INCLUDE_DIR} ${SYNC_INCLUDE_DIR})
target_link_libraries(set_example set)

# Add source to the tester
add_executable (set_test "set_test.c" "set.c")
add_dependencies(set_test set sync log)
target_include_directories(set_test PUBLIC ${SET_INCLUDE_DIR} ${SYNC_INCLUDE_DIR} ${LOG_INCLUDE_DIR})
target_link_libraries(set_test set sync log)

# Add source to the library
add_library(set SHARED "set.c")
add_dependencies(set sync)
target_include_directories(set PUBLIC ${SET_INCLUDE_DIR} ${SYNC_INCLUDE_DIR})
target_link_libraries(set sync)
