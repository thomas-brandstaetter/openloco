#include <iostream>
#include <string>
#include <sstream>

#include <gtest/gtest.h>

#include "../abstract_ut.h"

class binary_integer_test : public abstract_scanner_ut { };

TEST_F(binary_integer_test, match_integer) {
    input << "2#111";

    scanner.yyrestart(input);
    openloco::lang::parser::symbol_type result = scanner.yylex(driver);
    auto result_value = result.value.as<long>();

    ASSERT_EQ(7, result_value);
}

TEST_F(binary_integer_test, match_integer_w_underscore) {
    input << "2#1_11";

    scanner.yyrestart(input);
    openloco::lang::parser::symbol_type result = scanner.yylex(driver);
    auto result_value = result.value.as<long>();

    ASSERT_EQ(7, result_value);
}

TEST_F(binary_integer_test, match_integer_w_underscore_before_end) {
    input << "2#11_1";

    scanner.yyrestart(input);
    openloco::lang::parser::symbol_type result = scanner.yylex(driver);
    auto result_value = result.value.as<long>();

    ASSERT_EQ(7, result_value);
}

TEST_F(binary_integer_test, match_integer_w_underscore_at_end) {
    input << "2#111_";

    scanner.yyrestart(input);
    openloco::lang::parser::symbol_type result = scanner.yylex(driver);
    auto result_value = result.value.as<long>();

    ASSERT_EQ(7, result_value);
}