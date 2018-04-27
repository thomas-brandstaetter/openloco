add_executable(
    testfile_runner
    test_runner.cc
)

target_link_libraries(
    testfile_runner
    parser
)

# ----------------------------------------------------------------------------
#   1.3
# ----------------------------------------------------------------------------

testfile_runner (TESTFILE 13/type_with_array.0)
testfile_runner (TESTFILE 13/type_with_elementary.0)
testfile_runner (TESTFILE 13/type_with_enumerated.0)
testfile_runner (TESTFILE 13/type_with_multiple_subtypes.0)
testfile_runner (TESTFILE 13/type_with_struct.0)
testfile_runner (TESTFILE 13/type_with_subrange.openloco)

# ----------------------------------------------------------------------------
#   extra
# ----------------------------------------------------------------------------

testfile_runner (TESTFILE extra/nested_comments.1)
testfile_runner (TESTFILE extra/newline_in_comments.openloco)
testfile_runner (TESTFILE extra/single_comments.0)
