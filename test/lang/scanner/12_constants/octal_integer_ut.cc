#include <iostream>
#include <string>
#include <sstream>

#include <gtest/gtest.h>

#include "../abstract_ut.h"

using parser = openloco::lang::parser;
namespace ast = openloco::lang::ast;

class octal_integer_test : public abstract_scanner_ut { };

TEST_F(octal_integer_test, match_555) {
    std::stringstream input;
    input << "8#555";

    scanner.yyrestart(input);
    parser::symbol_type result = scanner.yylex(driver);
    auto result_value = result.value.as<ast::octal_integer>();

    ASSERT_EQ(0555, result_value.value);
}

TEST_F(octal_integer_test, match_token) {
    std::stringstream input;
    input << "8#555";

    scanner.yyrestart(input);
    parser::symbol_type result = scanner.yylex(driver);
    auto result_value = result.value.as<ast::octal_integer>();

    ASSERT_EQ(0555, result_value.value);
}

TEST_F(octal_integer_test, match_555_w_underscore_position_front) {
    std::stringstream input;
    input << "8#5_55";

    scanner.yyrestart(input);
    parser::symbol_type result = scanner.yylex(driver);
    auto result_value = result.value.as<ast::octal_integer>();

    ASSERT_EQ(0555, result_value.value);
}

TEST_F(octal_integer_test, match_555_w_underscore_position_middle) {
    std::stringstream input;
    input << "8#55_5";

    scanner.yyrestart(input);
    parser::symbol_type result = scanner.yylex(driver);
    auto result_value = result.value.as<ast::octal_integer>();

    ASSERT_EQ(0555, result_value.value);
}

TEST_F(octal_integer_test, match_555_w_underscore_position_end) {
    std::stringstream input;
    input << "8#555_";

    scanner.yyrestart(input);
    parser::symbol_type result = scanner.yylex(driver);
    auto result_value = result.value.as<ast::octal_integer>();

    ASSERT_EQ(0555, result_value.value);
}