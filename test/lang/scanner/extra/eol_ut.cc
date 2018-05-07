/**
 * @author Thomas Brandstätter 
 * @date 01.05.18.
 */


#include <iostream>
#include <sstream>

#include <gtest/gtest.h>

#include "../abstract_ut.h"

class eol_scanner_test : public abstract_scanner_ut { };

using openloco::lang::parser;


TEST_F(eol_scanner_test, defaults_to_disable_scanning_for_EOL) {
    input << "\n";

    scanner.reset(input);
    parser::symbol_type result = scanner.yylex(driver);

    ASSERT_EQ(parser::token::END, result.token());
}

TEST_F(eol_scanner_test, disable_scanning_for_EOL) {
    input << "\n";

    scanner.reset(input);
    scanner.set_scan_eol(false);
    parser::symbol_type result = scanner.yylex(driver);

    ASSERT_EQ(parser::token::END, result.token());
}

TEST_F(eol_scanner_test, enable_scanning_for_EOL) {
    input << "\n";

    scanner.reset(input);
    scanner.set_scan_eol(true);
    parser::symbol_type result = scanner.yylex(driver);

    ASSERT_EQ(parser::token::EOL, result.token());
}

