#include <string>
#include <sstream>
#include <iostream>

#include <gtest/gtest.h>

#include "../abstract_ut.h"

class identifier_test : public abstract_scanner_ut {};

using openloco::lang::parser;

TEST_F(identifier_test, match_identifier) {

    input << "11_identifier";

    scanner.reset(input);
    parser::symbol_type result = scanner.yylex(driver);

    ASSERT_EQ(result.token(), parser::token::IDENTIFIER);
}

TEST_F(identifier_test, dont_match_identifier_w_underscore_front) {

    input << "_identifier";

    scanner.reset(input);
    parser::symbol_type result = scanner.yylex(driver);
    ASSERT_NE(result.token(), parser::token::IDENTIFIER);
}

TEST_F(identifier_test, match_identifier_w_underscore_middle) {

    input << "identi_fier";

    scanner.reset(input);
    parser::symbol_type result = scanner.yylex(driver);
    ASSERT_EQ(result.token(), parser::token::IDENTIFIER);
}

TEST_F(identifier_test, match_identifier_w_underscore_end) {

    input << "identifier_";

    scanner.reset(input);
    parser::symbol_type result = scanner.yylex(driver);
    ASSERT_EQ(result.token(), parser::token::IDENTIFIER);
}

TEST_F(identifier_test, reject_identifier_begin_w_underscore) {

    input << "_identifier";

    scanner.reset(input);
    parser::symbol_type result = scanner.yylex(driver);

}