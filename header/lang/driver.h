#pragma once

#include <iostream>
#include <sstream>
#include <string>

namespace openloco {
namespace lang {

    class parser;

    class driver {
    public:
        driver() :
            _debug(true)
        {
        }

        virtual ~driver()
        {
        }

        int parse(std::istream& in, std::ostream& out);
        int parse(std::stringstream &input);
        int parse(std::ifstream &input);
        int parse(FILE *file);
        int parse();

        void set_debug(bool value) { _debug = value; }

        friend class parser;
        friend class scanner;

    private:
        bool _debug;
    };
}}