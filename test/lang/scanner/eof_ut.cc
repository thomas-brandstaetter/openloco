#include <iostream>
#include <sstream>

#include <gtest/gtest.h>

#include "abstract_ut.h"


class eof_test : public abstract_scanner_ut { };

using openloco::lang::parser;


TEST_F(eof_test, match_eof) {
    std::stringstream ss(EOF);

    scanner.yyrestart(ss);
    parser::symbol_type result = scanner.yylex(driver);
}

