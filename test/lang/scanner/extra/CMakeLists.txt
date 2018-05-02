
unit_test(
    TARGET  eof_ut
    SOURCES eof_ut.cc
    LIBRARIES parser
    LINK_FLEX
)

unit_test(
    TARGET  eol_ut
    SOURCES eol_ut.cc
    LIBRARIES parser
    LINK_FLEX
)

unit_test(
    TARGET  line_count_ut
    SOURCES line_count_ut.cc
    LIBRARIES parser
    LINK_FLEX
)


unit_test(
    TARGET  syntax_error
    SOURCES syntax_error_ut.cc
    LIBRARIES parser
    LINK_FLEX
)

