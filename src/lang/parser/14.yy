#line 1 "14.yy"
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
    : "." INTEGER directive_variable__positions
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

subscript_list: LSQUAREB subscript subscript_list__subscripts RSQUAREB;

subscript_list__subscripts
    : subscript_list__subscripts "," subscript
    |
    ;

    // TODO
subscript: IDENTIFIER;

structured_variable: record_variable "." field_selector;

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
    : var1_list COLON BOOL ed_edge
    ;

ed_edge
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

var1_list: IDENTIFIER identifier_list__;

    // var1_list__variables
    //     : var1_list__variables "," IDENTIFIER
    //     |
    //     ;

identifier_list__
    : identifier_list__ "," IDENTIFIER

array_var_init_decl: var1_list COLON array_spec_init;

structured_var_init_decl: var1_list COLON initialized_structure;


fb_name_decl
    : fb_name_list COLON IDENTIFIER
    | fb_name_list COLON IDENTIFIER DEF structure_initialization;


fb_name_list: fb_name fnl_names;

fnl_names
    :  fnl_names COMMA fb_name
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
