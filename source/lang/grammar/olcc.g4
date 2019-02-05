
grammar olcc;


    /*  C.2 Keywords */

/*
ACTION                    : 'ACTION' ;
AND                       : 'AND' ;
ANY                       : 'ANY' ;
ANY_BIT                   : 'ANY_BIT' ;
ANY_DATE                  : 'ANY_DATE' ;
ANY_DERIVED               : 'ANY_DERIVED' ;
ANY_ELEMENTARY            : 'ANY_ELEMENTARY' ;
ANY_INT                   : 'ANY_INT' ;
ANY_MAGNITUDE             : 'ANY_MAGNITUDE' ;
ANY_NUM                   : 'ANY_NUM' ;
ANY_REAL                  : 'ANY_REAL' ;
ANY_STRING                : 'ANY_STRING' ;
ARRAY                     : 'ARRAY' ;
AT                        : 'AT' ;
BOOL                      : 'BOOL' ;
BY                        : 'BY' ;
BYTE                      : 'BYTE' ;
CASE                      : 'CASE' ;
CONFIGURATION             : 'CONFIGURATION' ;
CONSTANT                  : 'CONSTANT' ;
D                         : 'D' ;
DATE                      : 'DATE' ;
DATE_AND_TIME             : 'DATE_AND_TIME' ;
DINT                      : 'DINT' ;
DO                        : 'DO' ;
DT                        : 'DT' ;
DWORD                     : 'DWORD' ;
E                         : 'E' ;
ELSE                      : 'ELSE' ;
ELSIF                     : 'ELSIF' ;
EN                        : 'EN' ;
END_ACTION                : 'END_ACTION' ;
END_CASE                  : 'END_CASE' ;
END_CONFIGURATION         : 'END_CONFIGURATION ' ;
END_FOR                   : 'END_FOR' ;
END_FUNCTION              : 'END_FUNCTION' ;
END_FUNCTION_BLOCK        : 'END_FUNCTION_BLOCK' ;
END_IF                    : 'END_IF' ;
END_PROGRAM               : 'END_PROGRAM' ;
END_REPEAT                : 'END_REPEAT' ;
END_RESOURCE              : 'END_RESOURCE' ;
END_STEP                  : 'END_STEP' ;
END_STRUCT                : 'END_STRUCT' ;
END_TRANSITION            : 'END_TRANSITION' ;
END_TYPE                  : 'END_TYPE' ;
END_VAR                   : 'END_VAR' ;
END_WHILE                 : 'END_WHILE' ;
ENO                       : 'ENO' ;
EXIT                      : 'EXIT' ;
FALSE                     : 'FALSE' ;
FOR                       : 'FOR' ;
FROM                      : 'FROM' ;
FUNCTION                  : 'FUNCTION' ;
FUNCTION_BLOCK            : 'FUNCTION_BLOCK' ;
F_EDGE                    : 'F_EDGE' ;
IF                        : 'IF' ;
INITIAL_STEP              : 'INITIAL_STEP' ;
INT                       : 'INT' ;
INTERVAL                  : 'INTERVAL' ;
LINT                      : 'LINT' ;
LREAL                     : 'LREAL' ;
LWORD                     : 'LWORD' ;
MOD                       : 'MOD' ;
NON_RETAIN                : 'NON_RETAIN' ;
NOT                       : 'NOT' ;
OF                        : 'OF' ;
ON                        : 'ON' ;
OR                        : 'OR' ;
PRIORITY                  : 'PRIORITY' ;
PROGRAM                   : 'PROGRAM' ;
READ_ONLY                 : 'READ_ONLY' ;
READ_WRITE                : 'READ_WRITE' ;
REAL                      : 'REAL' ;
REPEAT                    : 'REPEAT' ;
RESOURCE                  : 'RESOURCE' ;
RETAIN                    : 'RETAIN' ;
RETURN                    : 'RETURN' ;
R_EDGE                    : 'R_EDGE' ;
SINGLE                    : 'SINGLE' ;
SINT                      : 'SINT' ;
STEP                      : 'STEP' ;
STRING                    : 'STRING' ;
STRUCT                    : 'STRUCT' ;
TASK                      : 'TASK' ;
THEN                      : 'THEN' ;
TIME                      : 'TIME' ;
TIME_OF_DAY               : 'TIME_OF_DAY' ;
TO                        : 'TO         ' ;
TOD                       : 'TOD        ' ;
TRANSITION                : 'TRANSITION ' ;
TRUE                      : 'TRUE       ' ;
TYPE                      : 'TYPE       ' ;
UDINT                     : 'UDINT      ' ;
UINT                      : 'UINT       ' ;
ULINT                     : 'ULINT      ' ;
UNTIL                     : 'UNTIL      ' ;
USINT                     : 'USINT      ' ;
VAR                       : 'VAR        ' ;
VAR_ACCESS                : 'VAR_ACCESS ' ;
VAR_CONFIG                : 'VAR_CONFIG ' ;
VAR_EXTERNAL              : 'VAR_EXTERNAL' ;
VAR_GLOBAL                : 'VAR_GLOBAL' ;
VAR_INPUT                 : 'VAR_INPUT' ;
VAR_IN_OUT                : 'VAR_IN_OUT' ;
VAR_OUTPUT                : 'VAR_OUTPUT' ;
VAR_TEMP                  : 'VAR_TEMP' ;
WHILE                     : 'WHILE' ;
WITH                      : 'WITH' ;
WORD                      : 'WORD' ;
WSTRING                   : 'WSTRING' ;
XOR                       : 'XOR' ;
*/






WHITESPACE              : ' \t\r\n'+ -> skip ;

EOL                     : '\n' ;

    /*
     * B.0 Programming model
     */

library_element_name    : data_type_name
                        | function_name
                        | function_block_type_name
                        | program_type_name
                        | resource_type_name
                        | configuration_name
                        ;

library_element_declaration
                        : data_type_declaration
                        | function_declaration
                        | function_block_declaration
                        | program_declaration
                        | configuration_declaration
                        ;


    /*
     * B.1 Common elements
     */


    /* B.1.1 Letters, digits and identifiers */

LETTER                  : 'A'..'Z' | 'a'..'z' ;
DIGIT                   : '0'..'9' ;
HEX_DIGIT               : DIGIT | 'A'..'F' ;
OCTAL_DIGIT             : [0-7] ;
identifier              : (LETTER | ('_' (LETTER | DIGIT))) (('_') (LETTER | DIGIT))* ;


    /* B.1.2 Constants */

constant                : numeric_literal
                        | character_string
                        | time_literal
                        | bit_string_literal
                        | boolean_literal
                        ;

numeric_literal         : integer_literal
                        | real_literal
                        ;

integer_literal         : (integer_type_name '#')? (signed_integer | binary_integer | octal_integer | hex_integer);
signed_integer          : ('+' | '-')? integer ;
integer                 : DIGIT ('_'? DIGIT)* ;

binary_integer          : '2#' bit ('_'? bit)* ;
bit                     : '1' | '0' ;
octal_integer           : '8#' OCTAL_DIGIT ('_'? OCTAL_DIGIT)* ;
hex_integer             : '16#' HEX_DIGIT ('_'? HEX_DIGIT)* ;

real_literal            : (real_type_name '#')? signed_integer '.' integer exponent? ;
exponent                : ('E' | 'e') ('+' | '-')? integer ;

bit_string_literal      : (('BYTE' | 'WORD' | 'DWORD' | 'LWORD') '#')? (integer | binary_integer | octal_integer | hex_integer) ;

boolean_literal         : (('BOOL#')? ('1'|'0')) | 'TRUE' | 'FALSE' ;


character_string        : single_byte_character_string
                        | double_byte_character_string
                        ;

single_byte_character_string: '\'' {single_byte_character_representation} '\'' ;
double_byte_character_string: '"' {double_byte_character_representation} '"' ;

single_byte_character_representation
                        : common_character_representation
                        | '$\''
                        | '"'
                        | '$' HEX_DIGIT HEX_DIGIT
                        ;

double_byte_character_representation
                        : common_character_representation
                        | '$"'
                        | '\''
                        | '$' HEX_DIGIT HEX_DIGIT HEX_DIGIT HEX_DIGIT
                        ;

    /* TODO */
common_character_representation:
                        ;


    /* B.1.2.3 Time literals */

time_literal            : duration
                        | time_of_day
                        | date
                        | date_and_time
                        ;

duration                : ('T' | 'TIME') '#' '-'? interval
                        ;

interval                : days
                        | hours
                        | minutes
                        | seconds
                        | milliseconds
                        ;

days                    : fixed_point 'd'
                        | integer 'd' '_'? hours
                        ;

fixed_point             : integer ( '.' integer)?
                        ;

hours                   : fixed_point ('h')
                        | integer 'h' '_'? minutes
                        ;

minutes                 : fixed_point 'm'
                        | integer 'm' '_'? seconds
                        ;

seconds                 : fixed_point 's'
                        | integer 's' '_'? milliseconds
                        ;

milliseconds            : fixed_point 'ms'
                        ;


    /* B.1.2.3.2 Time of day and date */

time_of_day             : ('TIME_OF_DAY' | 'TOD') '#' daytime ;

daytime                 : day_hour ':' day_minute ':' day_second ;

day_hour                : integer ;

day_minute              : integer ;

day_second              : fixed_point ;

date                    : ('DATE' | 'D') '#' date_literal ;

date_literal            : year '-' month '-' day ;

year                    : integer ;

month                   : integer ;

day                     : integer ;

date_and_time           : ('DATE_AND_TIME' | 'DT') '#' date_literal '-' daytime ;



    /* B.1.3 Data types */

data_type_name          : non_generic_type_name
                        | generic_type_name
                        ;

non_generic_type_name   : elementary_type_name
                        | derived_type_name
                        ;

elementary_type_name    : numeric_type_name
                        | date_type_name
                        | bit_string_type_name
                        | 'STRING'
                        | 'WSTRING'
                        | 'TIME'
                        ;

numeric_type_name       : integer_type_name
                        | real_type_name
                        ;

integer_type_name       : signed_integer_type_name
                        | unsigned_integer_type_name
                        ;

signed_integer_type_name: 'SINT'
                        | 'INT'
                        | 'DINT'
                        | 'LINT'
                        ;

unsigned_integer_type_name
                        : 'USINT'
                        | 'UINT'
                        | 'UDINT'
                        | 'ULINT'
                        ;

real_type_name          : 'REAL'
                        | 'LREAL'
                        ;

date_type_name          : 'DATE'
                        | 'TIME_OF_DAY'
                        | 'TOD'
                        | 'DATE_AND_TIME'
                        | 'DT'
                        ;

bit_string_type_name    : 'BOOL'
                        | 'BYTE'
                        | 'WORD'
                        | 'DWORD'
                        | 'LWORD'
                        ;

    // -----------------------------------------------------------------------
    // B.1.3.2 Generic data types
    // -----------------------------------------------------------------------

generic_type_name       : 'ANY'
                        | 'ANY_DERIVED'
                        | 'ANY_ELEMENTARY'
                        | 'ANY_MAGNITUDE'
                        | 'ANY_NUM'
                        | 'ANY_REAL'
                        | 'ANY_INT'
                        | 'ANY_BIT'
                        | 'ANY_STRING'
                        | 'ANY_DATE'
                        ;

    // -----------------------------------------------------------------------
    // B.1.3.3 Derived data types
    // -----------------------------------------------------------------------

derived_type_name       : single_element_type_name
                        | array_type_name
                        | structure_type_name
                        | string_type_name
                        ;

single_element_type_name: simple_type_name
                        | subrange_type_name
                        | enumerated_type_name
                        ;

simple_type_name        : identifier ;

subrange_type_name      : identifier ;

enumerated_type_name    : identifier ;

array_type_name         : identifier ;

structure_type_name     : identifier ;

data_type_declaration   : 'TYPE' (type_declaration ';')+ 'END_TYPE' ;

type_declaration        : single_element_type_declaration
                        | array_type_declaration
                        | structure_type_declaration
                        | string_type_declaration
                        ;

single_element_type_declaration
                        : simple_type_declaration
                        | subrange_type_declaration
                        | enumerated_type_declaration
                        ;

simple_type_declaration : simple_type_name ':' simple_spec_init ;

simple_spec_init        : simple_specification (':=' constant)? ;

simple_specification    : elementary_type_name
                        | simple_type_name
                        ;

subrange_type_declaration: subrange_type_name ':' subrange_spec_init ;

subrange_spec_init      : subrange_specification (':=' signed_integer)? ;

subrange_specification  : integer_type_name '(' subrange')'
                        | subrange_type_name
                        ;

subrange                : signed_integer '..' signed_integer ;

enumerated_type_declaration : enumerated_type_name ':' enumerated_spec_init ;

enumerated_spec_init    : enumerated_specification (':=' enumerated_value)? ;

enumerated_specification: '(' enumerated_value (',' enumerated_value)* ')'
                        | enumerated_type_name
                        ;

enumerated_value        : (enumerated_type_name '#')? identifier ;

array_type_declaration  : array_type_name ':' array_spec_init ;

array_spec_init         : array_specification (':=' array_initialization)? ;

array_specification     : array_type_name
                        | 'ARRAY' '[' subrange (',' subrange)? ']' 'OF' non_generic_type_name
                        ;

array_initialization    : '[' array_initial_elements (',' array_initial_elements)* ']' ;

array_initial_elements  : array_initial_element
                        | integer '(' array_initial_element? ')'
                        ;

array_initial_element   : constant
                        | enumerated_value
                        | structure_initialization
                        | array_initialization
                        ;

structure_type_declaration : structure_type_name ':' structure_specification ;

structure_specification : structure_declaration
                        | initialized_structure
                        ;

initialized_structure   : structure_type_name (':=' structure_initialization)? ;

structure_declaration   : 'STRUCT' (structure_element_declaration ';')+ 'END_STRUCT' ;

structure_element_declaration
                        : structure_element_name ':'
                            ( simple_spec_init
                            | subrange_spec_init
                            | enumerated_spec_init
                            | array_spec_init
                            | initialized_structure)
                        ;

structure_element_name  : identifier ;

structure_initialization: '(' structure_element_initialization (',' structure_element_initialization)* ')' ;

structure_element_initialization
                        : structure_element_name ':='
                            (constant
                            | enumerated_value
                            | array_initialization
                            | structure_initialization)
                        ;

string_type_name        : identifier ;

string_type_declaration : string_type_name ':' ('STRING'|'WSTRING') ('[' integer ']')? (':=' character_string)? ;

    /* B.1.4 Variables */

variable                : direct_variable
                        | symbolic_variable
                        ;

/*symbolic_variable       : variable_name
                        | multi_element_variable
                        ;
*/

symbolic_variable       : variable_name                         #l_variable_name
                        | symbolic_variable subscript_list      #l_array_variable
                        | symbolic_variable '.' field_selector  #l_structured_variable
                        ;

variable_name           : identifier ;

    /* B.1.4.1 Directly represented variables */

direct_variable         : '%' location_prefix size_prefix integer ('.' integer)* ;

location_prefix         : 'I'
                        | 'Q'
                        | 'M'
                        ;

size_prefix             : 'X'
                        | 'B'
                        | 'W'
                        | 'D'
                        | 'L'
                        |
                        ;

    /* B.1.4.2 Multi-element variables */

/*multi_element_variable  : array_variable
                        | structured_variable
                        ;

array_variable          : subscripted_variable subscript_list ;

subscripted_variable    : symbolic_variable ;

*/


subscript_list          : '[' subscript (',' subscript)* ']' ;

subscript               : expression ;
/*
structured_variable     : record_variable '.' field_selector ;

record_variable         : symbolic_variable ;
*/

field_selector          : identifier ;


    /* B.1.4.3 Declaration and initialization */

input_declarations      : 'VAR_INPUT' ('RETAIN' | 'NON_RETAIN')? (input_declaration ';')+ 'END_VAR' ;

input_declaration       : var_init_decl | edge_declaration ;

edge_declaration        : var1_list ':' 'BOOL' ('R_EDGE' | 'F_EDGE') ;

var_init_decl           : var1_init_decl
                        | array_var_init_decl
                        | structured_var_init_decl
                        | fb_name_decl
                        | string_var_declaration
                        ;

var1_init_decl          : var1_list ':' (simple_spec_init | subrange_spec_init | enumerated_spec_init) ;

var1_list               : variable_name (',' variable_name)* ;

array_var_init_decl     : var1_list ':' array_spec_init ;

structured_var_init_decl: var1_list ':' initialized_structure ;

fb_name_decl            : fb_name_list ':' function_block_type_name ( ':=' structure_initialization ) ;

fb_name_list            : fb_name (',' fb_name)* ;

fb_name                 : identifier ;

output_declarations     : 'VAR_OUTPUT' ('RETAIN' | 'NON_RETAIN')? (var_init_decl ';')+ 'END_VAR' ;

input_output_declarations: 'VAR_IN_OUT' (var_declaration ';')+ 'END_VAR' ;

var_declaration         : temp_var_decl
                        | fb_name_decl
                        ;

temp_var_decl           : var1_declaration
                        | array_var_declaration
                        | structured_var_declaration
                        | string_var_declaration
                        ;

var1_declaration        : var1_list ':' (simple_specification | subrange_specification | enumerated_specification) ;

array_var_declaration   : var1_list ':' array_specification ;

structured_var_declaration: var1_list ':' structure_type_name ;

var_declarations        : 'VAR' 'CONSTANT'? (var_init_decl ';')+ 'END_VAR' ;

retentive_var_declarations: 'VAR' 'RETAIN' (var_init_decl ';')+ 'END_VAR' ;

located_var_declarations: 'VAR' ('CONSTANT' | 'RETAIN' | 'NON_RETAIN')? (located_var_decl ';')+ 'END_VAR' ;

located_var_decl        : variable_name? location ':' located_var_spec_init ;

external_var_declarations: 'VAR_EXTERNAL' 'CONSTANT'? (external_declaration ';')+ 'END_VAR' ;

external_declaration    : global_var_name ':'
                          ( simple_specification
                          | subrange_specification
                          | enumerated_specification
                          | array_specification
                          | structure_type_name
                          | function_block_type_name
                          )
                         ;

global_var_name         : identifier ;

global_var_declarations : 'VAR_GLOBAL' ('CONSTANT' | 'RETAIN')? (global_var_decl ';')+ 'END_VAR' ;

global_var_decl         : global_var_spec ':' ( located_var_spec_init | function_block_type_name ) ;

global_var_spec         : global_var_list | global_var_name? location ;

located_var_spec_init   : simple_spec_init
                        | subrange_spec_init
                        | enumerated_spec_init
                        | array_spec_init
                        | initialized_structure
                        | single_byte_string_spec
                        | double_byte_string_spec
                        ;

location                : 'AT' direct_variable ;

global_var_list         : global_var_name (',' global_var_name)* ;

string_var_declaration  : single_byte_string_var_declaration
                        | double_byte_string_var_declaration ;

single_byte_string_var_declaration
                        : var1_list ':' single_byte_string_spec
                        ;

single_byte_string_spec :'STRING' ('[' integer ']')* (':=' single_byte_character_string)? ;

double_byte_string_var_declaration
                        : var1_list ':' double_byte_string_spec
                        ;

double_byte_string_spec : 'WSTRING' ('[' integer ']')? (':=' double_byte_character_string)? ;

incompl_located_var_declarations
                        : 'VAR' ('RETAIN'|'NON_RETAIN')? (incompl_located_var_decl ';')+ 'END_VAR'
                        ;

incompl_located_var_decl: variable_name incompl_location ':' var_spec ;

incompl_location        : 'AT' '%' ('I' | 'Q' | 'M') '*' ;

var_spec                : simple_specification
                        | subrange_specification
                        | enumerated_specification
                        | array_specification
                        | structure_type_name
                        | 'STRING' ('[' integer ']')?
                        | 'WSTRING' ('[' integer ']')?
                        ;

    /* B.1.5 Program organization units */

    /* B.1.5.1 Functions */

function_name           : standard_function_name
                        | derived_function_name
                        ;

standard_function_name  : '<as defined in 2.5.1.5>' ;

derived_function_name   : identifier ;

function_declaration    : 'FUNCTION' derived_function_name ':' (elementary_type_name | derived_type_name)
                            ( io_var_declarations | function_var_decls )? function_body
                          'END_FUNCTION'
                        ;

io_var_declarations     : input_declarations
                        | output_declarations
                        | input_output_declarations
                        ;

function_var_decls      : 'VAR' 'CONSTANT'? (var2_init_decl ';')* 'END_VAR' ;

function_body           : instruction_list
                        |  statement_list
                        /*| ladder_diagram
                        | function_block_diagram
                        | <other languages> */
                        ;

var2_init_decl          : var1_init_decl
                        | array_var_init_decl
                        | structured_var_init_decl
                        | string_var_declaration
                        ;

    /* B.1.5.2 Function blocks */

function_block_type_name: standard_function_block_name
                        | derived_function_block_name
                        ;

standard_function_block_name : '<as defined in 2.5.2.3>' ;

derived_function_block_name: identifier ;

function_block_declaration
                        : 'FUNCTION_BLOCK' derived_function_block_name
                            ( io_var_declarations | other_var_declarations )*
                            function_block_body
                          'END_FUNCTION_BLOCK'
                        ;

other_var_declarations  : external_var_declarations
                        | var_declarations
                        | retentive_var_declarations
                        /*| non_retentive_var_declarations    used but not defined in the standard. */
                        | temp_var_decls
                        | incompl_located_var_declarations
                        ;

temp_var_decls          : 'VAR_TEMP' (temp_var_decl ';')* 'END_VAR' ;

non_retentive_var_decls : 'VAR' 'NON_RETAIN' (var_init_decl ';')+ 'END_VAR' ;

function_block_body     : sequential_function_chart
                        /*| ladder_diagram
                        | function_block_diagram */
                        | instruction_list
                        | statement_list
                        /*| <other languages> */
                        ;

    /* B.1.5.3 Programs */

program_type_name       : identifier ;

program_declaration     : 'PROGRAM' program_type_name
                            ( io_var_declarations
                            | other_var_declarations
                            | located_var_declarations
                            | program_access_decls
                            )*
                            function_block_body
                          'END_PROGRAM'
                          ;

program_access_decls    : 'VAR_ACCESS' (program_access_decl ';')* 'END_VAR' ;

program_access_decl     : access_name ':' symbolic_variable ':' non_generic_type_name direction? ;



    /* B.1.6 Sequential function chart elements */


sequential_function_chart: sfc_network+ ;

sfc_network             : initial_step (step | transition | action)* ;

initial_step            : 'INITIAL_STEP' step_name ':' (action_association ';')* 'END_STEP' ;

step                    : 'STEP' step_name ':' (action_association ';')* 'END_STEP' ;

step_name               : identifier ;

action_association      : action_name '(' action_qualifier? (',' indicator_name)* ')' ;

action_name             : identifier ;

action_qualifier        : 'N'
                        | 'R'
                        | 'S'
                        | 'P'
                        | timed_qualifier ',' action_time
                        ;

timed_qualifier         : 'L'
                        | 'D'
                        | 'SD'
                        | 'DS'
                        | 'SL'
                        ;

action_time             : duration
                        | variable_name
                        ;

indicator_name          : variable_name ;

transition              : 'TRANSITION' transition_name? ('(' 'PRIORITY' ':=' integer ')')? 'FROM' steps 'TO' steps
                            transition_condition
                          'END_TRANSITION'
                        ;

transition_name         : identifier ;

steps                   : step_name
                        | '(' step_name ',' step_name (',' step_name)* ')'
                        ;

transition_condition    : ':' /* simple_instruction_list */ instruction_list
                        | ':=' expression ';'
                        /*| ':' (fbd_network | rung) */
                        ;

action                  : 'ACTION' action_name ':' function_block_body 'END_ACTION' ;


    /* B.1.7 Configuration elements */

configuration_name      : identifier ;
resource_type_name      : identifier ;

configuration_declaration
                        : 'CONFIGURATION' configuration_name global_var_declarations?
                            ( single_resource_declaration | resource_declaration+ )
                            access_declarations?
                            instance_specific_initializations?
                          'END_CONFIGURATION'
                        ;

resource_declaration    : 'RESOURCE' resource_name 'ON' resource_type_name
                            global_var_declarations? single_resource_declaration
                          'END_RESOURCE'
                        ;

single_resource_declaration:
                       (task_configuration ';')*  program_configuration ';' (program_configuration ';')* ;

resource_name           : identifier ;

access_declarations     : 'VAR_ACCESS' (access_declaration ';')* 'END_VAR';

access_declaration      : access_name ':' access_path ':' non_generic_type_name direction? ;

access_path             : (resource_name '.')? direct_variable
                        | (resource_name '.')? (program_name '.')? (fb_name'.')* symbolic_variable
                        ;

global_var_reference    : (resource_name '.')? global_var_name ('.' structure_element_name)? ;

access_name             : identifier ;

program_output_reference: program_name '.' symbolic_variable ;

program_name            : identifier ;

direction               : 'READ_WRITE' | 'READ_ONLY' ;

task_configuration      : 'TASK' task_name task_initialization ;

task_name               : identifier ;

task_initialization     : '(' ('SINGLE' ':=' data_source ',')? ('INTERVAL' ':=' data_source ',')? 'PRIORITY' ':=' integer ')' ;

data_source             : constant
                        | global_var_reference
                        | program_output_reference
                        | direct_variable
                        ;

program_configuration   : 'PROGRAM' ('RETAIN' | 'NON_RETAIN')? program_name ('WITH' task_name)? ':' program_type_name ('(' prog_conf_elements ')')? ;

prog_conf_elements      : prog_conf_element (',' prog_conf_element)* ;

prog_conf_element       : fb_task | prog_cnxn ;

fb_task                 : fb_name 'WITH' task_name ;

prog_cnxn               : symbolic_variable ':=' prog_data_source
                        | symbolic_variable '=>' data_sink
                        ;

prog_data_source        : constant
                        | enumerated_value
                        | global_var_reference
                        | direct_variable
                        ;

data_sink               : global_var_reference
                        | direct_variable
                        ;

instance_specific_initializations
                        : 'VAR_CONFIG' (instance_specific_init ';')* 'END_VAR'
                        ;

instance_specific_init  : resource_name '.' program_name '.' (fb_name '.')*
                        ( variable_name location? ':' located_var_spec_init
                        | fb_name ':' function_block_type_name ':=' structure_initialization
                        )
                        ;

    /* B.2 Language IL (Instruction List) */
    /* B.2.1 Instructions and operands */

instruction_list        : il_instruction+ ;

il_instruction          : (label':')?
                          ( il_simple_operation
                          | il_expression
                          | il_jump_operation
                          | il_fb_call
                          | il_formal_funct_call
                          | il_return_operator
                          )
                          EOL+
                          ;

label                   : identifier ;

il_simple_operation     : il_simple_operator il_operand?
                        | function_name il_operand_list?
                        ;

il_expression           : il_expr_operator '(' il_operand? EOL+ simple_instr_list? ')' ;

il_jump_operation       : il_jump_operator label ;

il_fb_call              : il_call_operator fb_name ('(' (EOL+  il_param_list? ) | il_operand_list? ')')? ;

il_formal_funct_call    : function_name '(' EOL+ il_param_list? ')' ;

il_operand              : constant | variable | enumerated_value ;

il_operand_list         : il_operand (',' il_operand)* ;

simple_instr_list       : il_simple_instruction+ ;

il_simple_instruction   : (il_simple_operation | il_expression | il_formal_funct_call) EOL+ ;

il_param_list           : il_param_instruction* il_param_last_instruction ;

il_param_instruction    : (il_param_assignment | il_param_out_assignment) ',' EOL+ ;

il_param_last_instruction: ( il_param_assignment | il_param_out_assignment ) EOL+ ;

il_param_assignment     : il_assign_operator ( il_operand | ( '(' EOL+ simple_instr_list ')' ) ) ;

il_param_out_assignment : il_assign_out_operator variable ;

    /* B.2.2 Operators */

il_simple_operator      : 'LD'
                        | 'LDN'
                        | 'ST'
                        | 'STN'
                        | 'NOT'
                        | 'S'
                        | 'R'
                        | 'S1'
                        | 'R1'
                        | 'CLK'
                        | 'CU'
                        | 'CD'
                        | 'PV'
                        | 'IN'
                        | 'PT'
                        | il_expr_operator
                        ;

il_expr_operator        : 'AND'
                        | '&'
                        | 'OR'
                        | 'XOR'
                        | 'ANDN'
                        | '&N'
                        | 'ORN'
                        | 'XORN'
                        | 'ADD'
                        | 'SUB'
                        | 'MUL'
                        | 'DIV'
                        | 'MOD'
                        | 'GT'
                        | 'GE'
                        | 'EQ '
                        | 'LT'
                        | 'LE'
                        | 'NE'
                        ;

il_assign_operator      : variable_name ':=' ;

il_assign_out_operator  : 'NOT'? variable_name'=>' ;

il_call_operator        : 'CAL' | 'CALC' | 'CALCN' ;

il_return_operator      : 'RET' | 'RETC' | 'RETCN' ;

il_jump_operator        : 'JMP' | 'JMPC' | 'JMPCN' ;


    /* B.3 Language ST (Structured Text) */

    /* B.3.1 Expressions */

expression              : xor_expression ('OR' xor_expression)* ;

xor_expression          : and_expression ('XOR' and_expression)* ;

and_expression          : comparison (('&' | 'AND') comparison)* ;

comparison              : equ_expression ( ('=' | '<>') equ_expression)* ;

equ_expression          : add_expression (comparison_operator add_expression) ;

comparison_operator     : '<' | '>' | '<=' | '>=' ;

add_expression          : term (add_operator term)* ;

add_operator            : '+' | '-' ;

term                    : power_expression (multiply_operator power_expression)* ;

multiply_operator       : '*' | '/' | 'MOD' ;

power_expression        : unary_expression ('**' unary_expression)* ;

unary_expression        : unary_operator? primary_expression ;

unary_operator          : '-' | 'NOT' ;

primary_expression      : constant
                        | enumerated_value
                        | variable | '(' expression ')'
                        | function_name '(' param_assignment (',' param_assignment)* ')'
                        ;

    /* B.3.2 Statements */

statement_list          : (statement ';')+ ;

statement               : assignment_statement
                        | subprogram_control_statement
                        | selection_statement
                        | iteration_statement
                        ;

    /* B.3.2.1 Assignment statements */

assignment_statement    : variable ':=' expression ;

    /* B.3.2.2 Subprogram control statements */

subprogram_control_statement : fb_invocation | 'RETURN' ;

fb_invocation           : fb_name '(' (param_assignment (',' param_assignment)* )? ')' ;

param_assignment        : (variable_name ':=')? expression
                        | 'NOT'? variable_name '=>' variable
                        ;

    /* B.3.2.3 Selection statements */

selection_statement     : if_statement | case_statement ;

if_statement            : 'IF' expression
                            'THEN' statement_list
                            ('ELSIF' expression 'THEN' statement_list)*
                            ('ELSE' statement_list)?
                          'END_IF'
                        ;

case_statement          : 'CASE' expression 'OF' case_element+ ('ELSE' statement_list) 'END_CASE' ;

case_element            : case_list ':' statement_list ;

case_list               : case_list_element (',' case_list_element)* ;

case_list_element       : subrange
                        | signed_integer
                        | enumerated_value
                        ;


    /* B.3.2.4 Iteration statements */

iteration_statement     : for_statement
                        | while_statement
                        | repeat_statement
                        | exit_statement
                        ;

for_statement           : 'FOR' control_variable ':=' for_list 'DO' statement_list 'END_FOR' ;

control_variable        : identifier ;

for_list                : expression 'TO' expression ('BY' expression)? ;

while_statement         : 'WHILE' expression 'DO' statement_list 'END_WHILE' ;

repeat_statement        : 'REPEAT' statement_list 'UNTIL' expression 'END_REPEAT' ;

exit_statement          : 'EXIT' ;



