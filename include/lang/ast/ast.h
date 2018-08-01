#pragma once
/**
 * @author Thomas Brandstätter
 * @date 17.04.18.
 */

#include <algorithm>
#include <map>
#include <string>
#include <variant>
#include <vector>

//#include <llvm/IR/LLVMContext.h>
//#include <llvm/IR/IRBuilder.h>
//#include <llvm/IR/Module.h>
//#include <llvm/IR/Value.h>

#include "forward_ast.h"
#include "meta.h"

namespace openloco {
namespace lang {
namespace ast {

//    static llvm::LLVMContext context;
//    static llvm::IRBuilder<> builder(context);
//    static std::unique_ptr<llvm::Module> module;
//    static std::map<std::string, llvm::Value *> named_values;


    /**
     * value_wrapper
     *
     * On some places cpp requires non-fundamental types, therefore we wrap it.
     *
     * @see https://en.cppreference.com/w/cpp/language/types
     * @tparam FT The fundamental type to wrap
     */
    template<typename FT>
    struct value_wrapper
    {

        value_wrapper() : value() {}
        value_wrapper(FT& rhs) : value(rhs) {}
        value_wrapper(const FT& rhs) : value(rhs) {}

        virtual ~value_wrapper() {}

        FT value;

        operator FT () { return value; }
    };


    /**
     * type_declaration_base
     *
     * All type declarations in IEC 61131-3 have the same structure, this struct implements the common structure.
     *
     * @tparam TNT The type name type
     * @tparam ST The specification type
     * @tparam VT The value type
     */
    template<typename TNT, typename ST, typename VT>
    struct type_declaration_base {

        virtual ~type_declaration_base() {}

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

    struct identifier : std::string
    {
        using base_type = std::string;
        using base_type::base_type;
    };

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
        value_wrapper<double> hour;
        value_wrapper<double> minute;
        value_wrapper<double> second;
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
        long min;       // TODO: IEC type instead of C++ ones?
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
        using list = std::vector<enumerated_value>;

        std::string type_name;
        std::string value;
    };

    struct enumerated_specification : std::variant<enumerated_value::list, std::string>
    {
        using base_type = std::variant<enumerated_value::list, std::string>;
        using base_type::base_type;
    };

    struct enumerated_type_declaration : type_declaration_base<std::string, enumerated_specification, enumerated_value>
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
    struct single_element_type_declaration : std::variant<
            simple_type_declaration,
            subrange_type_declaration,
            enumerated_type_declaration>
    {
        using base_type = std::variant<
            simple_type_declaration,
            subrange_type_declaration,
            enumerated_type_declaration>;

        using base_type::base_type;
    };

    // array -------------------------

    struct array_specification {
        non_generic_type_name type_name;
        std::vector<subrange> dimension;
    };

    struct structure_initialization;
    struct array_initialization;

    struct array_initial_element : public std::variant<
            constant,
            enumerated_value,
            forward_ast<structure_initialization>,
            forward_ast<array_initialization>>
    {
        using base_type = std::variant<
            constant,
            enumerated_value,
            forward_ast<structure_initialization>,
            forward_ast<array_initialization>>;

        using base_type::base_type;
    };


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
        identifier name;
    };

    struct structure_initialization
    {
        using list = std::vector<structure_element_initialization>;
        using iterator = list::iterator;

        list element_initializations;
    };

    struct initialized_structure
    {
        identifier type_name;
        structure_initialization initialization;
    };

    struct structure_element_declaration
    {
        identifier element_name;

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
        identifier type_name;
        structure_specification specification;
    };

    struct type_declaration
    {
        using list = std::vector<type_declaration>;
        using iterator = list::iterator;

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
        type_declaration::list declarations;

    };

    /**
     * The name is program. This typedef is used as long as the grammar is not
     * completed and will change over time.
     */
    using temporary_root = type_declaration::list;

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







#pragma mark - B.2 Language IL (Instruction List)
#pragma mark - B.2.1 Instructions and operands

    struct il_instruction;
    struct il_simple_operation;
    struct il_expression;
    enum class il_simple_operator;
    enum class il_expr_operator;
    struct il_jump_operation;
    struct il_fb_call;
    //struct il_formal_funct_call;
    enum class il_return_operator;
    struct operand_list;
    struct simple_instruction_list;


    struct instruction_list : std::vector<il_instruction>
    {
    };

    struct label : std::string
    {
        using base_type = std::string;
        using base_type::base_type;
    };


    struct il_operand : std::variant<constant, variable, enumerated_value>
    {
        using base_type = std::variant<constant, variable, enumerated_value>;
        using base_type::base_type;
    };

    struct il_operand_list : std::vector<il_operand>
    {
        using base_type = std::vector<il_operand>;
        using base_type::base_type;
    };

    struct il_simple_operation
    {
        struct operation
        {
            forward_ast<il_simple_operator> simple_operator;
            std::vector<il_operand> operands;
        };

        struct function
        {
            identifier function_name;
            il_operand_list operand_list;
        };

        std::variant<operation, function> operation;
    };

    struct il_formal_funct_call;
    struct il_expression;
    struct il_simple_instruction : std::variant<
         il_simple_operation
        ,forward_ast<il_expression>
        ,forward_ast<il_formal_funct_call>>
    {
        using base_type = std::variant<il_simple_operation, forward_ast<il_expression>, forward_ast<il_formal_funct_call>>;
        using base_type::base_type;
    };

    struct simple_instr_list : std::vector<il_simple_instruction>
    {
        using base_type = std::vector<il_simple_instruction>;
        using base_type::base_type;
    };

    struct il_expression
    {
        forward_ast<il_expr_operator> operator_;
        std::vector<il_operand> operands;
        forward_ast<simple_instruction_list> instruction_list;
    };

    enum class il_jump_operator;
    struct il_jump_operation
    {
        forward_ast<il_jump_operator> jump_operator;
        label label;
    };


    enum class il_call_operator;
    struct il_param_list;
    struct il_fb_call
    {
        struct fb
        {
            forward_ast<il_call_operator> call_operator;
            fb_name name;
            // boost::optional
            forward_ast<il_param_list> param_list;
        };

        std::variant<fb, il_operand_list> TODO_name;
    };

    struct il_param_instruction;
    struct il_param_list : std::vector<il_param_instruction>
    {
        using base_type = std::vector<il_param_instruction>;
        using base_type::base_type;
    };

    struct il_formal_funct_call
    {
        // todo function_name
        std::string name;
        il_param_list param_list;
    };

    struct il_param_assignment;
    struct il_param_out_assignment;
    struct il_param_instruction : std::variant<
        forward_ast<il_param_assignment>,
        forward_ast<il_param_out_assignment>>
    {
    };



    struct il_assign_operator;
    struct il_param_assignment
    {
        forward_ast<il_assign_operator> assign_operator;
        using operand = std::variant<il_operand, simple_instr_list>;
        operand op;
    };

    struct il_assign_out_operator;
    struct il_param_out_assignment
    {
        forward_ast<il_assign_out_operator> assign_out_operator;
        variable variable;
    };

    struct il_instruction
    {
        using instruction = std::variant<
            il_simple_operator
            ,il_expression
            ,il_jump_operation
            ,il_fb_call
            //,il_formal_funct_call
            ,il_return_operator
        >;

        label label;
        instruction instr;
    };

#pragma mark - B.2.2 Operators

    /**
     * append il_expr_operator, or at least ensure both usages
     */
    enum class il_simple_operator
    {
        LD, LDN, ST, STN, NOT,
        S, R, S1, R1,
        CLK, CU, CD,
        PV, IN, PT
    };

    enum class il_expr_operator
    {
        AND, AND_, OR, XOR, ANDN, _N, ORN, XORN,
        ADD, SUB, MUL, DIV, MOD,
        GT, GE, EQ, LT, LE, NE
    };

    struct il_assign_operator : std::string
    {
        using base_type = std::string;
        using base_type::base_type;
    };

    struct il_assign_out_operator
    {
        bool is_negated;
        std::string name;
    };

    enum class il_call_operator
    {
        CAL, CALC, CLCN
    };

    enum class il_return_operator
    {
        RET, RETC, RETCN
    };

    enum class il_jump_operator
    {
        JMP, JMPC, JMPCN
    };


#pragma mark - B.3 Language ST (Structured Text)

#pragma mark - B.3.1 Expressions




    struct param_assignment;
    struct primary_expression_fc
    {
        std::string function_name;
        std::vector<param_assignment> param_assignments;
    };

    struct expression;
    struct primary_expression : std::variant<
         constant
        ,enumerated_value
        //,variable
        ,forward_ast<expression>
        ,primary_expression_fc>
    {
        using base_type = std::variant<constant, enumerated_value, forward_ast<expression>, primary_expression_fc>;
        using base_type::base_type;
    };

    enum class unary_operator
    {
        MINUS, NOT
    };

    struct unary_expression
    {
        unary_operator operator_;
        forward_ast<primary_expression> expression;
    };

    struct power_expression
    {
        unary_expression base;
        unary_expression exponent;
    };

    enum class multiply_operator
    {
         Multiplication
        ,Division
        ,Modulo
    };

    struct term
    {
        struct multiplicant
        {
            multiply_operator operator_;
            power_expression expression;
        };

        forward_ast<power_expression> expression;
        std::vector<multiplicant> multiplicants;
    };

    enum class add_operator
    {
        PLUS, MINUS
    };


    struct add_expression
    {
        term first_term;

        std::vector<add_operator> adds;
        std::vector<term> terms;

        void add_summand(forward_ast<add_operator> operator_, forward_ast<term> term_)
        {
            adds.push_back(operator_);
            terms.push_back(term_);
            assert (adds.size() == terms.size());
        }
    };

    enum class comparison_operator
    {
        LT, GT, LTE, GTE
    };

    /*
     * TODO: generalize the following:
     *
        std::vector<add_operator> adds;
        std::vector<term> terms;

        void add_summand(add_operator operator_, term term_)
        {
            adds.push_back(operator_);
            terms.push_back(term_);
            assert (adds.size() == terms.size());
        }
     */


    struct equ_expression
    {
        add_expression summand;

        std::vector<comparison_operator> comparisons;
        std::vector<add_expression> adds;

        void add_comparison(comparison_operator operator_, add_expression add_expr)
        {
            comparisons.push_back(operator_);
            adds.push_back(add_expr);
            assert (adds.size() == comparisons.size());
        }
    };

    struct comparison
    {
        equ_expression comparand;

        enum class equal_operator
        {
            EQ, NEQ
        };

        std::vector<equal_operator> comparisons;
        std::vector<equ_expression> equs;

        void add_comparison(equal_operator operator_, forward_ast<equ_expression> equ_expr)
        {
            comparisons.push_back(operator_);
            equs.push_back(equ_expr);
            assert (equs.size() == comparisons.size());
        }
    };


    struct and_expression
    {
        comparison first_compare;
        std::vector<comparison> compares;
    };

    struct xor_expression
    {
        and_expression first_and;
        std::vector<and_expression> ands;
    };

    struct expression
    {
        xor_expression first_expression;
        std::vector<xor_expression> xors;
    };

#pragma mark - B.3.2 Statements

    struct assignment_statement;
    struct subprogram_control_statement;
    struct selection_statement;
    struct iteration_statement;

    struct statement : std::variant<
         forward_ast<assignment_statement>
        ,forward_ast<subprogram_control_statement>
        ,forward_ast<selection_statement>
        ,forward_ast<iteration_statement>>
    {
        using base_type = std::variant<
            forward_ast<assignment_statement>
            ,forward_ast<subprogram_control_statement>
            ,forward_ast<selection_statement>
            ,forward_ast<iteration_statement>>;
        using base_type::base_type;
    };

    struct statement_list : std::vector<statement>
    {
        using base_type = std::vector<statement>;
        using base_type::base_type;
    };


#pragma mark - B.3.2.1 Assignment statements

    // TODO:
    struct assignment_statement
    {
        //variable var;
        expression exp;
    };

#pragma mark - B.3.2.2 Subprogram control statements

    // TODO:
    struct subprogram_control_statement
    {
        //fb_invocation invocation;
    };

    struct param_assignment
    {
        struct assigment
        {
            //variable_name name;
            expression exp;
        };

        // TODO
        struct TODO_find_a_name
        {
            // variable_name name;
            // variable var;
        };
    };

#pragma mark - B.3.2.3 Selection statements

    struct case_list_element : std::variant<
         subrange
        // TODO: ,signed_integer
        ,enumerated_value>
    {
        using base_type = std::variant<subrange, enumerated_value>;
        using base_type::base_type;
    };

    struct case_list : std::vector<case_list_element>
    {
        using base_type = std::vector<case_list_element>;
        using base_type::base_type;
    };

    struct case_element
    {
        case_list case_;
        statement_list statement;
    };

    struct case_statement
    {
        expression condition;
        std::vector<case_element> elements;
        statement_list else_statements;
    };

    struct if_statement
    {
        struct if_then
        {
            expression condition;
            statement_list then_statements;
        };

        struct else_if_then
        {
            expression condition;
            statement_list then_statements;
        };

        if_then if_;
        std::vector<else_if_then> else_if;
        statement_list else_;
    };

    struct selection_statement : std::variant<if_statement, case_statement>
    {
        using base_type = std::variant<if_statement, case_statement>;
        using base_type::base_type;
    };

#pragma mark - B.3.2.4 Iteration statements

    struct control_variable : identifier
    {
        using base_type = identifier;
        using base_type::base_type;
    };

    struct for_list
    {
        expression from;
        expression to;
        expression by;
    };

    struct for_statement
    {
        control_variable control;
        for_list list;
        statement_list statements;
    };

    struct while_statement
    {
        expression while_;
        statement_list do_;
    };

    struct repeat_statement
    {
        statement_list repeat_statements;
        expression until_expression;
    };

    struct exit_statement
    {
    };

    struct iteration_statement : std::variant<
         for_statement
        ,while_statement
        ,repeat_statement
        ,exit_statement>
    {
        using base_type = std::variant<for_statement, while_statement, repeat_statement ,exit_statement>;
        using base_type::base_type;
    };

}}}
