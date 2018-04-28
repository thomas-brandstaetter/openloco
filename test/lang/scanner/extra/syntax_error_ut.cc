/**
 * @author Thomas Brandstätter 
 * @date 28.04.18.
 */

#include <iostream>
#include <string>
#include <sstream>

#include <gtest/gtest.h>

#include <parser.hh>

#include <lang/driver.h>
#include <lang/scanner.h>
#include "../abstract_ut.h"

class syntax_error_test : public abstract_scanner_ut { };
class syntax_error_location_test : public abstract_scanner_ut { };
class syntax_error_special_strings : public abstract_scanner_ut { };

using openloco::lang::parser;

TEST_F(syntax_error_test, error_at_end) {
    std::stringstream input;
    input << "SYNTAXERROR[]\n";

    scanner.yyrestart(input);
    scanner.yylex(driver);  // match SYNTAXERROR
    parser::symbol_type result = scanner.yylex(driver);
}

TEST_F(syntax_error_test, error_at_begin) {
    std::stringstream input;
    input << "[]SYNTAXERROR\n";

    scanner.yyrestart(input);
    parser::symbol_type result = scanner.yylex(driver);
}

TEST_F(syntax_error_test, error_at_middle) {
    std::stringstream input;
    input << "SYNTAX[]ERROR\n";

    scanner.yyrestart(input);
    parser::symbol_type result = scanner.yylex(driver);
}


TEST_F(syntax_error_location_test, error_on_line_1) {
    input << "SYNTAXERROR[]\n";

    scanner.yyrestart(input);
    scanner.yylex(driver);  // match SYNTAXERROR
    parser::symbol_type result = scanner.yylex(driver);
    ASSERT_EQ(result.location.begin.line, 1);
    ASSERT_EQ(result.location.end.line, 1);
}

TEST_F(syntax_error_location_test, error_on_line_1_columns) {
    input << "error[]\n";

    scanner.reset(input);
    scanner.yylex(driver);  // match SYNTAXERROR
    parser::symbol_type result = scanner.yylex(driver);
    ASSERT_EQ(result.location.begin.column, 6);
    ASSERT_EQ(result.location.end.column, 7);
}


TEST_F(syntax_error_location_test, error_on_line_3) {
    input << "\n\nSYNTAXERROR[]\n";

    scanner.reset(input);
    scanner.yylex(driver);  // match SYNTAXERROR
    parser::symbol_type result = scanner.yylex(driver);
    ASSERT_EQ(result.location.begin.line, 3);
    ASSERT_EQ(result.location.end.line, 3);
}

TEST_F(syntax_error_location_test, error_on_line_3_columns) {
    input << "\n\nSYNTAXERROR[]\n";

    scanner.reset(input);
    scanner.yylex(driver);  // match SYNTAXERROR
    parser::symbol_type result = scanner.yylex(driver);
    ASSERT_EQ(result.location.begin.column, 12);
    ASSERT_EQ(result.location.end.column, 13);
}

TEST_F(syntax_error_location_test, error_on_none_ascii) {
    input << "@";

    scanner.reset(input);
    scanner.yylex(driver);  // match SYNTAXERROR
    parser::symbol_type result = scanner.yylex(driver);
    ASSERT_EQ(result.location.begin.column, 2);
    ASSERT_EQ(result.location.end.column, 2);
    ASSERT_EQ(result.location.begin.line, 1);
    ASSERT_EQ(result.location.end.line, 1);
}


TEST_F(syntax_error_special_strings, error_on_empty_string) {
    input << "";

    scanner.reset(input);
    scanner.yylex(driver);
    parser::symbol_type result = scanner.yylex(driver);
    ASSERT_EQ(result.location.begin.column, 1);
    ASSERT_EQ(result.location.end.column, 1);
    ASSERT_EQ(result.location.begin.line, 1);
    ASSERT_EQ(result.location.end.line, 1);
}

TEST_F(syntax_error_special_strings, scanner_location) {
    input << "abc";

    scanner.reset(input);
    parser::symbol_type result = scanner.yylex(driver);
    ASSERT_EQ(result.location.begin.column, 1);
    ASSERT_EQ(result.location.end.column, 4);
    ASSERT_EQ(result.location.begin.line, 1);
    ASSERT_EQ(result.location.end.line, 1);
}