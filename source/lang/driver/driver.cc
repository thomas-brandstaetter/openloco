#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>

#include <driver/driver.h>


namespace openloco {
namespace lang {


    int
    Driver::parse(std::istream &in, std::ostream &out)
    {

        scanner scanner{*this, in};
        parser parser{*this, scanner};

        scanner.yyrestart(in);
        scanner.set_debug(1);
        parser.set_debug_level(1);
        parser.set_debug_stream(std::cerr);
        int res = parser.parse();

        return res;
    }

    int
    Driver::parse(File& infile, std::ostream &out)
    {
        openloco::lang::FileStreambuffer fsb { infile };
        std::istream is { &fsb };

        _current_file = &infile;
        int res = parse(is, out);
        _current_file = nullptr;

        return res;
    }


    void
    Driver::add_token(std::string token)
    {
        _tokens.push_back(token);
    }

}}
