#include <iostream>
#include <string>
#include <sstream>

#include <gtest/gtest.h>

#include "abstract_ut.h"

using openloco::lang::parser;

class fixed_point_test : public abstract_scanner_ut { };


TEST_F(fixed_point_test, match_555_555) {
    input << "555.555";

    scanner.yyrestart(input);
    parser::symbol_type result = scanner.yylex(driver);

    ASSERT_EQ(555.555, result.value.as<double>());
    ASSERT_EQ(parser::token::FIXED_POINT, result.token());
}


TEST_F(fixed_point_test, match_w_underscore) {
    input << "5_55.55_5";

    scanner.yyrestart(input);
    parser::symbol_type result = scanner.yylex(driver);

    ASSERT_EQ(555.555, result.value.as<double>());
    ASSERT_EQ(parser::token::FIXED_POINT, result.token());
}