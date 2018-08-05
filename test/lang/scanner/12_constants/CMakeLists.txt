unit_test(
        TARGET  integer_ut
        SOURCES integer_ut.cc
        LIBRARIES parser ${CONAN_LIBS}
        LINK_FLEX
)

unit_test(
        TARGET  binary_integer_ut
        SOURCES binary_integer_ut.cc
        LIBRARIES parser ${CONAN_LIBS}
        LINK_FLEX
)

unit_test(
        TARGET  octal_integer_ut
        SOURCES octal_integer_ut.cc
        LIBRARIES parser ${CONAN_LIBS}
        LINK_FLEX
)

unit_test(
        TARGET  hex_integer_ut
        SOURCES hex_integer_ut.cc
        LIBRARIES parser ${CONAN_LIBS}
        LINK_FLEX
)

#unit_test(
#        TARGET  fixed_point_ut
#        SOURCES fixed_point_ut.cc
#        LIBRARIES parser ${CONAN_LIBS}
#        LINK_FLEX
#)

unit_test(
        TARGET  single_byte_string_ut
        SOURCES single_byte_string_ut.cc
        LIBRARIES parser
        LINK_FLEX
)

unit_test(
        TARGET  double_byte_string_ut
        SOURCES double_byte_string_ut.cc
        LIBRARIES parser
        LINK_FLEX
)