#line 1 "17.yy"

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

instance_specific_initializations
    : VAR_CONFIG instance_specific_init SEMICOLON isis_inits END_VAR

isis_inits
    : isis_inits instance_specific_init SEMICOLON
    |
    ;

instance_specific_init
    : resource_name DOT program_name DOT isi_fb_names isi_init
    ;

isi_fb_names
    : isi_fb_names fb_name DOT
    |
    ;

isi_init
    : variable_name COLON located_var_spec_init
    | variable_name location COLON located_var_spec_init
    | fb_name COLON function_block_type_name DEF structure_initialization
    ;
