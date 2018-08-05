#include <iostream>
#include <string>
#include <sstream>

#include <gtest/gtest.h>

#include "../abstract_ut.h"

using parser = openloco::lang::parser;
namespace ast = openloco::lang::ast;

class hex_integer_test : public abstract_scanner_ut { };

TEST_F(hex_integer_test, match_555) {
    std::stringstream input;
    input << "16#555";

    scanner.reset(input);
    parser::symbol_type result = scanner.yylex(driver);
    auto result_value = result.value.as<ast::hex_integer>();

    ASSERT_EQ(0x555, result_value.value);
}

TEST_F(hex_integer_test, match_555_w_underscore_position_front) {
    std::stringstream input;
    input << "16#5_55";

    scanner.reset(input);
    parser::symbol_type result = scanner.yylex(driver);
    auto result_value = result.value.as<ast::hex_integer>();

    ASSERT_EQ(0x555, result_value.value);
}

TEST_F(hex_integer_test, match_555_w_underscore_position_middle) {
    std::stringstream input;
    input << "16#55_5";

    scanner.reset(input);
    parser::symbol_type result = scanner.yylex(driver);
    auto result_value = result.value.as<ast::hex_integer>();

    ASSERT_EQ(0x555, result_value.value);
}

TEST_F(hex_integer_test, match_555_w_underscore_position_end) {
    std::stringstream input;
    input << "16#555_";

    scanner.reset(input);
    parser::symbol_type result = scanner.yylex(driver);
    auto result_value = result.value.as<ast::hex_integer>();

    ASSERT_EQ(0x555, result_value.value);
}