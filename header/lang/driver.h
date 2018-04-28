#pragma once

#include <iostream>
#include <sstream>
#include <string>

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

        driver() :
            _debug(true),
            dc()
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