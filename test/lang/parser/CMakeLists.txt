add_executable(
    testfile_runner
    test_runner.cc
)

target_link_libraries(
    testfile_runner
    parser ${GTEST_BOTH_LIBRARIES}
)

add_custom_command(
    OUTPUT ${BIN_DIR}/test_runner
    DEPENDS testfile_runner
    COMMAND
        ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_CURRENT_BINARY_DIR}/test_runner
        ${BIN_DIR}/test_runner
    COMMENT "message test"
)


file(GLOB_RECURSE testfiles RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} 13_data_types/*.[0-2])
foreach(file ${testfiles})
    testfile_runner( TESTFILE ${file})
endforeach()

file(GLOB_RECURSE testfiles RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} extra/*.[0-2])
foreach(file ${testfiles})
    testfile_runner( TESTFILE ${file})
endforeach()

