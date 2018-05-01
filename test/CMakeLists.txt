include_directories(${CMAKE_BINARY_DIR}/src/lang)
include_directories(${CMAKE_SOURCE_DIR}/src/lang)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(lang)

#add_custom_target("Run-all-tests" ${CMAKE_CTEST_COMMAND} -VV)