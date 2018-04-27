
add_custom_target("Test_All" ${CMAKE_CTEST_COMMAND} -V)

include_directories(${CMAKE_SOURCE_DIR}/header)
include_directories(${CMAKE_SOURCE_DIR}/header/lang)
include_directories(${CMAKE_BINARY_DIR}/src/lang)

add_subdirectory(lang)