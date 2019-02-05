Introduction
============

Conventions
-----------

- ``*`` zero or more repetition-symbol
- ``+`` one or more repetition-symbol
- ``-`` except-symbol
- `` `` concatenate-symbol
- ``|`` definition-separator-symbol
- ``=`` defining-symbol
- ``.`` terminator-symbol


B.1 Common Elements
===================

B.1.1 Letters, digits and identifiers
-------------------------------------

PRODUCTION RULES

::

    letter                          = `A` | `B` | ... | `Z` | `a` | `b` | ... | `z`

    digit                           = `0` | `1` | ... | `9`

    octal_digit                     = `0` | `1` | ... | `7`

    hex_digit                       = digit | `A` | `B` | `C` | `D` | `E` | `F`

    identifier                      = ( letter | ( `_` ( letter | digit ) ) ) { [`_`] ( letter | digit ) }

Semantics
~~~~~~~~~

The ... here indicates the ISO/IEC 10646-1 sequence of 26 letters or numbers between 2 and 6 or 2 and 8.


B.1.2 Constants
---------------

Production Rule

::

    numeric_literal                 = integer_literal | real_literal

    integer_literal                 = [ integer_type_name `#` ] ( signed_integer | binary_integer | octal_integer | hex_integer)

    signed_integer                  = [ `+` | `-` ] integer

    integer                         = digit { [`_`] digit }

    binary_integer                  = `2#` bit { [`_`] bit }

    bit                             = `1` | `0`

    octal_integer                   = `8#` octal_digit { [`_`] octal_digit}

    hex_integer                     = `16#` hex_digit { [`_`] hex_digit}

    real_literal                    = [ real_type_name `#` ] signed_integer  `.` integer [exponent]

    exponent                        = ( `E` | `e` ) [ `+` | `-` ] integer

    bit_string_literal              = [ (`BYTE` | `WORD` | `DWORD` | `LWORD`) `#` ] ( unsigned_integer | binary_integer | octal_integer | hex_integer)

    boolean_literal                 = ( [`BOOL#`]( `1` | `0` ) ) | `TRUE` | `FALSE`


B.1.2.2 Character strings
~~~~~~~~~~~~~~~~~~~~~~~~~

PRODUCTION RULES

::

    character_string                = single_byte_character_string | double_byte_character_string

    single_byte_character_string    = `z` {single_byte_character_representation} `'`

    double_byte_character_string    = `"` {double_byte_character_representation} `"`

    single_byte_character_representation = common_character_representation | `$'` | `"` | ( `$` hex_digit hex_digit )

    double_byte_character_representation = common_character_representation | `$"` | `'`| ( `$` hex_digit hex_digit hex_digit hex_digit )

    common_character_representation = <any printable character except `$`, `"` or `'`> | `$$` | `$L` | `$N` | `$P` | `$R` | `$T` | `$l` | `$n` | `$p` | `$r` | `$t`


B.1.2.3 Time literals
~~~~~~~~~~~~~~~~~~~~~

PRODUCTION RULE

::

    time_literal                    = duration | time_of_day | date | date_and_time


B.1.2.3.1 Duration
~~~~~~~~~~~~~~~~~~

PRODUCTION RULES

::

    duration                        = (`T` | `TIME`) `#` [`-`] interval

    interval                        = days
                                    | hours
                                    | minutes
                                    | seconds
                                    | milliseconds

    days                            = fixed_point (`d`) | integer (`d`) [`_`] hours

    fixed_point                     = integer [ `.` integer]

    hours                           = fixed_point (`h`)
                                    | integer (`h`) [`_`] minutes

    minutes                         = fixed_point (`m`)
                                    | integer (`m`) [`_`] seconds

    seconds                         = fixed_point (`s`)
                                    | integer (`s`) [`_`] milliseconds

    milliseconds                    = fixed_point (`ms`)

SEMANTICS

    The semantics of 2.2.3.1 impose additional constraints on the allowable values of `hours`,
    `minutes`, `seconds`, and `milliseconds`.

B.1.2.3.2 Time of day and date
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

PRODUCTION RULES

::

    time_of_day                     = ( `TIME_OF_DAY` | `TOD` ) `#` daytime

    daytime                         = day_hour `:` day_minute `: day_second

    day_hour                        = integer

    day_minute                      = integer

    day_second                      = fixed_point

    date                            = (`DATE` | `D`) `#` date_literal

    date_literal                    = year `-` month `-` day

    year                            = integer

    month                           = integer

    day                             = integer

    date_and_time                   = (`DATE_AND_TIME` | `DT`) `#` date_literal `-` daytime

SEMANTICS

The semantics of 2.2.3.2 impose additional constraints on the allowable values of


B.1.3 Data types
----------------

PRODUCTION RULES

::

    data_type_name                  = non_generic_type_name | generic_type_name

    non_generic_type_name           = elementary_type_name | derived_type_name


B.1.3.1 Elementary data types
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

PRODUCTION RULES

::

    elementary_type_name            = numeric_type_name
                                    | date_type_name
                                    | bit_string_type_name
                                    | `STRING`
                                    | `WSTRING`
                                    | `TIME`

    numeric_type_name               = integer_type_name | real_type_name

    integer_type_name               = signed_integer_type_name | unsigned_integer_type_name

    signed_integer_type_name        = `SINT` | `INT` | `DINT` | `LINT`

    unsigned_integer_type_name      = `USINT` | `UINT` | `UDINT` | `ULINT`

    real_type_name                  = `REAL` | `LREAL`

    date_type_name                  = `DATE` | `TIME_OF_DAY` | `TOD` | `DATE_AND_TIME` | `DT`

    bit_string_type_name            = `BOOL` | `BYTE` | `WORD` | `DWORD` | `LWORD`


B.1.3.2 Generic data types
~~~~~~~~~~~~~~~~~~~~~~~~~~

PRODUCTION RULE

::

    generic_type_name               = `ANY`
                                    | `ANY_DERIVED`
                                    | `ANY_ELEMENTARY`
                                    | `ANY_MAGNITUDE`
                                    | `ANY_NUM`
                                    | `ANY_REAL`
                                    | `ANY_INT`
                                    | `ANY_BIT`
                                    | `ANY_STRING`
                                    | `ANY_DATE`



B.1.3.3 Derived data types
~~~~~~~~~~~~~~~~~~~~~~~~~~

PRODUCTION RULES

::

    derived_type_name               = single_element_type_name | array_type_name | structure_type_name | string_type_name

    single_element_type_name        = simple_type_name | subrange_type_name | enumerated_type_name

    simple_type_name ::= identifier

    subrange_type_name              = identifier

    enumerated_type_name            = identifier

    array_type_name                 = identifier

    structure_type_name             = identifier

    data_type_declaration           = `TYPE` type_declaration `;`
                                          {type_declaration `;`}
                                      `END_TYPE`

    type_declaration                = single_element_type_declaration
                                    | array_type_declaration
                                    | structure_type_declaration
                                    | string_type_declaration

    single_element_type_declaration = simple_type_declaration
                                    | subrange_type_declaration
                                    | enumerated_type_declaration

    simple_type_declaration         = simple_type_name `:` simple_spec_init

    simple_spec_init                = simple_specification [`:=` constant]

    simple_specification            = elementary_type_name | simple_type_name

    subrange_type_declaration       = subrange_type_name `:` subrange_spec_init

    subrange_spec_init              = subrange_specification [ `:=` signed_integer ]

    subrange_specification          = integer_type_name `(` subrange`)`
                                    | subrange_type_name

    subrange                        = signed_integer `..` signed_integer

    enumerated_type_declaration     = enumerated_type_name `:` enumerated_spec_init

    enumerated_spec_init            = enumerated_specification [`:=` enumerated_value]

    enumerated_specification        = ( `(` enumerated_value {`,` enumerated_value} `)` )
                                    | enumerated_type_name

    enumerated_value                = [enumerated_type_name `#`] identifier

    array_type_declaration          = array_type_name `:` array_spec_init

    array_spec_init                 = array_specification [`:=` array_initialization]

    array_specification             = array_type_name
                                    | `ARRAY` `[` subrange {`,` subrange} `]` `OF` non_generic_type_name

    array_initialization            = `[` array_initial_elements {`,` array_initial_elements} `]`

    array_initial_elements          = array_initial_element
                                    | integer `(` [array_initial_element] `)`

    array_initial_element           = constant
                                    | enumerated_value
                                    | structure_initialization
                                    | array_initialization

    structure_type_declaration      = structure_type_name `:` structure_specification

    structure_specification         = structure_declaration | initialized_structure

    initialized_structure           = structure_type_name [`:=` structure_initialization]

    structure_declaration           = `STRUCT` +( structure_element_declaration `;` ) `END_STRUCT`

    structure_element_declaration   = structure_element_name `:` (  simple_spec_init
                                                                  | subrange_spec_init
                                                                  | enumerated_spec_init
                                                                  | array_spec_init
                                                                  | initialized_structure
                                                                 )

    structure_element_name          = identifier

    structure_initialization        = `(` structure_element_initialization {`,` structure_element_initialization} `)`

    structure_element_initialization = structure_element_name `:=` (  constant
                                                                    | enumerated_value
                                                                    | array_initialization
                                                                    | structure_initialization
                                                                   )

    string_type_name                = identifier

    string_type_declaration         = string_type_name `:` (`STRING`|`WSTRING`) [`[` integer `]`] [`:=` character_string]


B.1.4 Variables
---------------

PRODUCTION RULES

::

    variable                        = direct_variable | symbolic_variable

    symbolic_variable               = variable_name | multi_element_variable

    variable_name                   = identifier


B.1.4.1 Directly represented variables
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

PRODUCTION RULES

::

    direct_variable                 = `%` location_prefix size_prefix integer { `.` integer }

    location_prefix                 = `I` | `Q` | `M`

    size_prefix                     = NIL | `X` | `B` | `W` | `D` | `L`


B.1.4.2 Multi-element variables
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

PRODUCTION RULES

::

    multi_element_variable          = array_variable | structured_variable

    array_variable                  = subscripted_variable subscript_list

    subscripted_variable            = symbolic_variable

    subscript_list                  = `[` subscript {`,` subscript} `]`

    subscript                       = expression

    structured_variable             = record_variable `.` field_selector

    record_variable                 = symbolic_variable

    field_selector                  = identifier


B.1.4.3 Declaration and initialization
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

PRODUCTION RULES

::

    input_declarations              = `VAR_INPUT` [`RETAIN` | `NON_RETAIN`] +(input_declaration `;`) `END_VAR`

    input_declaration               = var_init_decl | edge_declaration

    edge_declaration                = var1_list `:` `BOOL` (`R_EDGE` | `F_EDGE`)

    var_init_decl                   = var1_init_decl
                                    | array_var_init_decl
                                    | structured_var_init_decl
                                    | fb_name_decl
                                    | string_var_declaration

    var1_init_decl                  = var1_list `:` (simple_spec_init | subrange_spec_init | enumerated_spec_init)

    var1_list                       = variable_name {`,` variable_name}

    array_var_init_decl             = var1_list `:` array_spec_init

    structured_var_init_decl        = var1_list `:` initialized_structure

    fb_name_decl                    = fb_name_list `:` function_block_type_name [ ’:=’ structure_initialization ]

    fb_name_list                    = fb_name *( `,` fb_name )

    fb_name                         = identifier

    output_declarations             = `VAR_OUTPUT` [`RETAIN` | `NON_RETAIN`] +( var_init_decl `;` ) `END_VAR`

    input_output_declarations       = `VAR_IN_OUT` +( var_declaration `;` ) `END_VAR`

    var_declaration                 = temp_var_decl | fb_name_decl

    temp_var_decl                   = var1_declaration | array_var_declaration | structured_var_declaration | string_var_declaration

    var1_declaration                = var1_list `:` ( simple_specification | subrange_specification | enumerated_specification )

    array_var_declaration           = var1_list `:` array_specification

    structured_var_declaration      = var1_list `:` structure_type_name

    var_declarations                = `VAR` [`CONSTANT`] *( var_init_decl `;` ) `END_VAR`

    retentive_var_declarations      = `VAR` `RETAIN` +( var_init_decl `;` ) `END_VAR`

    located_var_declarations        = `VAR` [`CONSTANT` | `RETAIN` | `NON_RETAIN`] *( located_var_decl `;` ) `END_VAR`

    located_var_decl                = [variable_name] location `:` located_var_spec_init

    external_var_declarations       = `VAR_EXTERNAL` [`CONSTANT`] +(external_declaration `;`) `END_VAR`

    external_declaration            = global_var_name `:` (  simple_specification
                                                           | subrange_specification
                                                           | enumerated_specification
                                                           | array_specification
                                                           | structure_type_name
                                                           | function_block_type_name
                                                          )

    global_var_name                 = identifier

    global_var_declarations         = `VAR_GLOBAL` [`CONSTANT` | `RETAIN`] +( global_var_decl `;` ) `END_VAR`

    global_var_decl                 = global_var_spec `:` [ located_var_spec_init | function_block_type_name ]

    global_var_spec                 = global_var_list | [global_var_name] location

    located_var_spec_init           = simple_spec_init
                                    | subrange_spec_init
                                    | enumerated_spec_init
                                    | array_spec_init
                                    | initialized_structure
                                    | single_byte_string_spec
                                    | double_byte_string_spec

    location                        = `AT` direct_variable

    global_var_list                 = global_var_name {`,` global_var_name}

    string_var_declaration          = single_byte_string_var_declaration | double_byte_string_var_declaration

    single_byte_string_var_declaration = var1_list `:` single_byte_string_spec

    single_byte_string_spec         = `STRING` [`[` integer `]`] [`:=` single_byte_character_string]

    double_byte_string_var_declaration = var1_list `:` double_byte_string_spec

    double_byte_string_spec         = `WSTRING` [`[` integer `]`] [`:=` double_byte_character_string]

    incompl_located_var_declarations = `VAR` [`RETAIN`|`NON_RETAIN`] +( incompl_located_var_decl `;` ) `END_VAR`

    incompl_located_var_decl        = variable_name incompl_location `:` var_spec

    incompl_location                = `AT` `%` (`I` | `Q` | `M`) `*`

    var_spec                        = simple_specification
                                    | subrange_specification
                                    | enumerated_specification
                                    | array_specification
                                    | structure_type_name
                                    | `STRING` [`[` integer `]`] | `WSTRING` [`[` integer `]`]


B.1.5 Program organization units
--------------------------------

B.1.5.1 Functions
~~~~~~~~~~~~~~~~~

PRODUCTION RULES

::

    function_name                   = standard_function_name
                                    | derived_function_name

    standard_function_name          = <as defined in 2.5.1.5>

    derived_function_name           = identifier

    function_declaration            = `FUNCTION` derived_function_name `:` (elementary_type_name | derived_type_name)
                                          *( io_var_declarations | function_var_decls )
                                          function_body
                                      `END_FUNCTION`

    io_var_declarations             = input_declarations | output_declarations | input_output_declarations

    function_var_decls              = `VAR` [`CONSTANT`] +( var2_init_decl `;` ) `END_VAR`

    function_body                   = ladder_diagram | function_block_diagram | instruction_list | statement_list | <other languages>

    var2_init_decl                  = var1_init_decl | array_var_init_decl | structured_var_init_decl | string_var_declaration

SEMANTICS

This syntax does not reflect the fact that each function must have at least one input declaration.
This syntax does not reflect the fact that edge declarations, function block references and invocations are not allowed in function bodies.
Ladder diagrams and function block diagrams are graphically represented as defined in Clause 4.
The non-terminals instruction_list and statement_list are defined in B.2.1 and B.3.2, respectively.


B.1.5.2 Function blocks
~~~~~~~~~~~~~~~~~~~~~~~

PRODUCTION RULES

::

    function_block_type_name        = standard_function_block_name | derived_function_block_name

    standard_function_block_name    = <as defined in 2.5.2.3>

    derived_function_block_name     = identifier

    function_block_declaration      = `FUNCTION_BLOCK` derived_function_block_name
                                          { io_var_declarations | other_var_declarations }
                                          function_block_body
                                      `END_FUNCTION_BLOCK`
    other_var_declarations          = external_var_declarations
                                    | var_declarations
                                    | retentive_var_declarations
                                    | non_retentive_var_declarations
                                    | temp_var_decls
                                    | incompl_located_var_declarations

    temp_var_decls                  = `VAR_TEMP` +( temp_var_decl `;` ) `END_VAR`

    non_retentive_var_decls         = `VAR` `NON_RETAIN` +( var_init_decl `;` ) `END_VAR`

    function_block_body ::= sequential_function_chart | ladder_diagram | function_block_diagram | instruction_list | statement_list | <other languages>


SEMANTICS:
Ladder diagrams and function block diagrams are graphically represented as defined in clause 4.

The non-terminals sequential_function_chart, instruction_list, and statement_list are defined in B.1.6, B.2.1, and B.3.2, respectively.


B.1.5.3 Programs
~~~~~~~~~~~~~~~~

PRODUCTION RULES

::

    program_type_name               = identifier
    program_declaration             = `PROGRAM` program_type_name
                                          *(  io_var_declarations
                                            | other_var_declarations
                                            | located_var_declarations
                                            | program_access_decls
                                           )
                                          function_block_body
                                      `END_PROGRAM`

    program_access_decls            = `VAR_ACCESS`  +( program_access_decl `;` ) `END_VAR`

    program_access_decl             = access_name `:` symbolic_variable `:` non_generic_type_name [direction]




B.1.6 Sequential function chart elements
----------------------------------------

PRODUCTION RULES

::

    sequential_function_chart       = sfc_network *( sfc_network )

    sfc_network                     = initial_step ( step | transition | action )

    initial_step                    = `INITIAL_STEP` step_name `:` +( action_association `;` ) `END_STEP`

    step                            = `STEP` step_name `:` +( action_association `;` ) `END_STEP`

    step_name                       = identifier

    action_association              = action_name `(` *( `,` indicator_name ) `)`

    action_name                     = identifier

    action_qualifier                = `N` | `R` | `S` | `P` | timed_qualifier `,` action_time

    timed_qualifier                 = `L` | `D` | `SD` | `DS` | `SL`

    action_time                     = duration | variable_name

    indicator_name                  = variable_name

    transition                      = `TRANSITION` [transition_name] [`(` `PRIORITY` `:=` integer `)`] `FROM` steps `TO` steps
                                          transition_condition
                                      `END_TRANSITION`

    transition_name                 = identifier

    steps                           = step_name | `(` step_name `,` step_name {`,` step_name} `)`

    transition_condition            = `:` simple_instruction_list | `:=` expression `;` | `:` (fbd_network | rung)

    action                          = `ACTION` action_name `:` function_block_body `END_ACTION`


SEMANTICS

The use of function block diagram networks and ladder diagram rungs, denoted by the non-terminals fbd_network and rung,respectively, for the expression of transition conditions shall be as defined in 2.6.3.

The non-terminals simple_instruction_list and expression are defined in B.2.1 and B.3.1, respectively.

The term [transition_name] can only be used in the production for transition when feature 7 of table 41 is supported. The resulting production is the textual equivalent of this feature.


B.1.7 Configuration elements
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

PRODUCTION RULES

::

    configuration_name              = identifier

    resource_type_name              = identifier

    configuration_declaration       = `CONFIGURATION` configuration_name

                                          [global_var_declarations]
                                          (  single_resource_declaration
                                           | +( resource_declaration )
                                          ) [access_declarations] [instance_specific_initializations]
                                      `END_CONFIGURATION`

    resource_declaration            = `RESOURCE` resource_name `ON` resource_type_name
                                          [global_var_declarations]
                                          single_resource_declaration
                                      `END_RESOURCE`

    single_resource_declaration     = *( task_configuration `;` ) +( program_configuration `;` )

    resource_name                   = identifier

    access_declarations             = `VAR_ACCESS` +( access_declaration `;` ) `END_VAR`

    access_declaration              = access_name `:` access_path `:` non_generic_type_name [direction]

    access_path                     = [resource_name `.`] direct_variable
                                    | [resource_name `.`] [program_name `.` {fb_name`.`} symbolic_variable

    global_var_reference            = [resource_name `.d] global_var_name [`.` structure_element_name]

    access_name                     = identifier

    program_output_reference        = program_name `.` symbolic_variable

    program_name                    = identifier

    direction                       = `READ_WRITE` | `READ_ONLY`

    task_configuration              = `TASK` task_name task_initialization task_name := identifier

    task_initialization             = `(` [`SINGLE` `:=` data_source `,`] [`INTERVAL` `:=` data_source `,`] `PRIORITY` `:=` integer `)`

    data_source                     = constant
                                    | global_var_reference
                                    | program_output_reference
                                    | direct_variable


    program_configuration           = `PROGRAM` [RETAIN | NON_RETAIN] program_name [`WITH` task_name] `:` program_type_name [`(` prog_conf_elements `)`]

    prog_conf_elements              = prog_conf_element {`,` prog_conf_element}

    prog_conf_element               = fb_task | prog_cnxn

    fb_task                         = fb_name `WITH` task_name

    prog_cnxn                       = symbolic_variable `:=` prog_data_source
                                    | symbolic_variable `=>` data_sink

    prog_data_source                = constant
                                    | enumerated_value
                                    | global_var_reference
                                    | direct_variable

    data_sink                       = global_var_reference | direct_variable

    instance_specific_initializations = `VAR_CONFIG` +( instance_specific_init `;` ) `END_VAR`
    instance_specific_init          = resource_name `.` program_name `.` {fb_name `.`}
                                      (  (variable_name [location] `:` located_var_spec_init)
                                       | (fb_name `:` function_block_type_name `:=` structure_initialization)
                                      )


SEMANTICS

This syntax does not reflect the fact that location assignments are only allowed for references to variables which are marked by the asterisk notation at type declaration level.


B.2 Language IL (Instruction List)
==================================

B.2.1 Instructions and operands
-------------------------------

PRODUCTION RULES

::

    instruction_list                = il_instruction {il_instruction}

    il_instruction                  = [label`:`]
                                      [  il_simple_operation
                                       | il_expression
                                       | il_jump_operation
                                       | il_fb_call
                                       | il_formal_funct_call
                                       | il_return_operator
                                      ]
                                      +EOL

    label                           = identifier

    il_simple_operation             = il_simple_operator [il_operand]
                                    | function_name [il_operand_list]

    il_expression                   = il_expr_operator `(` [ il_operand ] +EOL [ simple_instr_list ] `)`

    il_jump_operation               = il_jump_operator label

    il_fb_call                      = il_call_operator fb_name [`(` ( +EOL [ il_param_list ] | [ il_operand_list ] `)`]

    il_formal_funct_call            = function_name `(` +EOL [il_param_list] `)`

    il_operand                      = constant | variable | enumerated_value

    il_operand_list                 = il_operand *( `,` il_operand )

    simple_instr_list               = *il_simple_instruction

    il_simple_instruction           = ( il_simple_operation | il_expression | il_formal_funct_call ) +EOL

    il_param_list                   = +il_param_last_instruction

    il_param_instruction            = ( il_param_assignment | il_param_out_assignment ) `,` +EOL

    il_param_last_instruction       = ( il_param_assignment | il_param_out_assignment ) +EOL

    il_param_assignment             = il_assign_operator ( il_operand | ( `(` +EOL simple_instr_list `)` ) )

    il_param_out_assignment         = il_assign_out_operator variable



B.2.2 Operators
~~~~~~~~~~~~~~~

PRODUCTION RULES

::

    il_simple_operator              = `LD` | `LDN` | `ST` | `STN` | `NOT` | `S` | `R` | `S1` | `R1` | `CLK` | `CU` | `CD` | `PV` | `IN` | `PT` | il_expr_operator

    il_expr_operator                = `AND` | `&` | `OR` | `XOR` | `ANDN` | `&N` | `ORN` | `XORN` | `ADD` | `SUB` | `MUL` | `DIV` | `MOD` | `GT` | `GE` | `EQ ` | `LT` | `LE` | `NE`

    il_assign_operator              = variable_name `:=`

    il_assign_out_operator          = [`NOT`] variable_name `=>`

    il_call_operator                = `CAL` | `CALC` | `CALCN`

    il_return_operator              = `RET` | `RETC` | `RETCN`

SEMANTICS

This syntax does not reflect the possibility for typing IL operators as noted in table 52.


B.3 Language ST (Structured Text)
=================================

B.3.1 Expressions
-----------------

PRODUCTION RULES

::

    expression                      = xor_expression {`OR` xor_expression}

    xor_expression                  = and_expression {`XOR` and_expression}

    and_expression                  = comparison {(`&` | `AND`) comparison}

    comparison                      = equ_expression { (`=` | `<>`) equ_expression}

    equ_expression                  = add_expression {comparison_operator add_expression}

    comparison_operator             = `<` | `>` | `<=` | `>=` `

    add_expression                  = term {add_operator term}

    add_operator                    = `+` | `-`

    term                            = power_expression {multiply_operator power_expression}

    multiply_operator               = `*` | `/` | `MOD`

    power_expression                = unary_expression { `**` unary_expression }

    unary_expression                = [unary_operator] primary_expression

    unary_operator                  = `-` | `NOT`

    primary_expression              = constant
                                    | enumerated_value
                                    | variable
                                    | `(` expression `)`
                                    | function_name `(` param_assignment *( `,` param_assignment) `)`


SEMANTICS

These definitions have been arranged to show a top-down derivation of expression structure.
The precedence of operations is then implied by a “bottom-up” reading of the definitions of the various kinds of expressions.
Further discussion of the semantics of these definitions is given in 3.3.1. See 2.5.1.1 for details of the semantics of function calls.


B.3.2 Statements
----------------

PRODUCTION RULE

::

    statement_list                  = statement `;` {statement `;`}

    statement                       = NIL | assignment_statement | subprogram_control_statement | selection_statement | iteration_statement


B.3.2.1 Assignment statements
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

PRODUCTION RULE

::

    assignment_statement            = variable `:=` expression

B.3.2.2 Subprogram control statements
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

PRODUCTION RULES

::

    subprogram_control_statement    = fb_invocation | `RETURN`

    fb_invocation                   = fb_name `(` [param_assignment {`,` param_assignment}] `)`

    param_assignment                = ([variable_name `:=`] expression) | ([`NOT`] variable_name `=>` variable)


B.3.2.3 Selection statements
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

PRODUCTION RULES

::

    selection_statement             = if_statement | case_statement

    if_statement                    = `IF` expression
                                          `THEN` statement_list
                                           { `ELSIF` expression `THEN` statement_list }
                                           [`ELSE` statement_list ]
                                      `END_IF`

    case_statement                  = `CASE` expression `OF`
                                          case_element
                                          {case_element}
                                          [`ELSE` statement_list]
                                      `END_CASE`

    case_element                    = case_list `:` statement_list

    case_list                       = case_list_element {`,` case_list_element}

    case_list_element               = subrange | signed_integer | enumerated_value


B.3.2.4 Iteration statements
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

PRODUCTION RULES

::

    iteration_statement             = for_statement | while_statement | repeat_statement | exit_statement

    for_statement                   = `FOR` control_variable `:=` for_list `DO` statement_list `END_FOR`

    control_variable                = identifier

    for_list                        = expression `TO` expression [`BY` expression]

    while_statement                 = `WHILE` expression `DO` statement_list `END_WHILE`

    repeat_statement                = `REPEAT` statement_list `UNTIL` expression `END_REPEAT`

    exit_statement                  = `EXIT`





















.. [EBNF]_(Extended Backus-Naur Form)[https://en.wikipedia.org/wiki/Extended_Backus–Naur_form]

