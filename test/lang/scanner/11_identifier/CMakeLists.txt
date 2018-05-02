
unit_test(
    TARGET  identifier_ut
    SOURCES identifier_ut.cc
    LIBRARIES parser ${GTEST_BOTH_LIBRARIES} pthread gtest
    LINK_FLEX
)