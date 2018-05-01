#line 1 "preamble.yy"
%skeleton "lalr1.cc"
%require  "3.0"

%defines
%define api.namespace { openloco::lang }
%define parser_class_name {parser}
%define api.value.type variant
%define api.token.constructor
%define parse.assert true
//%define parse.error verbose
//%debug
%locations


%glr-parser
%expect 6
%expect-rr 5


%param {openloco::lang::driver &driver}
%parse-param {openloco::lang::scanner &scanner}

%code requires {
    #include <ast/ast.h>
    #include <boost/variant.hpp>

    namespace openloco {
    namespace lang {
        class scanner;
        class driver;
    }}

    #define YY_NULLPTR nullptr
    //#define YYERROR_VERBOSE 1
}

%{
    //#define YYDEBUG 1

    #include <cmath>
    #include <cassert>
    #include <iostream>

    #include <driver/driver.h>
    #include <scanner/scanner.h>

    #include <parser.hh>
    #include <location.hh>

    #undef yylex
    #define yylex scanner.yylex
%}

#line 60 "preamble.yy"
%token END EOF_ EOL

%token ACTION
%token AND
%token ANY
%token ANY_BIT
%token ANY_DATE
%token ANY_DERIVED
%token ANY_ELEMENTARY
%token ANY_INT
%token ANY_MAGNITUDE
%token ANY_NUM
%token ANY_REAL
%token ANY_STRING
%token ARRAY
%token AT
%token BOOL
%token BY
%token BYTE
%token CASE
%token CONFIGURATION
%token CONSTANT
%token D
%token DATE
%token DATE_AND_TIME
%token DINT
%token DO
%token DT
%token DWORD
%token E
%token ELSE
%token ELSIF
%token EN
%token END_ACTION
%token END_CASE
%token END_CONFIGURATION
%token END_FOR
%token END_FUNCTION
%token END_FUNCTION_BLOCK
%token END_IF
%token END_PROGRAM
%token END_REPEAT
%token END_RESOURCE
%token END_STEP
%token END_STRUCT
%token END_TRANSITION
%token END_TYPE
%token END_VAR
%token END_WHILE
%token ENO
%token EXIT
%token FALSE
%token FOR
%token FROM
%token FUNCTION
%token FUNCTION_BLOCK
%token F_EDGE
%token IF
%token INITIAL_STEP
%token INT
%token INTERVAL
%token LINT
%token LREAL
%token LWORD
%token MOD
%token NON_RETAIN
%token NOT
%token OF
%token ON
%token OR
%token PRIORITY
%token PROGRAM
%token READ_ONLY
%token READ_WRITE
%token REAL
%token REPEAT
%token RESOURCE
%token RETAIN
%token RETURN
%token R_EDGE
%token SINGLE
%token SINT
%token STEP
%token STRING
%token STRUCT
%token TASK
%token THEN
%token TIME
%token TIME_OF_DAY
%token TO
%token TOD
%token TRANSITION
%token TRUE
%token TYPE
%token UDINT
%token UINT
%token ULINT
%token UNTIL
%token USINT
%token VAR
%token VAR_ACCESS
%token VAR_CONFIG
%token VAR_EXTERNAL
%token VAR_GLOBAL
%token VAR_INPUT
%token VAR_IN_OUT
%token VAR_OUTPUT
%token VAR_TEMP
%token WHILE
%token WITH
%token WORD
%token WSTRING
%token XOR

%token PERCENT COLON SEMICOLON NUM LPAR RPAR LSQUAREB RSQUAREB DOT DDOT COMMA DEF PLUS MINUS STAR SSTAR MOVE_TO

%token SCANNER_ERROR

%token <std::string>    IDENTIFIER

    // B.1.2.1 Numeric literals
%type  <ast::value_wrapper<long>>               numeric_literal
%type  <ast::value_wrapper<long>>               integer_literal
%type  <ast::value_wrapper<long>>               integer_literal_value
%type  <ast::value_wrapper<long>>               signed_integer
%token <long>                                   INTEGER
%token <long>                                   BINARY_INTEGER
%token <long>                                   OCTAL_INTEGER
%token <long>                                   HEX_INTEGER
%type  <ast::value_wrapper<double>>             real_literal
%type  <ast::value_wrapper<long>>               exponent
%type  <ast::value_wrapper<long>>               bit_string_literal
%type  <ast::value_wrapper<long>>               bit_string_literal_value
%type  <ast::value_wrapper<bool>>               boolean_literal
%type  <ast::value_wrapper<bool>>               boolean_literal_value

    // B.1.2.2 Character strings
%token <std::string>        SINGLE_BYTE_CHARACTER_STRING
%token <std::string>        DOUBLE_BYTE_CHARACTER_STRING
%type  <ast::value_wrapper<std::string>>        character_string

%token <double>         MANTISSA

    // B.1.2.3 Time literals
%type  <double>                              time_literal

    // B.1.2.3.1 Duration
%type  <double>               duration
%type  <double>               interval
%type  <double>               days
%token <double>               FIXED_POINT
%type  <double>               hours
%type  <double>               minutes
%type  <double>               seconds
%type  <double>               milliseconds

    // B.1.2.3.2 Time of day and date
%type  <ast::time_of_day>     time_of_day
%type  <ast::daytime>         daytime
%type  <long>                 day_hour
%type  <long>                 day_minute
%type  <long>                 day_second

%type  <ast::date_literal>         date
%type  <ast::date_literal>         date_literal
%type  <long>                 year
%type  <long>                 month
%type  <long>                 day

%type  <ast::date_and_time>     date_and_time


    // B.1.3 Data types

%type  <ast::value_wrapper<ast::elementary_type_name>>  data_type_name
%type  <ast::non_generic_type_name>  non_generic_type_name

    // B.1.3.1 Elementary data types
%type  <ast::elementary_type_name>  elementary_type_name
%type  <ast::elementary_type_name>  numeric_type_name
%type  <ast::elementary_type_name>  integer_type_name
%type  <ast::elementary_type_name>  signed_integer_type_name
%type  <ast::elementary_type_name>  unsigned_integer_type_name
%type  <ast::elementary_type_name>  real_type_name
%type  <ast::elementary_type_name>  date_type_name
%type  <ast::elementary_type_name>  bit_string_type_name


    // B.1.3.2 GENERIC data types

%type  <ast::generic_type_name>     generic_type_name

    // B.1.3.3 GENERIC data types

%type  <std::string>        derived_type_name
%type  <ast::string_type_declaration>           string_type_declaration

%start file
%%
