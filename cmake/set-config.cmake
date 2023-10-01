# SET CMake configuration file:
# This file is meant to be placed in a cmake subfolder of SET-devel-2.x.y-VC

cmake_minimum_required(VERSION 3.0)

include(FeatureSummary)
set_package_properties(SET PROPERTIES
    URL "https://g10.app/status/#abstract_data_i"
    DESCRIPTION "Set ADT"
)

# Copied from `configure_package_config_file`
macro(set_and_check _var _file)
    set(${_var} "${_file}")
    if(NOT EXISTS "${_file}")
        message(FATAL_ERROR "File or directory ${_file} referenced by variable ${_var} does not exist !")
    endif()
endmacro()

# Copied from `configure_package_config_file`
macro(check_required_components _NAME)
    foreach(comp ${${_NAME}_FIND_COMPONENTS})
        if(NOT ${_NAME}_${comp}_FOUND)
            if(${_NAME}_FIND_REQUIRED_${comp})
                set(${_NAME}_FOUND FALSE)
            endif()
        endif()
    endforeach()
endmacro()

set(SET_FOUND TRUE)

# For compatibility with autotools SET-config.cmake, provide SET_* variables.

set_and_check(SET_PREFIX       "${CMAKE_CURRENT_LIST_DIR}/..")
set_and_check(SET_EXEC_PREFIX  "${CMAKE_CURRENT_LIST_DIR}/..")
set_and_check(SET_INCLUDE_DIR  "${SET_PREFIX}/include")
set(SET_INCLUDE_DIRS           "${SET_INCLUDE_DIR}")
set_and_check(SET_BINDIR       "${CMAKE_CURRENT_LIST_DIR}/../build/Debug/")
set_and_check(SET_LIBDIR       "${CMAKE_CURRENT_LIST_DIR}/../build/Debug/")

set(SET_LIBRARIES SET::SET)

# All targets are created, even when some might not be requested though COMPONENTS.
# This is done for compatibility with CMake generated SET-target.cmake files.

set(_SET_library     "${SET_LIBDIR}/set.lib")
set(_SET_dll_library "${SET_BINDIR}/set.dll")
if(EXISTS "${_SET_library}" AND EXISTS "${_SET_dll_library}")
    if(NOT TARGET SET::SET)
        add_library(SET::SET SHARED IMPORTED)
        set_target_properties(SET::SET
            PROPERTIES
                INTERFACE_INCLUDE_DIRECTORIES "${SET_INCLUDE_DIRS}"
                IMPORTED_IMPLIB "${_SET_library}"
                IMPORTED_LOCATION "${_SET_dll_library}"
                COMPATIBLE_INTERFACE_BOOL "SET_SHARED"
                INTERFACE_SET_SHARED "ON"
        )
    endif()
    set(SET_SET_FOUND TRUE)
else()
    set(SET_SET_FOUND FALSE)
endif()
unset(_SET_library)
unset(_SET_dll_library)

check_required_components(SET)
