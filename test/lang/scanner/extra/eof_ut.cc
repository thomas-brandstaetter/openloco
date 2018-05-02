#include <iostream>
#include <sstream>

#include <gtest/gtest.h>

#include "../abstract_ut.h"



#define ASSERT_EQ_LOC(loc, line_begin, line_end, column_begin, column_end)      \
    ASSERT_EQ(loc.begin.line,    line_begin);                                   \
    ASSERT_EQ(loc.end.line,      line_end);                                     \
    ASSERT_EQ(loc.begin.column,  column_begin);                                 \
    ASSERT_EQ(loc.end.column,    column_end);


class eof_test : public abstract_scanner_ut { };
class eof_scanner_test : public abstract_scanner_ut { };

using openloco::lang::parser;



TEST_F(eof_test, match_empty_string) {
    input << "";

    scanner.reset(input);
    parser::symbol_type result = scanner.yylex(driver);
    ASSERT_EQ(parser::token::END, result.token());
}


TEST_F(eof_test, token_after_identifier) {
    input << "abc";

    scanner.reset(input);
    scanner.yylex(driver);
    scanner.yylex(driver);
    parser::symbol_type result = scanner.yylex(driver);
    ASSERT_EQ(parser::token::END, result.token());
}

TEST_F(eof_test, eof_location_after_identifier) {
    input << "abc";

    scanner.reset(input);
    scanner.yylex(driver);
    scanner.yylex(driver);
    parser::symbol_type result = scanner.yylex(driver);
    ASSERT_EQ_LOC(result.location, 1, 1, 4 ,4);
}
