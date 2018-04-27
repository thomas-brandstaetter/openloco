
# ----------------------------------------------------------------------------
# project setup
# ----------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.10)
project(openloco CXX)

# ----------------------------------------------------------------------------
# Compiler settings
# ----------------------------------------------------------------------------

add_definitions(
    -std=c++11
    -ferror-limit=100
)
set(CMAKE_CXX_STANDARD 11)

# ----------------------------------------------------------------------------
# Include / Link directories
# ----------------------------------------------------------------------------

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/Modules)
include(${CMAKE_SOURCE_DIR}/cmake/Modules/unit_test.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/Modules/testfile_runner.cmake)

if (WIN32)
    SET(CMAKE_PREFIX_PATH "C:/Qt/5.10.1/msvc2017_64")
elseif(APPLE)
    # FIX ME: export CMAKE_PREFIX_PATH in ~/.zprofile. and check this here
    SET(CMAKE_PREFIX_PATH "/Users/tb/usr/Qt/5.10.1/clang_64")
else()

endif()

include_directories(
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

# ----------------------------------------------------------------------------
# Find packages
# ----------------------------------------------------------------------------

message(** LIBRARIES)

find_package(BOOST REQUIRED COMPONENTS variant)
    message("**    Boost version ${Boost_MAJOR_VERSION}.${Boost_MINOR_VERSION}")
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIRS})

find_package(BISON REQUIRED)
    message("**    Bison version ${BISON_VERSION}")

find_package(FLEX REQUIRED)
    message("**    ${FLEX_version_output}")
    include_directories(${FLEX_INCLUDE_DIRS})

find_package(Qt5Core REQUIRED)
    message("**    Qt5Core version ${Qt5Core_VERSION_STRING}")
    include_directories(${Qt5Core_INCLUDE_DIRS})

find_package(Qt5Widgets REQUIRED)
    message("**    Qt5Widgets version ${Qt5Widgets_VERSION_STRING}")
    include_directories(${Qt5Widgets_INCLUDE_DIRS})

if (WIN32)
    # FIXME GTest Windows bug
    include_directories("C:\\Program Files (x86)\\googletest-distribution\\include")
    set(GTEST_LIBRARY "C:\\Program Files (x86)\\googletest-distribution\\gtestd.lib")
    set(GTEST_MAIN_LIBRARY "C:\\Program Files (x86)\\googletest-distribution\\gtest_maind.lib")
    set( ${GTEST_LIBRARY} ${GTEST_MAIN_LIBRARY})
else()
    find_package(GTest REQUIRED)
        message("**    GTest found: ${GTEST_FOUND}")
        include_directories(${GTEST_INCLUDE_DIRS})

endif()




# ----------------------------------------------------------------------------
# CTEST CDASH
# ----------------------------------------------------------------------------


include(CTest)
enable_testing()



add_definitions(-g)
enable_testing()


# ----------------------------------------------------------------------------
# dive into the code
# ----------------------------------------------------------------------------

add_subdirectory(header)
add_subdirectory(src)
add_subdirectory(test)



#get_cmake_property(_variableNames VARIABLES)
#list (SORT _variableNames)
#foreach (_variableName ${_variableNames})
#    message(STATUS "${_variableName}=${${_variableName}}")
#endforeach()