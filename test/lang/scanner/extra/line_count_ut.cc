/**
 * @author Thomas Brandstätter 
 * @date 28.04.18.
 */

#include <iostream>
#include <string>
#include <sstream>

#include <gtest/gtest.h>

#include "../abstract_ut.h"

class syntax_error_test : public abstract_scanner_ut { };
class syntax_error_special_strings : public abstract_scanner_ut { };
class valid_identifiers : public abstract_scanner_ut { };

using openloco::lang::parser;

#define ASSERT_EQ_LOC(loc, line_begin, line_end, column_begin, column_end)      \
    ASSERT_EQ(loc.begin.line,    line_begin);                                   \
    ASSERT_EQ(loc.end.line,      line_end);                                     \
    ASSERT_EQ(loc.begin.column,  column_begin);                                 \
    ASSERT_EQ(loc.end.column,    column_end);

TEST_F(syntax_error_test, location_points_to_error) {
    input << "abc[]\n";

    scanner.yyrestart(input);
    scanner.yylex(driver);
    scanner.yylex(driver);
    parser::symbol_type result = scanner.yylex(driver);
    ASSERT_EQ(result.location.begin.line, 1);
    ASSERT_EQ(result.location.end.line, 1);
}

TEST_F(syntax_error_test, location_points_to_line_3) {
    input << "\n\nabc[]\n";

    scanner.reset(input);
    scanner.yylex(driver);
    scanner.yylex(driver);
    parser::symbol_type result = scanner.yylex(driver);

    ASSERT_EQ_LOC(result.location, 3, 3, 5, 6);
}

TEST_F(syntax_error_test, error_on_none_ascii) {
    input << "@";

    scanner.reset(input);
    parser::symbol_type result = scanner.yylex(driver);
    ASSERT_EQ_LOC(result.location, 1, 1, 1, 2);
}


TEST_F(syntax_error_special_strings, error_on_empty_string) {
    input << "";

    scanner.reset(input);
    scanner.yylex(driver);
    parser::symbol_type result = scanner.yylex(driver);
    ASSERT_EQ_LOC(result.location, 1, 1, 1, 1);
}

TEST_F(valid_identifiers, scanner_location) {
    input << "abc";

    scanner.reset(input);
    parser::symbol_type result = scanner.yylex(driver);
    ASSERT_EQ_LOC(result.location, 1, 1, 1 ,4);
}

