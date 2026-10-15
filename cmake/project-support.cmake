
# CMake generic project support
#
# version 1.0.2 2026-01-03T21:28

### No in-source builds ##########################################################
if (PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
    message(FATAL_ERROR "In-source build prevented. Use different -S and -B argument values.")
endif()


### parse arguments when using CMake-gui #########################################
#
# CMake-gui fails in accepting 'common sense' command line arguments
# such as --log-level=VERBOSE
# This is a work-around using an environment variable.
# Arguments accepted are on a 'want to have it now' base. If you need more
# add it to the list.

if (NOT ("$ENV{ARGS_CMAKE_GUI}" STREQUAL ""))
    foreach (arg IN ITEMS $ENV{ARGS_CMAKE_GUI})
        # arg pattern: --key=value
        if (arg MATCHES "^ *--([^=]+)=(.+)")
            if (CMAKE_MATCH_1 STREQUAL "log-level")
                if (2 LESS_EQUAL CMAKE_MATCH_COUNT)
                    set(CMAKE_MESSAGE_LOG_LEVEL ${CMAKE_MATCH_2})
                    message(VERBOSE "ARGS_CMAKE_GUI: accept ${arg}")
                else()
                    message(WARNING "ARGS_CMAKE_GUI: skipped ${arg}")
                endif()
            else()
                message(WARNING "ARGS_CMAKE_GUI: Not accepted ${arg}, ignored.")
            endif()
        # arg pattern: --key value
        elseif (arg MATCHES "^ *--([^ ]+)[ ]+([^ ]+)")
            if (CMAKE_MATCH_1 STREQUAL "install-prefix")
                if (2 LESS_EQUAL CMAKE_MATCH_COUNT)
                    set(CMAKE_INSTALL_PREFIX ${CMAKE_MATCH_2})
                    message(VERBOSE "ARGS_CMAKE_GUI: accept ${arg}")
                else()
                    message(WARNING "ARGS_CMAKE_GUI: skipped ${arg}")
                endif()
            else()
                message(WARNING "ARGS_CMAKE_GUI: Not accepted ${arg}, ignored.")
            endif()
        else()
           message(WARNING "ARGS_CMAKE_GUI: Not recognised ${arg}, ignored.")
        endif()
    endforeach()
endif()


### check environment settings ###################################################
if ("${CMAKE_PREFIX_PATH}" STREQUAL "")
    set(CMAKE_PREFIX_PATH $ENV{CMAKE_PREFIX_PATH})
endif()
if ("${CMAKE_PREFIX_PATH}" STREQUAL "")
    message(VERBOSE "CMAKE_PREFIX_PATH is empty, may have dificulties finding library depenendcies.")
else()
    message(VERBOSE "CMAKE_PREFIX_PATH=${CMAKE_PREFIX_PATH}")
endif()


### support for external libraries ##############################################

# package_target(package, tgt_name)
#
# Check if package is found and if TARGET tgt_name exists.
# If package found and TARGET tgt_name is not available try to create one.
# This will fail (with a fatal error) is the package is using link type 
# specifiers in the libraries list.
#
# Use this call if the package has not created a TARGET (such a thing as PKG::PKG).
# On a fatal error do not use this call and TARGET tgt_name in CMakeLists.txt
#
# On succes the core of this call is in the following code extract:
#
#     add_library(${tgt_name} INTERFACE IMPORTED)
#     set_target_properties(${tgt_name} PROPERTIES
#         INTERFACE_LINK_LIBRARIES "${LIBS}"
#         INTERFACE_INCLUDE_DIRECTORIES "${INCS}")
#
# Where LIBS are the libraries and INCS the include paths used in the found pacakage.
# If both LIBS and INCS are empty nothing is done and no TARGET tgt_name is available,
# then a fatal error message is triggered.
#
function(package_target package tgt_name)
    if(${package}_FOUND AND NOT TARGET ${tgt_name})
        unset(LIBS)
        if (${package}_LIBRARIES)
            set(LIBS ${${package}_LIBRARIES})
        elseif(${package}_LIBS)
            set(LIBS ${${package}_LIBS})
        endif()
        if (NOT "${LIBS}" STREQUAL "")
            foreach(v optimized debug)
                list(FIND LIBS ${v} have_item)
                if (have_item GREATER_EQUAL 0)
                    message(FATAL_ERROR ">> TARGET ${tgt_name} INTERFACE IMPORTED: Property INTERFACE_LINK_LIBRARIES may not contain link-type keyword '${v}'.")
                endif()
            endforeach()
        endif()

        unset(INCS)
        if (${package}_INCLUDE_DIRS)
            set(INCS ${${package}_INCLUDE_DIRS})
        elseif(${package}_INCLUDE_DIR)
            set(INCS ${${package}_INCLUDE_DIR})
        endif()
        if ("${INCS}" STREQUAL "")
            message(VERBOSE ">> ${package}_INCLUDE_DIRS empty")
        endif()

        if (NOT "${LIBS}" STREQUAL "" OR NOT "${INCS}" STREQUAL "")
            add_library(${tgt_name} INTERFACE IMPORTED)
            set_target_properties(${tgt_name} PROPERTIES
                INTERFACE_LINK_LIBRARIES "${LIBS}"
                INTERFACE_INCLUDE_DIRECTORIES "${INCS}")
        else()
            message(FATAL_ERROR ">> TARGET ${tgt_name} INTERFACE IMPORTED: PROPERTIES are all empy.")
        endif()
    endif()
endfunction()

# pkg_detail(package, detail)
#
# use detail to find a package attribute (deprecated of recommended) and report its value (may be empty)
#
# intended for internal use by pkg_details() but may be usefull on its own
function(pkg_detail package detail)
    message(">> ${package}_${detail}=${${package}_${detail}}")
endfunction()

# pkg_details(package, ...)
#
# Check if package is found. If found and no extra arguments report package
# as found. Or use the extra arguments as package attribute names (deprecated
# of recommended) and report its value (may be empty). If not found report
# package as not found.
#
function(pkg_details package)
    if (NOT ${package}_FOUND OR ${ARGC} EQUAL 1)
        pkg_detail(${package} FOUND)
    else()
        foreach (v ${ARGN})
            pkg_detail(${package} "${v}")
        endforeach()
    endif()
endfunction()

# package_details(package, ...)
#
# Check if package is found, report a list of package attributes.
# Append the default list of attributes with additional items from ARGN.
# Report attributes once.
# 
# Default list: "VERSION;INCLUDE_DIRS;INCLUDE_DIR;LIBRARIES;LIBS"
#
# See also: pkg_details() for details without a default attributes list.
function(package_details package)
    set(details "VERSION;INCLUDE_DIRS;INCLUDE_DIR;LIBRARIES;LIBS")
    if (${ARGC} GREATER 1)
        list(APPEND details ${ARGN})
        list(REMOVE_DUPLICATES details)
    endif()
    pkg_details(${package} ${details})
endfunction()

