#pragma once

#include <iostream>

#ifndef yyFlexLexerOnce
#include <FlexLexer.h>
#endif

#include <parser.hh>
#include <location.hh>

namespace openloco {
namespace lang {

    // forward declare to avoid an include
    class driver;

    class scanner : public yyFlexLexer {
    public:
        scanner(driver &driver) : yyFlexLexer(std::cin, std::cout), _driver(driver), _scan_eol(false) {}
        scanner(driver &driver, std::istream &in) : yyFlexLexer(in, std::cout), _driver(driver) {}
        virtual ~scanner() {}
        virtual openloco::lang::parser::symbol_type yylex(openloco::lang::driver &driver);

        /** EOL advanches as symbol */
        void set_scan_eol();
        /** Treat EOL as whitespace */
        void unset_scan_eol();
        bool is_scan_eol();

        void yyerror(const char* message);

    private:
        void remove_underscore(std::string& str_value);

        driver &_driver;
        bool _scan_eol;
    };
}}