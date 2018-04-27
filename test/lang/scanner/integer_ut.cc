#include <iostream>
#include <string>
#include <sstream>

#include <gtest/gtest.h>

#include "abstract_ut.h"

class integer_test : public abstract_scanner_ut { };

TEST_F(integer_test, match_555) {
    input << "555";

    scanner.yyrestart(input);
    openloco::lang::parser::symbol_type result = scanner.yylex(driver);
    auto result_value = result.value.as<long>();

    ASSERT_EQ(555, result_value);
}

TEST_F(integer_test, match_555_w_underscore_position_front) {
    input << "5_55";

    scanner.yyrestart(input);
    openloco::lang::parser::symbol_type result = scanner.yylex(driver);
    auto result_value = result.value.as<long>();

    ASSERT_EQ(555, result_value);
}

TEST_F(integer_test, match_555_w_underscore_position_middle) {
    input << "55_5";

    scanner.yyrestart(input);
    openloco::lang::parser::symbol_type result = scanner.yylex(driver);
    auto result_value = result.value.as<long>();

    ASSERT_EQ(555, result_value);
}

TEST_F(integer_test, match_555_w_underscore_position_end) {
    input << "555_";

    scanner.yyrestart(input);
    openloco::lang::parser::symbol_type result = scanner.yylex(driver);
    auto result_value = result.value.as<long>();

    ASSERT_EQ(555, result_value);
}