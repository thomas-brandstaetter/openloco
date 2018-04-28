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


        /** \addtogroup Scanner control */
        /** @{ */
        void reset(std::istream* input_file);
        void reset(std::istream& input_file);

        void set_scan_eol();            /**< Scanner treats EOL as symbol */
        void unset_scan_eol();          /**< Scanner treats EOL as whitespace */
        /** @} */

        void yyerror(const char* message, location loc);

        location loc;

    private:


        /** \addtogroup Number helper */
        /** @{ */
        void reset_location();
        /** @{ */


        /** \addtogroup Number helper */
        /** @{ */

        /**
         * @example
         *      (2, "2#1101_0010") --> 11010010
         * @param erease_end
         */
        void cleanup_number(const unsigned long erease_end, std::string& str_value) const  ;
        /** @} */



        driver &_driver;
        bool _scan_eol;
    };
}}