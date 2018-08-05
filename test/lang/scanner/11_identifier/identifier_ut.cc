#include <string>
#include <sstream>
#include <iostream>

#include <gtest/gtest.h>

#include "../abstract_ut.h"

class identifier_token_test : public abstract_scanner_ut {};
class identifier_value_test : public abstract_scanner_ut {};

using parser = openloco::lang::parser;
namespace ast = openloco::lang::ast;

TEST_F(identifier_token_test, match_identifier) {

    input << "identifier";

    scanner.reset(input);
    parser::symbol_type result = scanner.yylex(driver);

    ASSERT_EQ(result.token(), parser::token::IDENTIFIER);
}

TEST_F(identifier_token_test, match_identifier_w_underscore) {

    input << "identi_fier";

    scanner.reset(input);
    parser::symbol_type result = scanner.yylex(driver);
    ASSERT_EQ(result.token(), parser::token::IDENTIFIER);
}

TEST_F(identifier_token_test, match_identifier_w_underscore_end) {

    input << "identifier_";

    scanner.reset(input);
    parser::symbol_type result = scanner.yylex(driver);
    ASSERT_EQ(result.token(), parser::token::IDENTIFIER);
}

TEST_F(identifier_token_test, reject_identifier_begin_w_underscore) {

    input << "_identifier";

    scanner.reset(input);
    parser::symbol_type result = scanner.yylex(driver);
    ASSERT_NE(result.token(), parser::token::IDENTIFIER);
}

TEST_F(identifier_token_test, reject_identifier_begin_w_number) {

    input << "1stidentifier";

    scanner.reset(input);
    parser::symbol_type result = scanner.yylex(driver);
    ASSERT_NE(result.token(), parser::token::IDENTIFIER);
}

TEST_F(identifier_value_test, match_values) {

    input << "identifier";
    std::string expected { input.str() };

    scanner.reset(input);
    parser::symbol_type result = scanner.yylex(driver);
    auto result_value = result.value.as<ast::identifier>();


    ASSERT_STREQ(expected.c_str(), result_value.value.c_str());
}