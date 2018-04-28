#line 1 "11-13.yy"
    // -----------------------------------------------------------------------
    // B.1 Common elements
    // -----------------------------------------------------------------------

    // -----------------------------------------------------------------------
    // B.1.1 TODO place name here
    // -----------------------------------------------------------------------

    // -----------------------------------------------------------------------
    // B.1.2 Constants
    // -----------------------------------------------------------------------

constant
    : numeric_literal
    | character_string
    | time_literal
    | bit_string_literal
    | boolean_literal
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
    : PLUS INTEGER      { $$.value = $2; }
    | MINUS INTEGER     { $2 = -($2); $$.value = $2; }
    ;

real_literal
    : MANTISSA exponent { $$.value = std::pow($1, $2.value); }
    | FIXED_POINT exponent { $$.value = std::pow($1, $2.value); }
    | real_type_name "#" MANTISSA exponent { $$.value = std::pow($3, $4.value); }
    | real_type_name "#" FIXED_POINT exponent { $$.value = std::pow($3, $4.value); }
    ;

exponent
    : E PLUS INTEGER    { $$.value = $3; }
    | E MINUS INTEGER   { $3 = -($3);  $$.value = $3; }
    | E INTEGER         { $$.value = $2; }
    ;

bit_string_literal
    : bit_string_type_name "#" bit_string_literal_value { $$.value = $3.value; }
    ;

bit_string_literal_value
    : INTEGER           { $$.vlaue = $1; }
    | BINARY_INTEGER    { $$.vlaue = $1; }
    | OCTAL_INTEGER     { $$.vlaue = $1; }
    | HEX_INTEGER       { $$.vlaue = $1; }
    ;


boolean_literal
    : BOOL "#" boolean_literal_value    { $$.value = $3.value; }
    | boolean_literal_value             { $$.value = $1.value; }
    ;

boolean_literal_value
    : "0"               { $$.value = false; }
    | "1"               { $$.value = true; }
    | "TRUE"            { $$.value = true; }
    | "FALSE"           { $$.value = false; }
	;

    // -----------------------------------------------------------------------
    // B.1.2.2 Character strings
    // -----------------------------------------------------------------------

character_string
    : SINGLE_BYTE_CHARACTER_STRING
    | DOUBLE_BYTE_CHARACTER_STRING
    ;

    // -----------------------------------------------------------------------
    // B.1.2.3 Time literals
    // -----------------------------------------------------------------------

time_literal
    : duration
    | time_of_day
    | date
    | date_and_time
    ;


    // -----------------------------------------------------------------------
    // B.1.2.3.1 Duration
    // -----------------------------------------------------------------------

    // TODO time_type_name
duration
    : "T" "#" MINUS interval
    | "TIME" "#" MINUS interval
    | "T" "#" interval
    | "TIME" "#" interval
    ;

interval
    : days
    | hours
    | minutes
    | seconds
    | milliseconds
    ;

days
    : FIXED_POINT "d"
    | INTEGER "d" "_" hours
    | INTEGER "d" hours
    ;

hours
    : FIXED_POINT "h"
    | INTEGER "h" "_" minutes
    | INTEGER "h" minutes
    ;

minutes
    : FIXED_POINT "m"
    | INTEGER "m" seconds
    | INTEGER "m" "_" seconds
    ;

seconds
    : FIXED_POINT "s"
    | INTEGER "s" milliseconds
    | INTEGER "s" "_" milliseconds
    ;

milliseconds
    : FIXED_POINT "ms"
    ;

    // -----------------------------------------------------------------------
    // B.1.2.3.2 Time of day and date
    // -----------------------------------------------------------------------

time_of_day
    : TIME_OF_DAY "#" daytime
    | TOD "#" daytime
    ;

daytime: day_hour COLON day_minute COLON day_second;

day_hour: INTEGER;
day_minute: INTEGER;
day_second: FIXED_POINT;

date
    : DATE "#" date_literal
    | D "#" date_literal;

date_literal: year MINUS month MINUS day;

year: INTEGER;
month: INTEGER;
day: INTEGER;

date_and_time
    : DATE_AND_TIME "#" date_literal MINUS daytime
    | DT "#" date_literal MINUS daytime
    ;

    // -----------------------------------------------------------------------
    // B.1.3 Data types
    // -----------------------------------------------------------------------

data_type_name
    : non_generic_type_name { $$ = $1; }
    | generic_type_name     { $$ = $1; }
    ;

non_generic_type_name
    : elementary_type_name  { $$ = $1; }
    //    | derived_type_name
    ;

    // -----------------------------------------------------------------------
    // B.1.3.1 Elementary data types
    // -----------------------------------------------------------------------

elementary_type_name
    : numeric_type_name     { $$ = $1; }
    | date_type_name        { $$ = $1; }
    | bit_string_type_name  { $$ = $1; }
    | "STRING"              { $$ = ast::elementary_type_name::STRING; }
    | "WSTRING"             { $$ = ast::elementary_type_name::WSTRING; }
    | "TIME"                { $$ = ast::elementary_type_name::TIME; }
    ;

numeric_type_name
    : integer_type_name { $$ = $1; }
    | real_type_name    { $$ = $1; }
    ;

integer_type_name
    : signed_integer_type_name      { $$ = $1; }
    | unsigned_integer_type_name    { $$ = $1; }
    ;

signed_integer_type_name
    : SINT              { $$ = ast::elementary_type_name::SINT; }
    | INT               { $$ = ast::elementary_type_name::INT; }
    | DINT              { $$ = ast::elementary_type_name::DINT; }
    | LINT              { $$ = ast::elementary_type_name::LINT; }
    ;

unsigned_integer_type_name
    : USINT             { $$ = ast::elementary_type_name::USINT; }
    | UINT              { $$ = ast::elementary_type_name::UINT; }
    | UDINT             { $$ = ast::elementary_type_name::UDINT; }
    | ULINT             { $$ = ast::elementary_type_name::ULINT; }
    ;

real_type_name
    : REAL              { $$ = ast::elementary_type_name::REAL; }
    | LREAL             { $$ = ast::elementary_type_name::LREAL; }
    ;

date_type_name
    : DATE              { $$ = ast::elementary_type_name::DATE; }
    | TIME_OF_DAY       { $$ = ast::elementary_type_name::TOD; }
    | TOD               { $$ = ast::elementary_type_name::TOD; }
    | DATE_AND_TIME     { $$ = ast::elementary_type_name::DT; }
    | DT                { $$ = ast::elementary_type_name::DT; }
    ;

bit_string_type_name
    : BYTE              { $$ = ast::elementary_type_name::BYTE; }
    | WORD              { $$ = ast::elementary_type_name::WORD; }
    | DWORD             { $$ = ast::elementary_type_name::DWORD; }
    | LWORD             { $$ = ast::elementary_type_name::LWORD; }
    ;

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

derived_type_name: IDENTIFIER;
    //    : single_element_type_name
    //    | array_type_name
    //    | structure_type_name
    //    | string_type_name
    //    ;

    //single_element_type_name: IDENTIFIER;
    //    : simple_type_name
    //    | subrange_type_name
    //    | enumerated_type_name
    //    ;

    // simple_type_name:       IDENTIFIER;
    // subrange_type_name:     IDENTIFIER;
    // enumerated_type_name:   IDENTIFIER;
    // array_type_name:        IDENTIFIER;
    // structure_type_name:    IDENTIFIER;

data_type_declaration: TYPE type_declaration SEMICOLON type_declaration__declarations END_TYPE;

type_declaration__declarations
    : type_declaration__declarations type_declaration SEMICOLON
    |
    ;

// type_declaration: IDENTIFIER COLON type_declaration__decls;

//type_declaration__decls           <<-- parser is not correct, but no errors
//    : simple_spec_init
//    | subrange_spec_init
//    | enumerated_spec_init
//    | array_spec_init
//    | structure_specification
//    | "STRING"
//    | "WSTRING"
//    | IDENTIFIER
//    ;

type_declaration
    : single_element_type_declaration
    | array_type_declaration
    | structure_type_declaration
    | string_type_declaration
    | IDENTIFIER
    ;

single_element_type_declaration
    : simple_type_declaration
    | subrange_type_declaration
    | enumerated_type_declaration
    ;

simple_type_declaration: IDENTIFIER COLON simple_spec_init;

simple_spec_init
    : simple_specification DEF constant
    | simple_specification
    ;

simple_specification
   : elementary_type_name
//   | IDENTIFIER
   ;

subrange_type_declaration: IDENTIFIER COLON subrange_spec_init;

subrange_spec_init
    : subrange_specification DEF signed_integer
    | subrange_specification
    ;

subrange_specification
    : integer_type_name "(" subrange ")"
//    | IDENTIFIER
    ;

// extension due to MANTISSA scan
subrange
    : signed_integer ".." signed_integer
    | INTEGER ".." INTEGER
    | signed_integer ".." INTEGER
    | INTEGER ".." signed_integer
    ;

enumerated_type_declaration: IDENTIFIER COLON enumerated_spec_init;

enumerated_spec_init
    : enumerated_specification
    | enumerated_specification DEF enumerated_value
    ;

enumerated_specification
    : "(" enumerated_value enumerated_specification__values ")";
//    | IDENTIFIER
    ;

enumerated_specification__values
    : enumerated_specification__values "," enumerated_value
    |
    ;

enumerated_value
    : IDENTIFIER "#" IDENTIFIER
//    | IDENTIFIER
    ;

array_type_declaration: IDENTIFIER COLON array_spec_init;

array_spec_init
    : array_specification
    | array_specification DEF array_initialization
    ;

array_specification
    : "ARRAY" "[" subrange array_specification__subranges "]" "OF" non_generic_type_name
//    | IDENTIFIER
    ;

array_specification__subranges
    : array_specification__subranges "," subrange
    |
    ;

array_initialization: "[" array_initial_elements array_initialization__elements "]";

array_initialization__elements
    : array_initialization__elements "," array_initial_elements
    |
    ;

array_initial_elements
    : array_initial_element
    | INTEGER "(" ")"
    | INTEGER "(" array_initial_element ")"
    ;

array_initial_element
    : constant
    | enumerated_value
    | structure_initialization
    | array_initialization
    ;

structure_type_declaration: IDENTIFIER COLON structure_specification;

structure_specification
    : structure_declaration
    | initialized_structure
    ;

initialized_structure
    : IDENTIFIER DEF structure_initialization
//    | IDENTIFIER
    ;

structure_declaration:
    STRUCT
        structure_element_declaration SEMICOLON structure_element_declaration__declarations
    END_STRUCT
    ;

structure_element_declaration__declarations
    : structure_element_declaration__declarations structure_element_declaration SEMICOLON
    |
    ;

structure_element_declaration
    : IDENTIFIER DEF simple_spec_init
    | IDENTIFIER DEF subrange_spec_init
    | IDENTIFIER DEF enumerated_spec_init
    | IDENTIFIER DEF array_spec_init
    | IDENTIFIER DEF initialized_structure
    ;

structure_element_name: IDENTIFIER;

structure_initialization: "(" structure_element_initialization structure_element_initialization__list ")";

structure_element_initialization__list
    : structure_element_initialization__list "," structure_element_initialization
    |
    ;

structure_element_initialization
    : structure_element_name DEF constant
    | structure_element_name DEF enumerated_value
    | structure_element_name DEF array_initialization
    | structure_element_name DEF structure_initialization
    ;

string_type_name: IDENTIFIER;

string_type_declaration
    : "STRING"
    | "STRING" "[" INTEGER "]"
    | "STRING" DEF character_string
    | "STRING" "[" INTEGER "]" DEF character_string
    | "WSTRING"
    | "WSTRING" "[" INTEGER "]"
    | "WSTRING" DEF character_string
    | "WSTRING" "[" INTEGER "]" DEF character_string
