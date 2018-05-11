
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

find_package(Threads REQUIRED)
    message("**    PThreads found: ${THREADS_FOUND}")

if (WIN32)
    
#    include_directories("C:\\Program Files (x86)\\googletest-distribution\\include")
#    set(GTEST_LIBRARY "C:\\Program Files (x86)\\googletest-distribution\\gtestd.lib")
#    set(GTEST_MAIN_LIBRARY "C:\\Program Files (x86)\\googletest-distribution\\gtest_maind.lib")
#    set(GTEST_BOTH_LIBRARIES ${GTEST_LIBRARY} ${GTEST_MAIN_LIBRARY})
#
#	list(APPEND CMAKE_FIND_LIBRARY_SUFFIXES ".a")
#
#
#	include_directories("C:\\msys64\\usr\\include")
#
#	find_package(BISON REQUIRED)
#		message("**    Bison version ${BISON_VERSION}")
#
#	set(FLEX_EXECUTABLE "C:\\msys64\\usr\\bin\\flex.exe")
#	mark_as_advanced(FLEX_EXECUTABLE)
#	set(FLEX_LIBRARIES "C:\\msys64\\usr\\lib\\libfl.a")
#	set(FLEX_INCLUDE_DIRS "C:\\msys64\\usr\\include" )
#	mark_as_advanced(FL_LIBRARIES FLEX_INCLUDE_DIRS)
#
#	include(${CMAKE_SOURCE_DIR}/cmake/Modules/win_flex.cmake)
	
else()
    find_package(GTest REQUIRED pthread)
        message("**    GTest found:    ${GTEST_FOUND}")
        include_directories(${GTEST_INCLUDE_DIRS})

	find_package(BISON REQUIRED)
		message("**    Bison version ${BISON_VERSION}")


	find_package(FLEX REQUIRED)
		message("**    ${FLEX_version_output}")
		include_directories(${FLEX_INCLUDE_DIRS})
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

