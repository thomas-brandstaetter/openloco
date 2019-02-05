
set(SRC_DIRECTORY ${CMAKE_SOURCE_DIR}/lang/src)
set(TEST_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})


include_directories(${SRC_DIRECTORY})
include_directories(${TEST_DIRECTORY})

#add_subdirectory(ast)
#add_subdirectory(scanner)
#add_subdirectory(parser)



#add_custom_target("Run-all-tests" ${CMAKE_CTEST_COMMAND} -VV)