#pragma once
/**
 * @author Thomas Brandstätter
 * @date 17.04.18.
 */

#include <algorithm>
#include <string>
#include <variant>
#include <vector>

#include "forward_ast.h"
#include "meta.h"

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


    template<typename TNT, typename ST, typename VT>
    struct type_declaration_base {

        struct spec_init
        {
            ST specification;
            VT value;
        };

        void set_spec_init(spec_init si)
        {
            specification = si.specification;
            value = si.value;
        }

        TNT type_name;
        ST specification;
        VT value;
    };


#pragma mark - B.1 Common elements
#pragma mark - B.1.1 Letters, digits and identifiers


#pragma mark - B.1.2.1 Numeric literals

    // TODO: implement 1.2 Constants types

    struct integer_literal : value_wrapper<long>
    {
    };

    struct _literal : value_wrapper<long>
    {
    };


    struct numeric_literal : value_wrapper<long>
    {
    };



#pragma mark B.1.2.3.1 Duration

    struct days : value_wrapper<double>
    {
    };

    struct interval : ast::days
    {
        interval operator-() const
        {
            interval i;
            i.value = -value;
            return i;
        }
    };

    struct duration : ast::interval
    {
        duration& operator=(const interval i)
        {
            value = i.value;
            return *this;
        }
    };

#pragma mark B.1.2.3.2 Time of day and date

    struct daytime
    {
        double hour;
        double minute;
        double second;
    };

    struct time_of_day : daytime
    {
        time_of_day & operator=(daytime & rhs)
        {
            std::swap(hour, rhs.hour);
            std::swap(minute, rhs.minute);
            std::swap(second, rhs.second);
            return *this;
        }
    };

    struct date_literal
    {
        long year;
        long month;
        long day;
    };

    struct date_and_time
    {
        date_literal date;
        daytime time;
    };

    using time_literal =
        std::variant<duration, time_of_day, date_literal, date_and_time>;



    using constant =
        std::variant<
            numeric_literal,
            std::string,
            time_literal,
            long,
            ast::value_wrapper<bool> >;



#pragma mark - B.1.3 Data types


#pragma mark B.1.3.1 Elementary data types

    enum class elementary_type_name {
        elementary_type_name            = 0x40000000,
        numeric_type_name               = elementary_type_name | 0x00010000,
        date_type_name                  = elementary_type_name | 0x00800000,
        bit_string_type_name            = elementary_type_name | 0x00200000,
        STRING                          = elementary_type_name | 0x00400001,
        WSTRING                         = elementary_type_name | 0x00400002,
        TIME                            = elementary_type_name | 0x00020000,
    };


    const int ntn = static_cast<int>(elementary_type_name::numeric_type_name);

    enum class numeric_type_name {
        integer_type_name               = ntn | 0x00002000,
        real_type_name                  = ntn | 0x00001000,
    };

    const int itn = static_cast<int>(numeric_type_name::integer_type_name);

    enum class integer_type_name {
        signed_integer_type_name        = itn | 0x00000100,
        unsigned_integer_type_name      = itn | 0x00000200,
    };

    enum class signed_integer_type_name {
        SINT                            = static_cast<int>(integer_type_name::signed_integer_type_name) | 1,
        INT,
        DINT,
        LINT
    };

    enum class unsigned_integer_type_name {
        USINT                           = static_cast<int>(integer_type_name::unsigned_integer_type_name) | 1,
        UINT,
        UDINT,
        ULINT
    };

    enum class real_type_name {
        REAL                            = static_cast<int>(numeric_type_name::real_type_name) | 1,
        LREAL,
    };

    enum class date_type_name {
        DATE                            = static_cast<int>(elementary_type_name::date_type_name) | 1,
        TIME_OF_DAY,
        DATE_AND_TIME
    };

    enum class bit_string_type_name {
        BOOL                            = static_cast<int>(elementary_type_name::bit_string_type_name) | 1,
        BYTE,
        WORD,
        DWORD,
        LWORD,
    };


#pragma mark B.1.3.2 Generic data types

    enum class generic_type_name {
         ANY                = 0x40000000
        ,ANY_DERIVED        = 0x10000000    | static_cast<int>(ANY)
        ,ANY_ELEMENTARY     = 0x20000000    | static_cast<int>(ANY)
        ,ANY_MAGNITUDE      = 0x00100000    | static_cast<int>(ANY_ELEMENTARY)
        ,ANY_NUM            = 0x00010000    | static_cast<int>(ANY_MAGNITUDE)
        ,ANY_REAL           = 0x00001000    | static_cast<int>(ANY_NUM)
        ,ANY_INT            = 0x00002000    | static_cast<int>(ANY_NUM)
        ,ANY_TIME           = 0x00020000    | static_cast<int>(ANY_MAGNITUDE)
        ,ANY_BIT            = 0x00200000    | static_cast<int>(ANY_ELEMENTARY)
        ,ANY_STRING         = 0x00400000    | static_cast<int>(ANY_ELEMENTARY)
        ,ANY_DATE           = 0x00800000    | static_cast<int>(ANY_ELEMENTARY)
    };

    using non_generic_type_name = std::variant<elementary_type_name, std::string>;

#pragma mark B.1.3.3 Derived data types


    struct simple_type_declaration : type_declaration_base<
        std::string,
        std::variant< elementary_type_name, std::string>,
        constant>
    {
    };


    // subrange ----------------------

    struct subrange {
        long min;       // TODO: IEC type instead of C++ ones
        long max;

        using list = std::vector<subrange>;
    };


    struct ss_specification
    {
        integer_type_name type_name;
        subrange value;
    };

    using subrange_specification = std::variant<std::string, ss_specification>;

    struct subrange_type_declaration : type_declaration_base<
        std::string,
        subrange_specification,
        constant>
    {
    };

    // enumerated --------------------

    struct enumerated_value
    {
        std::string type_name;
        std::string value;
    };

    using enumerated_specification = 
        std::variant<
            std::vector<enumerated_value>,
            std::string>;

    struct enumerated_type_declaration : type_declaration_base<
        std::string,
        enumerated_specification,
        enumerated_value>
    {
    };


    // string ------------------------

    struct string_type_declaration
    {
        ast::elementary_type_name type_name;
        unsigned long size;
        std::string value;
    };



    // -------------------------------
    using single_element_type_declaration = 
        std::variant<
            simple_type_declaration,
            subrange_type_declaration,
            enumerated_type_declaration>;

    // array -------------------------

    struct array_specification {
        non_generic_type_name type_name;
        std::vector<subrange> dimension;
    };

    struct structure_initialization;
    struct array_initialization;

    using array_initial_element =
        std::variant<
            constant,
            enumerated_value,
            forward_ast<structure_initialization>,
            forward_ast<array_initialization>>;


    struct array_initial_elements {
        long size;
        array_initial_element element;
    };

    struct array_initialization
    {
        using list = std::vector<array_initial_elements>;
        list elements;
    };

    struct array_type_declaration : type_declaration_base<
            std::string,
            array_specification,
            array_initialization>
    {
    };

    // structure ---------------------

    struct structure_element_initialization
    {
        using value =
            std::variant<
                constant,
                enumerated_value,
                array_initialization,
                forward_ast<structure_initialization>>;

        value init_value;
        std::string name;
    };

    struct structure_initialization
    {
        using list = std::vector<structure_element_initialization>;
        using iterator = list::iterator;

        list element_initializations;
    };

    struct initialized_structure
    {
        std::string type_name;
        structure_initialization initialization;
    };

    struct structure_element_declaration
    {
        std::string element_name;

        using spec_init =
            std::variant<
                simple_type_declaration::spec_init,
                subrange_type_declaration::spec_init,
                enumerated_type_declaration::spec_init,
                array_type_declaration::spec_init,
                initialized_structure>;

        spec_init specification_init;
    };

    struct structure_declaration
    {
        using list = std::vector<structure_element_declaration>;
        using iterator = list::iterator;
        list declarations;
    };

    using structure_specification = std::variant<structure_declaration, initialized_structure>;

    struct structure_type_declaration
    {
        std::string type_name;
        structure_specification specification;
    };

    struct type_declaration
    {
        using declaration =
            std::variant<
                single_element_type_declaration,
                array_type_declaration,
                structure_type_declaration,
                string_type_declaration>;

        declaration decl;
        std::string type_name;
    };
    
    // -------------------------------
    struct data_type_declaration
    {
        std::vector<type_declaration> declarations;
    };

    /**
     * The name is program. This typedef is used as long as the grammar is not
     * completed and will change over time.
     */
    using temporary_root = std::vector<type_declaration>;

    using root = temporary_root;


#pragma mark - B.1.4. Variables
    struct direct_variable;
    struct array_variable;
    struct structured_variable;

    using multi_element_variable = std::variant<
        forward_ast<array_variable>,
        forward_ast<structured_variable>>;

    using variable_name = std::string;

    using symbolic_variable = std::variant<
        variable_name,
        forward_ast<multi_element_variable>>;

    using variable = std::variant<
        forward_ast<direct_variable>,
        symbolic_variable>;


#pragma mark - B.1.4.1 Directly represented variables


    enum class size_prefix {
        X, B, W, D, L
    };

    enum class location_prefix {
        I, Q, M
    };

    struct direct_variable {
        using positions = std::vector<long>;

        location_prefix location;
        size_prefix size;

        positions position;
    };


#pragma mark - B.1.4.2 Multi-element variables

    using field_selector = std::string;
    using record_variable = symbolic_variable;

    struct structured_variable
    {
        record_variable record;
        field_selector field;
    };


    using subscript = std::string;
    using subscripted_variable = symbolic_variable;
    using subscript_list = std::vector<subscript>;

    struct array_variable {
        subscripted_variable variable;
        subscript_list subscripts;
    };

#pragma mark - B.1.4.3 Declaration and initialization

    enum class retain_value {
        RETAIN, NON_RETAIN, CONSTANT, UNDEFINED
    };

    enum class edge_value {
        R_EDGE, F_EDGE, UNDEFINED
    };


    using var1_list = std::vector<std::string>;

    struct var1_init_decl {
        using spec_init = std::variant<
            simple_type_declaration::spec_init,
            subrange_type_declaration::spec_init,
            enumerated_type_declaration::spec_init>;

        spec_init specification;
        var1_list variables;
    };

    struct array_var_init_decl
    {
        var1_list variables;
        array_type_declaration::spec_init specification;
    };

    struct structured_var_init_decl {
        var1_list variables;
        initialized_structure init;
    };

    using fb_name_list = std::vector<std::string>;
    using fb_name = std::string;

    struct fb_name_decl
    {
        fb_name_list fb_names;
        std::string name;
        structure_initialization initialization;
    };


}}}
