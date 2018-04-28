#include <iostream>
#include <string>
#include <sstream>

#include <gtest/gtest.h>

#include "../abstract_ut.h"

using openloco::lang::parser;

class double_type_string_test : public abstract_scanner_ut { };

TEST_F(double_type_string_test, match_empty_string) {
    input << "''";

    scanner.yyrestart(input);
    parser::symbol_type result = scanner.yylex(driver);
    auto result_value = result.value.as<std::string>();

    ASSERT_STREQ("", result_value.c_str());
}

TEST_F(double_type_string_test, match_string) {
    input << "'string'";

    scanner.yyrestart(input);
    parser::symbol_type result = scanner.yylex(driver);
    auto result_value = result.value.as<std::string>();

    ASSERT_STREQ("string", result_value.c_str());
}

TEST_F(double_type_string_test, token_empty_string) {
    input << "''";

    scanner.yyrestart(input);
    parser::symbol_type result = scanner.yylex(driver);

    ASSERT_EQ(parser::token::DOUBLE_BYTE_CHARACTER_STRING, result.token());
}

TEST_F(double_type_string_test, token_non_empty_string) {
    input << "'not empty'";

    scanner.yyrestart(input);
    parser::symbol_type result = scanner.yylex(driver);

    ASSERT_EQ(parser::token::DOUBLE_BYTE_CHARACTER_STRING, result.token());
}
