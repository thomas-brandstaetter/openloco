#line 1 "13.yy"
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
    : BOOL              { $$ = ast::elementary_type_name::BOOL; }
    | BYTE              { $$ = ast::elementary_type_name::BYTE; }
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

derived_type_name: IDENTIFIER { $$ = $1;};

simple_type_name: IDENTIFIER;
subrange_type_name: IDENTIFIER;
enumerated_type_name: IDENTIFIER;
array_type_name: IDENTIFIER;
structure_type_name: IDENTIFIER;

data_type_declaration
    : TYPE type_declaration SEMICOLON type_declaration__declarations END_TYPE {
    }
    ;

type_declaration__declarations
    : type_declaration__declarations type_declaration SEMICOLON
    |
    ;

type_declaration
    : single_element_type_declaration {
    }
    | array_type_declaration {
    }
    | structure_type_declaration {
    }
    | string_type_declaration {
    }
    | IDENTIFIER {
    }
    ;

single_element_type_declaration
    : simple_type_declaration {
    }
    | subrange_type_declaration {
    }
    | enumerated_type_declaration {
    }
    ;

simple_type_declaration
    : IDENTIFIER COLON simple_spec_init
    ;

simple_spec_init
    : simple_specification DEF constant
    | simple_specification
    ;

simple_specification
   : elementary_type_name
   | simple_type_name
   ;

subrange_type_declaration: IDENTIFIER COLON subrange_spec_init;

subrange_spec_init
    : subrange_specification DEF signed_integer
    | subrange_specification
    ;

subrange_specification
    : integer_type_name LPAR subrange RPAR
    | subrange_type_name
    ;

subrange
    : signed_integer DDOT signed_integer
    | INTEGER DDOT INTEGER
    | signed_integer DDOT INTEGER
    | INTEGER DDOT signed_integer
    ;

enumerated_type_declaration
    : IDENTIFIER COLON enumerated_spec_init {
    }
    ;

enumerated_spec_init
    : enumerated_specification DEF enumerated_value {
    }
    | enumerated_specification
    ;

enumerated_specification
    : LPAR enumerated_value enumerated_specification__values RPAR
    ;

enumerated_specification__values
    : enumerated_specification__values COMMA enumerated_value
    |
    ;

enumerated_value
    : IDENTIFIER NUM IDENTIFIER
    | IDENTIFIER
    ;

array_type_declaration
    : IDENTIFIER COLON array_spec_init{
    }
    ;

array_spec_init
    : array_specification
    | array_specification DEF array_initialization
    ;

array_specification
    : ARRAY LSQUAREB subrange array_specification__subranges RSQUAREB OF non_generic_type_name
    ;

array_specification__subranges
    : array_specification__subranges COMMA subrange
    |
    ;

array_initialization: LSQUAREB array_initial_elements array_initialization__elements RSQUAREB;

array_initialization__elements
    : array_initialization__elements COMMA array_initial_elements
    |
    ;

array_initial_elements
    : array_initial_element
    | INTEGER LPAR RPAR
    | INTEGER LPAR array_initial_element RPAR
    ;

array_initial_element
    : constant
    | enumerated_value
    | structure_initialization
    | array_initialization
    ;

structure_type_declaration
    : IDENTIFIER COLON structure_specification {
    }
    ;

structure_specification
    : structure_declaration
    | initialized_structure
    ;

initialized_structure
    : IDENTIFIER DEF structure_initialization
    ;

structure_declaration:
    STRUCT structure_element_declaration SEMICOLON structure_element_declaration__declarations END_STRUCT {
    }
    ;

structure_element_declaration__declarations
    : structure_element_declaration__declarations structure_element_declaration SEMICOLON
    |
    ;

structure_element_declaration
    : IDENTIFIER COLON simple_spec_init
    | IDENTIFIER COLON subrange_spec_init
    | IDENTIFIER COLON enumerated_spec_init
    | IDENTIFIER COLON array_spec_init
    | IDENTIFIER COLON initialized_structure
    ;

structure_element_name: IDENTIFIER;

structure_initialization
    : LPAR structure_element_initialization structure_element_initialization__list RPAR
    ;

structure_element_initialization__list
    : structure_element_initialization__list COMMA structure_element_initialization
    |
    ;

structure_element_initialization
    : structure_element_name DEF constant
    | structure_element_name DEF enumerated_value
    | structure_element_name DEF array_initialization
    | structure_element_name DEF structure_initialization
    ;

string_type_declaration
    : IDENTIFIER COLON STRING  {
        $$.type = ast::elementary_type_name::STRING;
    }
    | IDENTIFIER COLON STRING LSQUAREB INTEGER RSQUAREB {
        $$.type = ast::elementary_type_name::STRING;
        $$.size = $5;
    }
    | IDENTIFIER COLON STRING DEF character_string {
        $$.type = ast::elementary_type_name::STRING;
        $$.value = $5.value;
    }
    | IDENTIFIER COLON STRING LSQUAREB INTEGER RSQUAREB DEF character_string {
        $$.type = ast::elementary_type_name::STRING;
        $$.size = $5;
        $$.value = $8.value;
    }
    | IDENTIFIER COLON WSTRING {
        $$.type = ast::elementary_type_name::STRING;
    }
    | IDENTIFIER COLON WSTRING LSQUAREB INTEGER RSQUAREB {
        $$.type = ast::elementary_type_name::STRING;
        $$.size = $5;
    }
    | IDENTIFIER COLON WSTRING DEF character_string{
        $$.type = ast::elementary_type_name::STRING;
        $$.value = $5.value;
    }
    | IDENTIFIER COLON WSTRING LSQUAREB INTEGER RSQUAREB DEF character_string{
        $$.type = ast::elementary_type_name::WSTRING;
        $$.size = $5;
        $$.value = $8.value;
    }
    ;
