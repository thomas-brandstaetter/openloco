#include <iostream>
#include <string>
#include <sstream>

#include <gtest/gtest.h>

#include "../abstract_ut.h"

using openloco::lang::parser;

class single_type_string_test : public abstract_scanner_ut { };

TEST_F(single_type_string_test, match_empty_string) {
    input << "''";

    scanner.yyrestart(input);
    parser::symbol_type result = scanner.yylex(driver);
    char * result_value = result.value.as<char *>();

    ASSERT_STREQ("", result_value);
}

TEST_F(single_type_string_test, match_string) {
    input << "'string'";

    scanner.yyrestart(input);
    parser::symbol_type result = scanner.yylex(driver);
    std::string result_value = result.value.as<std::string>();

    ASSERT_STREQ("string", result_value.c_str());
}