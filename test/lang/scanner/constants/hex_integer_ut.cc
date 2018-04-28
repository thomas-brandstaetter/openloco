#include <iostream>
#include <string>
#include <sstream>

#include <gtest/gtest.h>

#include "../abstract_ut.h"

class hex_integer_test : public abstract_scanner_ut { };

TEST_F(hex_integer_test, match_555) {
    std::stringstream input;
    input << "16#555";

    scanner.yyrestart(input);
    openloco::lang::parser::symbol_type result = scanner.yylex(driver);
    auto result_value = result.value.as<long>();

    ASSERT_EQ(0x555, result_value);
}

TEST_F(hex_integer_test, match_555_w_underscore_position_front) {
    std::stringstream input;
    input << "16#5_55";

    scanner.yyrestart(input);
    openloco::lang::parser::symbol_type result = scanner.yylex(driver);
    auto result_value = result.value.as<long>();

    ASSERT_EQ(0x555, result_value);
}

TEST_F(hex_integer_test, match_555_w_underscore_position_middle) {
    std::stringstream input;
    input << "16#55_5";

    scanner.yyrestart(input);
    openloco::lang::parser::symbol_type result = scanner.yylex(driver);
    auto result_value = result.value.as<long>();

    ASSERT_EQ(0x555, result_value);
}

TEST_F(hex_integer_test, match_555_w_underscore_position_end) {
    std::stringstream input;
    input << "16#555_";

    scanner.yyrestart(input);
    openloco::lang::parser::symbol_type result = scanner.yylex(driver);
    auto result_value = result.value.as<long>();

    ASSERT_EQ(0x555, result_value);
}