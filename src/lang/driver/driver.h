#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <ast/ast.h>

#include <driver/file.h>

namespace openloco {
namespace lang {

    class parser;

    class driver {
    public:

        /**
         * ease the way we calculate with dates
         */
        struct date_calculator {

            const long kMillisecondPerSecond;
            const long kSecondPerMinute;
            const long kMinutePerHour;
            const long kHourPerDay;

            static date_calculator& shared_instance() {
                static date_calculator dc;
                return dc;
            }


            inline double
            days_in_ms(const double value)
            {
                return
                    value
                    * kHourPerDay
                    * kMinutePerHour
                    * kSecondPerMinute
                    * kMillisecondPerSecond;
            }

            inline double
            hours_in_ms(const double value) const
            {
                return
                    value
                    * kMinutePerHour
                    * kSecondPerMinute
                    * kMillisecondPerSecond;
            }

            inline double
            minutes_in_ms(const double value) const
            {
                return value * kSecondPerMinute * kMillisecondPerSecond;
            }

            inline double
            seconds_in_ms(const double value) const
            {
                return value * kSecondPerMinute;
            }

            date_calculator()
                :    kMillisecondPerSecond(1000)
                ,kSecondPerMinute(60)
                ,kMinutePerHour(60)
                ,kHourPerDay(24)
            {}
        };

        date_calculator dc;

        /** \addtogroup Constructors */
        /** @{ */
        driver() :
            dc(),
            _tokens(),
            _debug(false),
            _current_file(nullptr)
        {
        }
        /** @} */

        virtual ~driver()
        {
        }

        /** \addtogroup Parsing */
        /** @{ */

        int parse(std::istream& in, std::ostream& out = std::cout);
        int parse(file& infile, std::ostream& out = std::cout);

        /** @} */

        void set_debug(bool value) { _debug = value; }

        /** /addgroup Gathering */
        /** @{ */

        /**
         * Build a pushdown automaton while parsing.
         *
         * @details Needs invocation in the parser code.
         *
         * @param token The token to add.
         */
        void add_token(std::string token);

        void set_root(ast::root root)   { _ast_root = root; }
        ast::root& get_root()           { return _ast_root; }
        /** @} */

        friend class parser;
        friend class scanner;

    private:

        std::vector<std::string> _tokens;
        file* _current_file;
        bool _debug;

        ast::root _ast_root;
    };
}}
