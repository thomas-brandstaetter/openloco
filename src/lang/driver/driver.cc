#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>

#include <scanner/scanner.h>
#include <driver/driver.h>


int
openloco::lang::driver::parse(std::istream& in, std::ostream& out) {

    openloco::lang::scanner scanner {*this};
    openloco::lang::parser parser {*this, scanner};

    scanner.yyrestart(in);
    scanner.set_debug(1);
    parser.set_debug_level(false);
    int res = parser.parse();

    return res;
}

int
openloco::lang::driver::parse(std::stringstream &input) {
    return parse(input, std::cout);
}

int
openloco::lang::driver::parse(std::ifstream &input) {
    return parse(input, std::cout);
}

int
openloco::lang::driver::parse() {
    return parse(std::cin, std::cout);
}

void
openloco::lang::driver::add_token(std::string token) {
    _tokens.push_back(token);
}