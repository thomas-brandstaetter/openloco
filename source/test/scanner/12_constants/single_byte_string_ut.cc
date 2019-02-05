#include <iostream>
#include <string>
#include <sstream>

#include <gtest/gtest.h>

#include "lang/test/scanner/abstract_ut.h"

using openloco::lang::parser;

class single_type_string_test : public abstract_scanner_ut { };

TEST_F(single_type_string_test, match_empty_string) {
    input << "''";

    scanner.yyrestart(input);
    parser::symbol_type result = scanner.yylex(driver);

    ASSERT_EQ(parser::token::SINGLE_BYTE_CHARACTER_STRING, result.token());
    ASSERT_STREQ("", result.value.as<std::string>().c_str());
}

TEST_F(single_type_string_test, match_string) {
    input << "'string'";

    scanner.yyrestart(input);
    parser::symbol_type result = scanner.yylex(driver);
    std::string result_value = result.value.as<std::string>();

    ASSERT_EQ(parser::token::SINGLE_BYTE_CHARACTER_STRING, result.token());
    ASSERT_STREQ("string", result_value.c_str());
}

TEST_F(single_type_string_test, dont_match_double_byte_string) {
    input << "'string'";

    scanner.yyrestart(input);
    parser::symbol_type result = scanner.yylex(driver);

    ASSERT_NE(parser::token::DOUBLE_BYTE_CHARACTER_STRING, result.token());
}