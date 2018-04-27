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

        value_wrapper(value_wrapper &) = default;
        value_wrapper(const value_wrapper &) = default;

        value_wrapper& operator=(value_wrapper& other) = default;
        value_wrapper& operator=(const value_wrapper& other)  = default;

        value_wrapper(value_wrapper&& rhs) = default;
        value_wrapper& operator=(value_wrapper && ) = default;


        virtual ~value_wrapper() {}

        VT value;
    };

    template<typename TT, typename VT>
    struct literal_wrapper : value_wrapper<VT>
    {
        literal_wrapper() : value_wrapper<VT>(), type() {}

        literal_wrapper(TT rhs_type, VT rhs_value) :
            value_wrapper<VT>(rhs_value),
            type(rhs_type) {}

        literal_wrapper(literal_wrapper &) = default;
        literal_wrapper(const literal_wrapper &) = default;

        literal_wrapper(literal_wrapper&& rhs) = default;
        literal_wrapper& operator=(literal_wrapper && ) = default;

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

    typedef enum elementary_type_name_ {

         undefined = 0

        ,numeric_type_name
        ,date_type_name
        ,bit_string_type_name
        ,STRING
        ,WSTRING
        ,TIME

        ,integer_type_name
        ,real_type_name

        ,signed_integer_type_name
        ,unsigned_integer_type_name

        ,SINT
        ,INT
        ,DINT
        ,LINT

        ,USINT
        ,UINT
        ,UDINT
        ,ULINT

        ,REAL
        ,LREAL

        ,DATE
        ,TIME_OF_DAY
        ,TOD
        ,DATE_AND_TIME
        ,DT

        ,BOOL
        ,BYTE
        ,WORD
        ,DWORD
        ,LWORD

    } elementary_type_name;

//    typedef elementary_type_name numeric_type_name;
//    typedef elementary_type_name integer_type_name;
    typedef elementary_type_name integer_literal_value;
//    typedef elementary_type_name signed_integer_type_name;
//    typedef elementary_type_name unsigned_integer_type_name;
    typedef elementary_type_name real_integer_type_name;
    typedef elementary_type_name date_integer_type_name;
    typedef elementary_type_name bit_string_integer_type_name;

#pragma mark - B.1.3 Data types


    struct non_generic_type_name : boost::variant<elementary_type_name, std::string> {};



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


#pragma mark - B.1.2.1 Numeric literals

//        struct boolean_literal  :
//
//        struct integer_literal  : value_wrapper<elementary_type_name> {};
//        struct real_literal     : value_wrapper<elementary_type_name> {};
//
//        struct numeric_literal  : value_wrapper<elementary_type_name> { };



}}}