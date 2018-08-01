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

        /** \addtogroup Constructors */
        /** @{ */
        scanner(driver &driver) : yyFlexLexer(std::cin, std::cout), _driver(driver), _scan_eol(false) {}
        scanner(driver &driver, std::istream &in) : yyFlexLexer(in, std::cout), _driver(driver) {}
        /** @} */

        virtual ~scanner() {}
        virtual openloco::lang::parser::symbol_type yylex(openloco::lang::driver &driver);

        /** \addtogroup Scanner control */
        /** @{ */
        void reset(std::istream* input_file);
        void reset(std::istream& input_file);

        void set_scan_eol(bool scan_eol);       /**< Scanner treats EOL as symbol or whitespace */
        /** @} */

        void yyerror(const char* message, location loc);

        location loc;

    private:


        /** \addtogroup Scanner control */
        /** @{ */
        void reset_location();
        /** @} */


        /** \addtogroup Helper */
        /** @{ */

        /**
         * prepare IEC numeric constants for converting from string to a numeric type
         *
         * @example
         *      (2, "2#1101_0010") --> 11010010
         */
        void cleanup_number(const unsigned long prefix_length, std::string& str_value) const  ;
        /** @} */


        driver &_driver;
        bool _scan_eol;
    };
}}
