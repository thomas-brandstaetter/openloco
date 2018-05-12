
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

add_definitions(-std=c++17)

if({CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
    add_definitions(-stdlib=libc++)
endif()
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message("** COMPILER")
message("**    Build type:      ${CMAKE_BUILD_TYPE}")
message("**    Generator:       ${CMAKE_GENERATOR}")
message("**    C compiler:      ${CMAKE_C_COMPILER_ID}")
message("**    C++ compiler:    ${CMAKE_CXX_COMPILER_ID}")

# ----------------------------------------------------------------------------
# Include / Link directories
# ----------------------------------------------------------------------------

include_directories(
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

# ----------------------------------------------------------------------------
# Find packages
# ----------------------------------------------------------------------------

message("** LIBRARIES")

if(Win32)
	include_directories("C:/msys2/usr/include")
	link_directories("C:/msys2/usr/lib")

	set(GTEST_ROOT "C:/Program Files (x86)/googletest-distribution")
	list(APPEND CMAKE_STATIC_LIBRARY_SUFFIX ".a")
endif()


find_package(Threads REQUIRED)
    message("**    PThreads found: ${THREADS_FOUND}")


find_package(GTest REQUIRED pthread)
    message("**    GTest found:    ${GTEST_FOUND}")
    include_directories(${GTEST_INCLUDE_DIRS})

find_package(BISON REQUIRED)
	message("**    Bison version ${BISON_VERSION}")


find_package(FLEX REQUIRED)
	message("**    ${FLEX_version_output}")
	include_directories(${FLEX_INCLUDE_DIRS})



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

