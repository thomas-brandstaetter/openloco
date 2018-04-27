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

    // program_type_name: IDENTIFIER;

program_declaration:
    PROGRAM IDENTIFIER
        program_declaration__declarations
        function_block_body
    END_PROGRAM
    ;

program_declaration__declarations
    : program_declaration__declarations program_declaration_var
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
        program_access_decls__declarations
     END_VAR
     ;

program_access_decls__declarations
    : program_access_decls__declarations program_access_decl SEMICOLON
    |
    ;

program_access_decl: IDENTIFIER COLON symbolic_variable COLON non_generic_type_name program_access_decl_direction;

program_access_decl_direction
    : direction
    |
    ;
