SET(GCC_DEBUG_FLAGS "-g -Wall")


message("** BUILD_TYPES")

set(CMAKE_CXX_FLAGS_COVERAGE "${GCC_FLAGS} -fprofile-arcs -ftest-coverage")
set(CMAKE_C_FLAGS_COVERAGE "${GCC_FLAGS} -fprofile-arcs -ftest-coverage")
set(CMAKE_EXE_LINKER_FLAGS_COVERAGE "")
set(CMAKE_SHARED_LINKER_FLAGS_COVERAGE "")


