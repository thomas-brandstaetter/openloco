
# ----------------------------------------------------------------------------
# project setup
# ----------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.0)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/Modules)
include(${CMAKE_SOURCE_DIR}/cmake/Modules/unit_test.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/Modules/testfile_runner.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/Modules/coverage_build_type.cmake)

project(openloco C CXX)

# ----------------------------------------------------------------------------
# Compiler settings
# ----------------------------------------------------------------------------

add_definitions(-std=c++11)

if({CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
    add_definitions(-stdlib=libc++)
endif()
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message("** COMPILER")
message("**    Build type:      ${CMAKE_BUILD_TYPE}")
message("**    Generator:       ${CMAKE_GENERATOR}")
message("**    C compiler:      ${CMAKE_C_COMPILER_ID}")
message("**    C++ compiler:    ${CMAKE_CXX_COMPILER_ID}")

# ----------------------------------------------------------------------------
# Include / Link directories
# ----------------------------------------------------------------------------

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

message("** LIBRARIES")

find_package(Threads REQUIRED)
    message("**    PThreads found: ${THREADS_FOUND}")

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
    message("**    Qt5Gui version ${Qt5Gui_VERSION_STRING}")
    include_directories(${Qt5Widgets_INCLUDE_DIRS})


if (WIN32)
    # FIXME GTest Windows bug
    include_directories("C:\\Program Files (x86)\\googletest-distribution\\include")
    set(GTEST_LIBRARY "C:\\Program Files (x86)\\googletest-distribution\\gtestd.lib")
    set(GTEST_MAIN_LIBRARY "C:\\Program Files (x86)\\googletest-distribution\\gtest_maind.lib")
    set( ${GTEST_LIBRARY} ${GTEST_MAIN_LIBRARY})
else()
    find_package(GTest REQUIRED pthread)
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

message("** Configuring begin")

add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(test)