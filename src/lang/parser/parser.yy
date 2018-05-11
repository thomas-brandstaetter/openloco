%skeleton "lalr1.cc"
%require  "3.0.4"

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
%expect 11
%expect-rr 15

%param {openloco::lang::driver &driver}
%parse-param {openloco::lang::scanner &scanner}

%code requires {
    #include <ast/ast.h>
    #include <variant>

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
    #include <algorithm>

    #include <driver/driver.h>
    #include <scanner/scanner.h>

    #include <parser.hh>
    #include <location.hh>

    #undef yylex
    #define yylex scanner.yylex
%}


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

%token <std::string>                            IDENTIFIER

    // B.1.2 Constants

%type  <ast::constant>                          constant

    // B.1.2.1 Numeric literals
%type  <ast::numeric_literal>                   numeric_literal
%type  <ast::integer_literal>                   integer_literal
%type  <ast::value_wrapper<long>>               integer_literal_value
%type  <long>               signed_integer
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
%type  <std::string>        character_string

%token <double>         MANTISSA

    // B.1.2.3 Time literals
%type  <ast::time_literal>  time_literal

    // B.1.2.3.1 Duration
%type  <double>             duration
%type  <double>             interval
%type  <double>             days
%token <double>             FIXED_POINT
%type  <double>             hours
%type  <double>             minutes
%type  <double>             seconds
%type  <double>             milliseconds

    // B.1.2.3.2 Time of day and date
%type  <ast::time_of_day>   time_of_day
%type  <ast::daytime>       daytime
%type  <long>               day_hour
%type  <long>               day_minute
%type  <long>               day_second

%type  <ast::date_literal>  date
%type  <ast::date_literal>  date_literal
%type  <long>               year
%type  <long>               month
%type  <long>               day

%type  <ast::date_and_time>     date_and_time


    // B.1.3 Data types

%type  <ast::elementary_type_name>      data_type_name
%type  <std::variant<ast::elementary_type_name, std::string>>     non_generic_type_name

    // B.1.3.1 Elementary data types
%type  <ast::elementary_type_name>      elementary_type_name
%type  <ast::numeric_type_name>         numeric_type_name
%type  <ast::integer_type_name>         integer_type_name
%type  <ast::signed_integer_type_name>  signed_integer_type_name
%type  <ast::unsigned_integer_type_name>    unsigned_integer_type_name
%type  <ast::real_type_name>            real_type_name
%type  <ast::date_type_name>            date_type_name
%type  <ast::bit_string_type_name>      bit_string_type_name


    // B.1.3.2 GENERIC data types

%type  <ast::generic_type_name>     generic_type_name

    // B.1.3.3 GENERIC data types

%type  <std::string>            derived_type_name

%type  <std::string>            simple_type_name
%type  <std::string>            subrange_type_name
%type  <std::string>            enumerated_type_name
%type  <std::string>            array_type_name
%type  <std::string>            structure_type_name

%type  <std::vector<ast::type_declaration>>     data_type_declaration
%type  <std::vector<ast::type_declaration>>     dtd__declarations
%type  <ast::type_declaration>      type_declaration

%type  <ast::single_element_type_declaration> single_element_type_declaration

%type  <ast::simple_type_declaration>                   simple_type_declaration
%type  <ast::simple_type_declaration::spec_init>        simple_spec_init
%type  <std::variant<ast::elementary_type_name, std::string>>                     simple_specification

%type  <ast::subrange_type_declaration> subrange_type_declaration
%type  <ast::subrange_type_declaration::spec_init>        subrange_spec_init
%type  <ast::subrange_specification>    subrange_specification
%type  <ast::subrange>                  subrange


%type  <ast::enumerated_type_declaration>   enumerated_type_declaration
%type  <ast::enumerated_type_declaration::spec_init>        enumerated_spec_init
%type  <ast::enumerated_specification>      enumerated_specification
%type  <std::vector<ast::enumerated_value>>      es__values
%type  <ast::enumerated_value>              enumerated_value

%type  <ast::array_type_declaration>        array_type_declaration
%type  <ast::array_initialization>          array_initialization
%type  <std::vector<ast::array_initial_elements>>     ai__elements
%type  <ast::array_specification>           array_specification
%type  <ast::array_type_declaration::spec_init> array_spec_init
%type  <ast::array_initial_element>         array_initial_element
%type  <ast::array_initial_elements>        array_initial_elements

%type  <std::vector<ast::subrange>>         as__subranges

%type  <ast::structure_type_declaration>    structure_type_declaration
%type  <ast::structure_initialization>      structure_initialization
%type  <std::string>                        structure_element_name

%type  <ast::structure_element_initialization::element_initialization>    sei__value

%type  <ast::string_type_declaration>       string_type_declaration
%type  <long>                               std__size
%type  <std::string>                        std__init


%start file
%%


file
    : library_element_name END { YYACCEPT; }
    | library_element_declaration END { YYACCEPT; }
    ;

    // -----------------------------------------------------------------------
    // B.0 Programming model
    // -----------------------------------------------------------------------

library_element_name: IDENTIFIER;

library_element_declaration
    : data_type_declaration {
        ast::root root = static_cast<ast::root>($1);
        driver.set_root(root);
    }
    | function_declaration
    | function_block_declaration
    | program_declaration
    | configuration_declaration
    ;



    // -----------------------------------------------------------------------
    // B.1.2 Constants
    // -----------------------------------------------------------------------
constant
    : numeric_literal           { $$ = $1; }
    | character_string          { $$ = $1; }
    | time_literal              { $$ = $1; }
    | bit_string_literal        { $$ = $1.value; }
    | boolean_literal           { $$ = $1; }
    ;

    // -----------------------------------------------------------------------
    // B.1.2.1 Numeric literals
    // -----------------------------------------------------------------------
numeric_literal
    : integer_literal   { $$.value = $1.value; }
    | real_literal      { $$.value = $1.value; }
    ;

integer_literal
    : integer_type_name integer_literal_value   { $$.value = $2.value; }
    | integer_literal_value                     { $$.value = $1.value; }
    ;

integer_literal_value
    : signed_integer    { $$ = $1; }
    | INTEGER           { $$.value = $1; }
    | BINARY_INTEGER    { $$.value = $1; }
    | OCTAL_INTEGER     { $$.value = $1; }
    | HEX_INTEGER       { $$.value = $1; }
    ;

signed_integer
    : PLUS INTEGER      { $$ = $2; }
    | MINUS INTEGER     { $$ = -($2); }
    ;

real_literal
    : MANTISSA exponent { $$.value = std::pow($1, $2.value); }
    | FIXED_POINT exponent { $$.value = std::pow($1, $2.value); }
    | real_type_name NUM MANTISSA exponent { $$.value = std::pow($3, $4.value); }
    | real_type_name NUM FIXED_POINT exponent { $$.value = std::pow($3, $4.value); }
    ;

exponent
    : E signed_integer  { $$.value = $2; }
    |                   { $$.value = 1; }
    ;

bit_string_literal
    : bit_string_type_name NUM bit_string_literal_value { $$.value = $3.value; }
    ;

bit_string_literal_value
    : INTEGER           { $$.value = $1; }
    | BINARY_INTEGER    { $$.value = $1; }
    | OCTAL_INTEGER     { $$.value = $1; }
    | HEX_INTEGER       { $$.value = $1; }
    ;


boolean_literal
    : BOOL NUM boolean_literal_value    { $$.value = $3.value; }
    | boolean_literal_value             { $$.value = $1.value; }
    ;

boolean_literal_value
    : "0"               { $$.value = false; }
    | "1"               { $$.value = true; }
    | TRUE              { $$.value = true; }
    | FALSE             { $$.value = false; }
	;

    // -----------------------------------------------------------------------
    // B.1.2.2 Character strings
    // -----------------------------------------------------------------------
character_string
    : SINGLE_BYTE_CHARACTER_STRING { $$ = $1; }
    | DOUBLE_BYTE_CHARACTER_STRING { $$ = $1; }
    ;

    // -----------------------------------------------------------------------
    // B.1.2.3 Time literals
    // -----------------------------------------------------------------------

time_literal
    : duration          { }
    | time_of_day       { }
    | date              { }
    | date_and_time     { }
    ;

    // -----------------------------------------------------------------------
    // B.1.2.3.1 Duration
    // -----------------------------------------------------------------------

    // TODO time_type_name
duration
    : "T" NUM MINUS interval    { $4 = -$4; $$ = $4; }
    | "TIME" NUM MINUS interval { $4 = -$4; $$ = $4; }
    | "T" NUM interval          { $$ = $3; }
    | "TIME" NUM interval       { $$ = $3; }
    ;

interval
    : days              { $$ = driver.dc.days_in_ms($1); }
    | hours             { $$ = driver.dc.hours_in_ms($1); }
    | minutes           { $$ = driver.dc.minutes_in_ms($1); }
    | seconds           { $$ = driver.dc.seconds_in_ms($1); }
    | milliseconds      { $$ = $1; }
    ;

days
    : FIXED_POINT "d"           { $$ = driver.dc.days_in_ms($1); }
    | INTEGER "d" "_" hours     {
        $$ = driver.dc.days_in_ms($1);
        $$ += driver.dc.hours_in_ms($4);
    }
    | INTEGER "d" hours         {
        $$ = driver.dc.days_in_ms($1);
        $$ += driver.dc.hours_in_ms($3);
    }
    ;

hours
    : FIXED_POINT "h"           { $$ = driver.dc.hours_in_ms($1); }
    | INTEGER "h" "_" minutes   {
        $$  = driver.dc.hours_in_ms($1);;
        $$ += driver.dc.minutes_in_ms($4);;
    }
    | INTEGER "h" minutes {
        $$  = driver.dc.hours_in_ms($1);;
        $$ += driver.dc.minutes_in_ms($3);;
    }
    ;

minutes
    : FIXED_POINT "m"           { $$ = driver.dc.minutes_in_ms($1); }
    | INTEGER "m" seconds       {
        $$ += driver.dc.minutes_in_ms($1);
        $$ += driver.dc.seconds_in_ms($3);
    }
    | INTEGER "m" "_" seconds   {
        $$ += driver.dc.minutes_in_ms($1);
        $$ += driver.dc.seconds_in_ms($4);
    }
    ;

seconds
    : FIXED_POINT "s"           { $$ = driver.dc.seconds_in_ms($1); }
    | INTEGER "s" milliseconds  { $$ += driver.dc.seconds_in_ms($1); $$ += $3; }
    | INTEGER "s" "_" milliseconds { $$ += driver.dc.seconds_in_ms($1); $$ += $4; }
    ;

milliseconds
    : FIXED_POINT "ms"          { $$ = $1; }
    ;

    // -----------------------------------------------------------------------
    // B.1.2.3.2 Time of day and date
    // -----------------------------------------------------------------------
time_of_day
    : TIME_OF_DAY NUM daytime   { $$ = $3; }
    | TOD NUM daytime           { $$ = $3; }
    ;

daytime: day_hour COLON day_minute COLON day_second {
        $$.hour = $1;
        $$.minute = $3;
        $$.second = $5;
    }
    ;

day_hour: INTEGER       { $$ = $1; };
day_minute: INTEGER     { $$ = $1; };
day_second: FIXED_POINT { $$ = $1; };

date
    : DATE NUM date_literal { std::swap($$, $3); }
    | D NUM date_literal    { std::swap($$, $3); }
    ;

date_literal: year MINUS month MINUS day {
        $$.year = $1;
        $$.month = $3;
        $$.day = $5;
    }
    ;

year: INTEGER           { $$ = $1; };
month: INTEGER          { $$ = $1; };
day: INTEGER            { $$ = $1; };

date_and_time
    : DATE_AND_TIME NUM date_literal MINUS daytime {
        $$.date = $3;
        $$.time = $5;
    }
    | DT NUM date_literal MINUS daytime {
        $$.date = $3;
        $$.time = $5;
    }
    ;



    // -----------------------------------------------------------------------
    // B.1.3 Data types
    // -----------------------------------------------------------------------
data_type_name
    : non_generic_type_name { }
    | generic_type_name     { $$ = $1; }
    ;

non_generic_type_name
    : elementary_type_name  {
        // $$ = $1
    }
    | derived_type_name     {
        // $$ = $1;
    }
    ;

    // -----------------------------------------------------------------------
    // B.1.3.1 Elementary data types
    // -----------------------------------------------------------------------

elementary_type_name
    : numeric_type_name     { $$ = static_cast<ast::elementary_type_name>($1); }
    | date_type_name        { $$ = static_cast<ast::elementary_type_name>($1); }
    | bit_string_type_name  { $$ = static_cast<ast::elementary_type_name>($1); }
    | "STRING"              { $$ = ast::elementary_type_name::STRING; }
    | "WSTRING"             { $$ = ast::elementary_type_name::WSTRING; }
    | "TIME"                { $$ = ast::elementary_type_name::TIME; }
    ;

numeric_type_name
    : integer_type_name { $$ = static_cast<ast::numeric_type_name>($1); }
    | real_type_name    { $$ = static_cast<ast::numeric_type_name>($1); }
    ;

integer_type_name
    : signed_integer_type_name      { $$ = static_cast<ast::integer_type_name>($1); }
    | unsigned_integer_type_name    { $$ = static_cast<ast::integer_type_name>($1); }
    ;

signed_integer_type_name
    : SINT              { $$ = ast::signed_integer_type_name::SINT; }
    | INT               { $$ = ast::signed_integer_type_name::INT; }
    | DINT              { $$ = ast::signed_integer_type_name::DINT; }
    | LINT              { $$ = ast::signed_integer_type_name::LINT; }
    ;

unsigned_integer_type_name
    : USINT             { $$ = ast::unsigned_integer_type_name::USINT; }
    | UINT              { $$ = ast::unsigned_integer_type_name::UINT; }
    | UDINT             { $$ = ast::unsigned_integer_type_name::UDINT; }
    | ULINT             { $$ = ast::unsigned_integer_type_name::ULINT; }
    ;

real_type_name
    : REAL              { $$ = ast::real_type_name::REAL; }
    | LREAL             { $$ = ast::real_type_name::LREAL; }
    ;

date_type_name
    : DATE              { $$ = ast::date_type_name::DATE; }
    | TIME_OF_DAY       { $$ = ast::date_type_name::TIME_OF_DAY; }
    | TOD               { $$ = ast::date_type_name::TIME_OF_DAY; }
    | DATE_AND_TIME     { $$ = ast::date_type_name::DATE_AND_TIME; }
    | DT                { $$ = ast::date_type_name::DATE_AND_TIME; }
    ;

bit_string_type_name
    : BOOL              { $$ = ast::bit_string_type_name::BOOL; }
    | BYTE              { $$ = ast::bit_string_type_name::BYTE; }
    | WORD              { $$ = ast::bit_string_type_name::WORD; }
    | DWORD             { $$ = ast::bit_string_type_name::DWORD; }
    | LWORD             { $$ = ast::bit_string_type_name::LWORD; }
    ;

string_type_name: IDENTIFIER;

    // -----------------------------------------------------------------------
    // B.1.3.2 Generic data types
    // -----------------------------------------------------------------------
generic_type_name
    : ANY               { $$ = ast::generic_type_name::ANY; }
    | ANY_DERIVED       { $$ = ast::generic_type_name::ANY_DERIVED; }
    | ANY_ELEMENTARY    { $$ = ast::generic_type_name::ANY_ELEMENTARY; }
    | ANY_MAGNITUDE     { $$ = ast::generic_type_name::ANY_MAGNITUDE; }
    | ANY_NUM           { $$ = ast::generic_type_name::ANY_NUM; }
    | ANY_REAL          { $$ = ast::generic_type_name::ANY_REAL; }
    | ANY_INT           { $$ = ast::generic_type_name::ANY_INT; }
    | ANY_BIT           { $$ = ast::generic_type_name::ANY_BIT; }
    | ANY_STRING        { $$ = ast::generic_type_name::ANY_STRING; }
    | ANY_DATE          { $$ = ast::generic_type_name::ANY_DATE; }
    ;


    // derived_type_name : IDENTIFIER;


    // -----------------------------------------------------------------------
    // B.1.3.3 Derived data types
    // -----------------------------------------------------------------------

derived_type_name:      IDENTIFIER { $$ = $1; };

simple_type_name:       IDENTIFIER { $$ = $1; };
subrange_type_name:     IDENTIFIER { $$ = $1; };
enumerated_type_name:   IDENTIFIER { $$ = $1; };
array_type_name:        IDENTIFIER { $$ = $1; };
structure_type_name:    IDENTIFIER { $$ = $1; };

data_type_declaration
    : TYPE dtd__declarations END_TYPE { std::swap($$, $2); }
    ;

dtd__declarations
    : dtd__declarations type_declaration SEMICOLON {
        $$.push_back($2);
        std::swap($$, $1);
    }
    | type_declaration SEMICOLON {
        $$.push_back($1);
    }
    ;

type_declaration
    : single_element_type_declaration   { $$ = $1; }
    | array_type_declaration            { $$ = $1; }
    | structure_type_declaration        { $$ = $1; }
    | string_type_declaration           { $$ = $1; }
    ;

single_element_type_declaration
    : simple_type_declaration           { $$ = $1; }
    | subrange_type_declaration         { $$ = $1; }
    | enumerated_type_declaration       { $$ = $1; }
    ;

simple_type_declaration
    : simple_type_name COLON simple_spec_init {
        $$.type_name = $1;
        $$.set_spec_init($3);
    }
    ;

simple_spec_init
    : simple_specification DEF constant {
        $$.specification = $1;
        $$.value = $3;
    }
    | simple_specification {
        $$.specification = $1;
    }
    ;

simple_specification
   : elementary_type_name       { $$ = $1; }
   | simple_type_name           { $$ = $1; }
   ;

subrange_type_declaration
    : subrange_type_name COLON subrange_spec_init {
        $$.type_name = $1;
        $$.set_spec_init($3);
    }
    ;

subrange_spec_init
    : subrange_specification DEF signed_integer {
        $$.specification = $1;
        $$.value = $3;
    }
    | subrange_specification {
        $$.specification = $1;
    }
    ;

subrange_specification
    : integer_type_name LPAR subrange RPAR {
        ast::ss_specification sss;
        sss.type_name = $1;
        sss.value = $3;
        $$ = sss;
    }
    | subrange_type_name { $$ = $1; }
    ;

subrange
    : signed_integer DDOT signed_integer {
        $$.min = $1;
        $$.max = $3;
    }
    ;

enumerated_type_declaration
    : enumerated_type_name COLON enumerated_spec_init {
        $$.type_name = $1;
        $$.set_spec_init($3);
    }
    ;

enumerated_spec_init
    : enumerated_specification DEF enumerated_value {
        $$.specification = $1;
        $$.value = $3;
    }
    | enumerated_specification {
        $$.specification = $1;
    }
    ;

enumerated_specification
    : LPAR enumerated_value es__values RPAR {
        $3.insert($3.begin(), $2);
        $$ = $3;
    }
    | enumerated_type_name {
        $$ = $1;
    }
    ;

es__values
    : es__values COMMA enumerated_value {
        $1.push_back($3);
        std::swap($$, $1);
    }
    | {}
    ;

enumerated_value
    : enumerated_type_name NUM IDENTIFIER {
        $$.type_name = $1;
        $$.value = $3;
    }
    | IDENTIFIER {
        $$.type_name = $1;
    }
    ;

array_type_declaration
    : array_type_name COLON array_spec_init {
        $$.type_name = $1;
        $$.set_spec_init($3);
    }
    ;

array_spec_init
    : array_specification
    | array_specification DEF array_initialization
    ;

array_specification
    : ARRAY LSQUAREB subrange as__subranges RSQUAREB OF non_generic_type_name {
        $$.type_name = $7;
        $$.dimension.push_back($3);
        $$.dimension.insert($$.dimension.end(), $4.begin(), $4.end());
    }
    ;

as__subranges
    : as__subranges COMMA subrange {
        $1.push_back($3);
        std::swap($$, $1);
    }
    |
    ;

array_initialization
    : LSQUAREB array_initial_elements ai__elements RSQUAREB {
        $$.elements.push_back($2);
        $$.elements.insert($$.elements.end(), $3.begin(), $3.end());
    }
    ;

ai__elements
    : ai__elements COMMA array_initial_elements {
        $1.push_back($3);
        std::swap($$, $1);
    }
    |
    ;

array_initial_elements
    : array_initial_element
    | INTEGER LPAR RPAR
    | INTEGER LPAR array_initial_element RPAR
    ;

array_initial_element
    : constant                      { $$ = $1; }
    | enumerated_value              { $$ = $1; }
    | structure_initialization      { $$ = $1; }
    | array_initialization          { $$ = $1; }
    ;

structure_type_declaration
    : structure_type_name COLON structure_specification {
    }
    ;

structure_specification
    : structure_declaration
    | initialized_structure
    ;

initialized_structure
    : structure_type_name DEF structure_initialization
    ;

structure_declaration:
    STRUCT sed__declarations END_STRUCT {
    }
    ;

sed__declarations
    : sed__declarations structure_element_declaration SEMICOLON
    | structure_element_declaration SEMICOLON
    ;

structure_element_declaration
    : IDENTIFIER COLON sed__spec_init
    ;

sed__spec_init
    : simple_spec_init
    | subrange_spec_init
    | enumerated_spec_init
    | array_spec_init
    | initialized_structure
    ;

structure_element_name: IDENTIFIER  { $$ = $1; };

structure_initialization
    : LPAR structure_element_initialization si__initializations RPAR
    ;

si__initializations
    : si__initializations COMMA structure_element_initialization
    |
    ;

structure_element_initialization
    : structure_element_name DEF sei__value;

sei__value
    : constant                      { $$ = $1; }
    | enumerated_value              { $$ = $1; }
    | array_initialization          { $$ = $1; }
    | structure_initialization      { $$ = $1; }
    ;

string_type_declaration
    : string_type_name COLON STRING std__size std__init {
        $$.type_name = ast::elementary_type_name::STRING;
        $$.size = $4;
        $$.value = $5;
    }
    | string_type_name COLON WSTRING std__size std__init {
        $$.type_name = ast::elementary_type_name::WSTRING;
        $$.size = $4;
        $$.value = $5;
    }
    ;

std__size
    : LSQUAREB INTEGER RSQUAREB     { $$ = $2; }
    |                               { $$ = -1; }
    ;

std__init
    : DEF character_string          { $$ = $2; }
    |                               { $$ = ""; }
    ;

    // -----------------------------------------------------------------------
    // B.1.4. Variables
    // -----------------------------------------------------------------------

variable
    : direct_variable
    | symbolic_variable
    ;

symbolic_variable
    : variable_name
    | multi_element_variable
    ;

variable_name: IDENTIFIER;

    // -----------------------------------------------------------------------
    // B.1.4.1 Directly represented variables
    // -----------------------------------------------------------------------

direct_variable: PERCENT location_prefix size_prefix INTEGER directive_variable__positions;

directive_variable__positions
    : DOT INTEGER directive_variable__positions
    |
    ;

location_prefix
    : "I"
    | "Q"
    | "M"
    ;

size_prefix
    :
    | "X"
    | "B"
    | "W"
    | "D"
    | "L"
    ;


    // -----------------------------------------------------------------------
    // B.1.4.2 Multi-element variables
    // -----------------------------------------------------------------------

multi_element_variable
    : array_variable
    | structured_variable
    ;

array_variable: subscripted_variable subscript_list;

subscripted_variable: symbolic_variable;

subscript_list: LSQUAREB subscript sl__subscripts RSQUAREB;

sl__subscripts
    : sl__subscripts "," subscript
    |
    ;


subscript: IDENTIFIER;

structured_variable: record_variable DOT field_selector;

record_variable: symbolic_variable;

field_selector: IDENTIFIER;


    // -----------------------------------------------------------------------
    // B.1.4.3 Declaration and initialization
    // -----------------------------------------------------------------------

input_declarations
    : VAR_INPUT RETAIN input_declaration SEMICOLON ids__declarations END_VAR
    | VAR_INPUT NON_RETAIN input_declaration SEMICOLON ids__declarations END_VAR
    | VAR_INPUT input_declaration SEMICOLON ids__declarations END_VAR;


ids__declarations
    : ids__declarations input_declaration SEMICOLON
    |
    ;

input_declaration
    : var_init_decl
    | edge_declaration
    ;

edge_declaration
    : var1_list COLON BOOL ed__edge
    ;

ed__edge
    : R_EDGE
    | F_EDGE
    |
    ;

var_init_decl
    : var1_init_decl
    | array_var_init_decl
    | structured_var_init_decl
    | fb_name_decl
    | string_var_declaration
    ;

var1_init_decl
    : var1_list COLON simple_spec_init
    | var1_list COLON subrange_spec_init
    | var1_list COLON enumerated_spec_init;

var1_list: IDENTIFIER v1l__identifiers;

v1l__identifiers
    : v1l__identifiers "," IDENTIFIER
    |
    ;

array_var_init_decl
    : var1_list COLON array_spec_init
    ;

structured_var_init_decl
    : var1_list COLON initialized_structure
    ;

fb_name_decl
    : fb_name_list COLON IDENTIFIER
    | fb_name_list COLON IDENTIFIER DEF structure_initialization
    ;


fb_name_list: fb_name fnl__names;

fnl__names
    :  fnl__names COMMA fb_name
    |
    ;

fb_name: IDENTIFIER;

output_declarations
    : VAR_OUTPUT RETAIN var_init_decl SEMICOLON  output_declarations__init_decls END_VAR
    | VAR_OUTPUT NON_RETAIN var_init_decl SEMICOLON  output_declarations__init_decls END_VAR
    | VAR_OUTPUT var_init_decl SEMICOLON  output_declarations__init_decls END_VAR
    ;

output_declarations__init_decls
    : output_declarations__init_decls var_init_decl SEMICOLON
    |
    ;

input_output_declarations: "VAR_IN_OUT" var_declaration SEMICOLON input_output_declarations__declarations END_VAR;

input_output_declarations__declarations
    : input_output_declarations__declarations var_declaration SEMICOLON
    |
    ;

var_declaration
    : temp_var_decl
    | fb_name_decl
    ;

    // TODO
temp_var_decl
    : var1_declaration
    | array_var_declaration
    | structured_var_declaration
    | string_var_declaration
    ;

var1_declaration
    : var1_list COLON IDENTIFIER
    | var1_list COLON subrange_specification
    | var1_list COLON enumerated_specification;

array_var_declaration: var1_list COLON array_specification;

structured_var_declaration: var1_list COLON IDENTIFIER;

var_declarations: VAR CONSTANT vd__declarations END_VAR;

vd__declarations
    : vd__declarations var_init_decl SEMICOLON
    | var_init_decl SEMICOLON
    ;

retentive_var_declarations: VAR RETAIN rvd__declarations END_VAR;

rvd__declarations
    : rvd__declarations var_init_decl SEMICOLON
    | var_init_decl SEMICOLON
    ;

located_var_declarations
    : VAR lvd__retain lvd__declarations END_VAR
    ;

lvd__retain
    : CONSTANT
    | RETAIN
    | NON_RETAIN
    |
    ;

lvd__declarations
    : lvd__declarations located_var_decl SEMICOLON
    | located_var_decl SEMICOLON
    ;

located_var_decl
    : IDENTIFIER location COLON located_var_spec_init
    | location COLON located_var_spec_init;

external_var_declarations
    : VAR_EXTERNAL evd__retain evd__declarations END_VAR

evd__retain
    : CONSTANT
    |
    ;

evd__declarations
    : evd__declarations external_declaration SEMICOLON
    | external_declaration SEMICOLON
    ;

    // TODO function_block_type_name
external_declaration
    : global_var_name COLON IDENTIFIER
    | global_var_name COLON subrange_specification
    | global_var_name COLON enumerated_specification
    | global_var_name COLON array_specification
    | global_var_name COLON structure_type_name
    // | global_var_name COLON IDENTIFIER;
    ;

global_var_name: IDENTIFIER;

global_var_declarations
    : VAR_GLOBAL gvds__retain global_var_decl SEMICOLON gvds__declarations END_VAR
    ;

gvds__retain
    : RETAIN
    | CONSTANT
    |
    ;

gvds__declarations
   : gvds__declarations global_var_decl SEMICOLON
   | global_var_decl SEMICOLON
   ;

    // TODO: function_block_type_name
global_var_decl
    : global_var_spec COLON located_var_spec_init
    | global_var_spec COLON IDENTIFIER
    ;

global_var_spec
    : global_var_list
    | location
    | global_var_name location
    ;

located_var_spec_init
    : simple_spec_init
    | subrange_spec_init
    | enumerated_spec_init
    | array_spec_init
    | initialized_structure
    | single_byte_string_spec
    | double_byte_string_spec
    ;

location: AT direct_variable

global_var_list: global_var_name global_var_list__names;

global_var_list__names
    : global_var_list__names "," global_var_name
    |
    ;

string_var_declaration
    : single_byte_string_var_declaration
    | double_byte_string_var_declaration
    ;

single_byte_string_var_declaration: var1_list COLON single_byte_string_spec;

single_byte_string_spec
    : STRING LSQUAREB INTEGER RSQUAREB
    | STRING DEF DOUBLE_BYTE_CHARACTER_STRING
    | STRING LSQUAREB INTEGER RSQUAREB DEF DOUBLE_BYTE_CHARACTER_STRING
    ;

double_byte_string_var_declaration: var1_list COLON double_byte_string_spec;

double_byte_string_spec
    : WSTRING LSQUAREB INTEGER RSQUAREB
    | WSTRING DEF DOUBLE_BYTE_CHARACTER_STRING
    | WSTRING LSQUAREB INTEGER RSQUAREB DEF DOUBLE_BYTE_CHARACTER_STRING
    ;

incompl_located_var_declarations
    : VAR RETAIN incompl_located_var_decl SEMICOLON incompl_located_var_decl END_VAR
    | VAR NON_RETAIN incompl_located_var_decl SEMICOLON incompl_located_var_decl END_VAR
    | VAR incompl_located_var_decl SEMICOLON incompl_located_var_decl END_VAR
    ;


incompl_located_var_decl
    : IDENTIFIER incompl_location COLON var_spec
    ;

incompl_location
    : AT PERCENT "I" STAR
    | AT PERCENT "M" STAR
    | AT PERCENT "Q" STAR
    ;

var_spec
    : IDENTIFIER
    | subrange_specification
    | enumerated_specification
    | array_specification
    | STRING LSQUAREB INTEGER RSQUAREB
    | WSTRING LSQUAREB INTEGER RSQUAREB
    | STRING
    | WSTRING
    ;

    // -----------------------------------------------------------------------
    // B.1.5 Program organization units
    // -----------------------------------------------------------------------

    // -----------------------------------------------------------------------
    // B.1.5.1 Functions
    // -----------------------------------------------------------------------

function_name
    : standard_function_name
    | derived_function_name
    ;

    // Defined in 2.5.1.5
    // 2.5.1.5.1 Type conversion functions
    // 2.5.1.5.2 Numerical functions
    // 2.5.1.5.3 Bit string functions
    // 2.5.1.5.4 Selection and comparison functions
    // 2.5.1.5.5 Character string functions
    // 2.5.1.5.6 Functions of time data types
    // 2.5.1.5.7 Functions of enumerated data types
standard_function_name
    : "*_TO_*"
    | "TRUNC"
    | "*_BCD_TO_*"
    | "*_TO_BCD_*"

    | "ABS"
    | "SQRT"
    | "LN"
    | "LOG"
    | "EXP"
    | "SIN"
    | "COS"
    | "TAN"
    | "ASIN"
    | "ACOS"
    | "ATAN"
    | "ADD"
    | "MUL"
    | "SUB"
    | "DIV"
    | "MOD"
    | "EXPT"
    | "MOVE"

    | "SHL"
    | "SHR"
    | "ROR"
    | "ROL"

    | "SEL"
    | "MAX"
    | "MIN"
    | "LIMIT"
    | "MUX"
    | "AND"
    | "OR"
    | "XOR"
    | "NOT"
    | "GT"
    | "GE"
    | "EQ"
    | "LE"
    | "LT"
    | "NE"

    | "LEN"
    | "LEFT"
    | "RIGHT"
    | "MID"
    | "CONCAT"
    | "INSERT"
    | "DELETE"
    | "REPLACE"
    | "FIND"

    | "ADD_TIME"
    | "ADD_TOD_TIME"
    | "ADD_DT_TIME"
    | "SUB_TIME"
    | "SUB_DATE_DATE"
    | "SUB_TOD_TIME"
    | "SUB_TOD_TOD"
    | "SUB_DT_TIME"
    | "SUB_DT_DT"
    | "MULTIME"
    | "DIVTIME"
    | "CONCAT_DATE_TOD"
    | "DT_TO_TOD"
    | "DT_TO_DATE"

    ;
derived_function_name: IDENTIFIER;


//function_declaration: FUNCTION derived_function_name COLON IDENTIFIER function_declaration__declarations function_body END_FUNCTION


function_declaration
    : FUNCTION derived_function_name COLON elementary_type_name function_declaration__declarations function_body END_FUNCTION
    | FUNCTION derived_function_name COLON derived_type_name function_declaration__declarations function_body END_FUNCTION;

function_declaration__declarations
    : function_declaration__declarations io_var_declarations
    | function_declaration__declarations function_var_decls
    |
    ;

io_var_declarations
    : input_declarations
    | output_declarations
    | input_output_declarations
    ;

function_var_decls
    : VAR CONSTANT var2_init_decl SEMICOLON function_var_decls__declarations END_VAR
    | VAR var2_init_decl SEMICOLON function_var_decls__declarations END_VAR;

function_var_decls__declarations
    : function_var_decls__declarations var2_init_decl SEMICOLON
    |
    ;

    // TODO
function_body: "FUNCTION_BODY_PLACEHOLDER"
    //    : instruction_list
    //  | statement_list
    ;

var2_init_decl
    : var1_init_decl
    | array_var_init_decl
    | structured_var_init_decl
    | string_var_declaration
    ;

    // -----------------------------------------------------------------------
    // B.1.5.2 Function blocks
    // -----------------------------------------------------------------------

function_block_type_name
    : standard_function_block_name
    | derived_function_block_name
    ;

    // Defined in 2.5.2.3
    // 2.5.2.3.1 Bistable elements
    // 2.5.2.3.2 Edge detection
    // 2.5.2.3.3 Counters
    // 2.5.2.3.4 Timers
    // 2.5.2.3.5 Communication function blocks      <<--- TODO
standard_function_block_name
    : "SR"
    | "RS"

    | "R_TRIG"
    | "F_TRIG"

    | "CTU"
    | "CTU_DINT"
    | "CTU_LINT"
    | "CTU_UDINT"
    | "CTU_ULINT"
    | "CTD"
    | "CTD_DINT"
    | "CTD_LINT"
    | "CTD_UDINT"
    | "CTD_ULINT"
    | "CTUD"
    | "CTUD_LINT"
    | "CTUD_ULINT"

    | "TP"
    | "TON"
    | "T---Q"
    | "TOF"
    | "Q---T"

derived_function_block_name: IDENTIFIER;

function_block_declaration: "FUNCTION_BLOCK" derived_function_block_name function_block_declaration__variables function_block_body "END_FUNCTION_BLOCK";

function_block_declaration__variables
    : function_block_declaration__variables io_var_declarations
    | function_block_declaration__variables function_var_decls
    |
    ;

other_var_declarations
    : external_var_declarations
    | var_declarations
    | retentive_var_declarations
    | non_retentive_var_declarations
    | temp_var_decls
    | incompl_located_var_declarations
    ;

temp_var_decls: "VAR_TEMP" temp_var_decl SEMICOLON temp_var_decls__declarations END_VAR;

temp_var_decls__declarations
    : temp_var_decls__declarations temp_var_decl SEMICOLON
    |
    ;

non_retentive_var_declarations: VAR NON_RETAIN  var_init_decl SEMICOLON non_retentive_var_declarations__declarations END_VAR;

non_retentive_var_declarations__declarations
    : non_retentive_var_declarations__declarations var_init_decl SEMICOLON
    |
    ;

    // TODO
function_block_body: "FUNCTION_BLOCK_PLACEHOLDER"
    //: sequential_function_chart
    //| ladder_diagram
    //| function_block_diagram
    //| instruction_list
    //| statement_list
    ;


    // -----------------------------------------------------------------------
    // B.1.5.3 Programs
    // -----------------------------------------------------------------------

program_type_name
    : IDENTIFIER
    ;

program_declaration:
    PROGRAM IDENTIFIER
        pd__declarations
        function_block_body
    END_PROGRAM
    ;

pd__declarations
    : pd__declarations program_declaration_var
    |
    ;

program_declaration_var
    : io_var_declarations
    | other_var_declarations
    | located_var_declarations
    | program_access_decls
    ;

program_access_decls:
     VAR_ACCESS program_access_decl SEMICOLON
        pad__declarations
     END_VAR
     ;

pad__declarations
    : pad__declarations program_access_decl SEMICOLON
    |
    ;

program_access_decl
    : IDENTIFIER COLON symbolic_variable COLON non_generic_type_name program_access_decl_direction
    ;

program_access_decl_direction
    : direction
    |
    ;

    // -----------------------------------------------------------------------
    // B.1.7 Configuration elements
    // -----------------------------------------------------------------------

configuration_name
    : IDENTIFIER
    ;

resource_type_name
    : IDENTIFIER
    ;

configuration_declaration
    : CONFIGURATION configuration_name
        cg__global_var_declarations
        cg__resource_declaration
        cg__access_declarations
        cg__instance_specific_initializations
      END_CONFIGURATION
    ;


cg__global_var_declarations
    : global_var_declarations
    |
    ;

cg__resource_declaration
    : single_resource_declaration
    | cgrd__resource_declarations

cgrd__resource_declarations
    : cgrd__resource_declarations resource_declaration
    | resource_declaration
    ;

cg__access_declarations
    : access_declarations
    |
    ;

cg__instance_specific_initializations
    : instance_specific_initializations
    |
    ;


resource_declaration
    : RESOURCE resource_name ON resource_type_name
        rd__global_var_declarations
        single_resource_declaration
      END_RESOURCE
    ;

rd__global_var_declarations
    : global_var_declarations
    |
    ;

single_resource_declaration
    : srd__task_configuration srd__program_configurations
    ;

srd__task_configuration
    : task_configuration
    |
    ;

srd__program_configurations
    : srd__program_configurations program_configuration
    | program_configuration
    ;

resource_name
    : IDENTIFIER
    ;

access_declarations
    : VAR_ACCESS
        ad__access_declaration
      END_VAR

ad__access_declaration
    : ad__access_declaration access_declaration
    | access_declaration
    ;

access_declaration
    : access_name COLON access_path COLON non_generic_type_name ad__direction
    ;

ad__direction
    : direction
    |
    ;

access_path
    : ap__resource_name direct_variable
    | ap__resource_name ap__program_name ap__fb_names symbolic_variable
    ;


ap__resource_name
    : resource_name
    |
    ;

ap__program_name
    : program_name
    |
    ;

ap__fb_names
    : ap__fb_names fb_name DOT
    |
    ;

global_var_reference
    : gvr__resource_name global_var_name gvr__structure_element_name
    ;

gvr__resource_name
    : resource_name DOT
    |
    ;

gvr__structure_element_name
    : DOT structure_element_name
    |
    ;


access_name: IDENTIFIER;

program_output_reference
    : program_name DOT symbolic_variable

program_name: IDENTIFIER;

direction
    : "READ_WRITE"
    | "READ_ONLY"
    ;

task_configuration: TASK task_name task_initialization;

task_name: IDENTIFIER

    // TODO: simplify

task_initialization
    : LPAR ti__single ti__interval PRIORITY DEF INTEGER LPAR
    ;

ti__single
    : SINGLE DEF data_source COMMA
    |
    ;

ti__interval
    : INTERVAL DEF data_source COMMA
    |
    ;

data_source
    : constant
    | global_var_reference
    | program_output_reference
    | direct_variable
    ;

program_configuration
    : PROGRAM pc_retain program_name pc_task_name COLON program_type_name pc_conf_elements
    ;

pc_retain
    : RETAIN
    | NON_RETAIN
    |
    ;

pc_task_name
    : WITH task_name
    |
    ;

pc_conf_elements
    : LPAR prog_conf_elements RPAR

prog_conf_elements
    : prog_conf_element pce_elements;

pce_elements
    : pce_elements COMMA prog_conf_element
    |
    ;

prog_conf_element
    : fb_task
    | prog_cnxn
    ;

fb_task
    : fb_name WITH task_name
    ;

prog_cnxn
    : symbolic_variable DEF prog_data_source
    | symbolic_variable MOVE_TO data_sink

prog_data_source
    : constant
    | enumerated_value
    | global_var_reference
    | direct_variable
    ;

data_sink
    : global_var_reference
    | direct_variable
    ;

    // instance_specific_initializations ::= 'VAR_CONFIG'
    //            instance_specific_init ';'
    //            {instance_specific_init ';'}
    //          'END_VAR'

instance_specific_initializations
    : VAR_CONFIG isis__inits END_VAR

isis__inits
    : isis__inits instance_specific_init SEMICOLON
    | instance_specific_init SEMICOLON
    ;

    // instance_specific_init ::=
    //   resource_name '.' program_name '.' {fb_name '.'} ((variable_name [location] ':' located_var_spec_init) |
    //   (fb_name ':' function_block_type_name ':=' structure_initialization))

instance_specific_init
    : resource_name DOT program_name DOT isi__fb_names isi__init
    ;

isi__fb_names
    : isi__fb_names fb_name DOT
    |
    ;

isi__init
    : variable_name COLON located_var_spec_init
    | variable_name location COLON located_var_spec_init
    | fb_name COLON function_block_type_name DEF structure_initialization
    ;



%%

void
openloco::lang::parser::error(const location_type &loc, const std::string& message) {
    std::cerr
        << "parser error at "
        << loc
        << ": " << message << std::endl;
    std::cerr << std::flush;

    exit(1);
}


