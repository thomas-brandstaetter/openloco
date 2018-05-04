#pragma once
/**
 * @author Thomas Brandstätter
 * @date 17.04.18.
 */

#include <string>

#include <boost/variant.hpp>

namespace openloco {
namespace lang {
namespace ast {

    template<typename VT>
    struct value_wrapper
    {
        value_wrapper() : value() {}
        value_wrapper(VT& rhs) : value(rhs) {}
        value_wrapper(const VT& rhs) : value(rhs) {}

        virtual ~value_wrapper() {}

        VT value;
    };

    template<typename TT, typename VT>
    struct typed_value_wrapper : value_wrapper<VT>
    {
        typed_value_wrapper() : value_wrapper<VT>(), type() {}

        typed_value_wrapper(TT rhs_type, VT rhs_value) :
            value_wrapper<VT>(rhs_value),
            type(rhs_type) {}

        typed_value_wrapper(typed_value_wrapper &) = default;
        typed_value_wrapper(const typed_value_wrapper &) = default;

        typed_value_wrapper(typed_value_wrapper&& rhs) = default;
        typed_value_wrapper& operator=(typed_value_wrapper && ) = default;

        VT value;
        TT type;
    };

#pragma mark - B.1.3.1 Elementary data types

    /*
     *  elementary_type_name
     *      numeric_type_name
     *          integer_type_name
     *              signed
     *                  SINT
     *                  INT
     *                  DINT
     *                  LINT
     *              unsigned
     *                  USINT
     *                  UINT
     *                  UDINT>
     *                  ULINT
     *          real_type_name
     *              REAL
     *              LREAL
     *      date_type_name
     *          DATE
     *          TIME_OF_DAY TOD
     *          DATE_AND_TIME DT
     *      bit_string_type_name
     *          BOOL
     *          BYTE
     *          WORD
     *          DWORD
     *          LWORD
     *      string
     *      time
     *
     */

    /**
     * @details type range 2^47 > 2^39
     */
    typedef enum elementary_type_name_ {

         undefined = 0

        ,numeric                  = 0x0100000000000ul
        ,date                     = 0x0200000000000ul
        ,bit_string               = 0x0400000000000ul
        ,string                   = 0x0800000000000ul
        ,time                     = 0x1000000000000ul

        ,TIME                     = 0x1 | time

        ,integer                  = 0x0001000000000ul | numeric
        ,real                     = 0x0002000000000ul | numeric

        ,signed_integer           = 0x0000010000000ul | integer
        ,unsigned_integer         = 0x0000020000000ul | integer

        ,STRING                   = 0x1 | string
        ,WSTRING                  = 0x2 | string

        ,SINT                     = 0x1 | signed_integer
        ,INT                      = 0x2 | signed_integer
        ,DINT                     = 0x4 | signed_integer
        ,LINT                     = 0x8 | signed_integer

        ,USINT                    = 0x1 | unsigned_integer
        ,UINT                     = 0x2 | unsigned_integer
        ,UDINT					  = 0x4 | unsigned_integer
        ,ULINT					  = 0x8 | unsigned_integer

        ,REAL					  = 0x1 | real
        ,LREAL					  = 0x2 | real

        ,DATE					  = 0x01 | date
        ,TIME_OF_DAY			  = 0x02 | date
        ,TOD					  = 0x04 | date
        ,DATE_AND_TIME			  = 0x08 | date
        ,DT						  = 0x10 | date

        ,BOOL                     = 0x1 | numeric

        ,BYTE                     = 0x1 | bit_string
        ,WORD                     = 0x2 | bit_string
        ,DWORD                    = 0x4 | bit_string
        ,LWORD                    = 0x8 | bit_string

    } elementary_type_name;

//    typedef elementary_type_name numeric_type_name;
//    typedef elementary_type_name integer_type_name;
    typedef elementary_type_name integer_literal_value;
//    typedef elementary_type_name signed_integer_type_name;
//    typedef elementary_type_name unsigned_integer_type_name;
    typedef elementary_type_name real_integer_type_name;
    typedef elementary_type_name date_integer_type_name;
    typedef elementary_type_name bit_string_integer_type_name;

#pragma mark - B.1.2.1 Numeric literals

//        struct boolean_literal  :
//
//        struct integer_literal  : value_wrapper<elementary_type_name> {};
//        struct real_literal     : value_wrapper<elementary_type_name> {};
//
//        struct numeric_literal  : value_wrapper<elementary_type_name> { };

#pragma mark B.1.2.3.1 Duration

    struct days : value_wrapper<double> {};

    struct interval : value_wrapper<ast::days> {};
    struct duration : value_wrapper<ast::interval> {};

#pragma mark B.1.2.3.2 Time of day and date

    struct daytime {
        double hour;
        double minute;
        double second;
    };

    struct time_of_day : daytime {
        time_of_day & operator=(daytime & rhs) {
            std::swap(hour, rhs.hour);
            std::swap(minute, rhs.minute);
            std::swap(second, rhs.second);
            return *this;
        }
    };

    struct date_literal {
        long year;
        long month;
        long day;
    };

    struct date_and_time {
        date_literal date;
        daytime time;
    };

    struct time_literal : boost::variant<
        duration,
        time_of_day,
        date_literal,
        date_and_time
    >
    {};


#pragma mark - B.1.3 Data types


    struct non_generic_type_name : boost::variant<
        elementary_type_name,
        std::string>
    {
    };



#pragma mark B.1.3.2 Generic data types
    // B.1.3.2 Generic data types
    enum generic_type_name {
        ANY                = 0x80000000
        ,ANY_DERIVED        = 0x10000000    | ANY
        ,ANY_ELEMENTARY     = 0x20000000    | ANY
        ,ANY_MAGNITUDE      = 0x00100000    | ANY_ELEMENTARY
        ,ANY_NUM            = 0x00010000    | ANY_MAGNITUDE
        ,ANY_REAL           = 0x00001000    | ANY_NUM
        ,ANY_INT            = 0x00002000    | ANY_NUM
        ,ANY_TIME           = 0x00020000    | ANY_MAGNITUDE
        ,ANY_BIT            = 0x00200000    | ANY_ELEMENTARY
        ,ANY_STRING         = 0x00400000    | ANY_ELEMENTARY
        ,ANY_DATE           = 0x00800000    | ANY_ELEMENTARY
    };

#pragma mark B.1.3.3 Derived data types


    struct string_type_declaration
    {
        elementary_type_name type;
        unsigned long size;
        std::string value;
    };

}}}
