#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>

#include <header/lang/scanner.h>
#include <header/lang/driver.h>


int
openloco::lang::driver::parse(std::istream& in, std::ostream& out) {

    openloco::lang::scanner scanner {*this};
    openloco::lang::parser parser {*this, scanner};

    scanner.yyrestart(in);
    if (_debug) {
        scanner.set_debug(_debug);
    }
    //parser.set_debug_level(1);
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
