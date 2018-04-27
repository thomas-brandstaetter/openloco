

    // -----------------------------------------------------------------------
    // B.1.6 Sequential function chart elements
    // -----------------------------------------------------------------------

sequential_function_chart: sfc_networks;

sfc_networks
    : sfc_networks sfc_network
    | sfc_network
    ;

sfc_network: initial_step sfc_networks;

sfc_networks
    : sfc_networks step
    | sfc_networks transition
    | sfc_networks action
    |
    ;

initial_step: INITIAL_STEP IDENTIFIER COLON action_associations END_STEP;

step: STEP IDENTIFIER COLON action_associations END_STEP;

action_associations
    : action_associations action_association SEMICOLON
    |
    ;

action_association : IDENTIFIER LPAR action_association_qualifier indicator_names RPAR

indicator_names
    : indicator_names COMMA IDENTIFIER
    |
    ;

action_association_qualifier
    : action_qualifier
    |
    ;

action_qualifier
    : "N"
    | "R"
    | "S"
    | "P"
    | timed_qualifier "," action_time
    ;

timed_qualifier
    : "L"
    | "D"
    | "SD"
    | "DS"
    | "SL"
    ;

action_time
    : duration
    | IDENTIFIER
    ;

transition:
    "TRANSITION"
        transition_name transition_priority FROM steps TO steps
        transition_condition
    "END_TRANSITION"
    ;


transition_name
    : IDENTIFIER
    |
    ;

transition_priority
    : LPAR PRIORITY DEF INTEGER RPAR
    |
    ;

steps
    : IDENTIFIER
    | LPAR IDENTIFIER COMMA IDENTIFIER step_names RPAR
    ;

step_names
    : step_names COMMA IDENTIFIER
    |
    ;

    // TODO
transition_condition
    : COLON "IL_INSTRUCTIONS_PLACEHOLDER";

action: ACTION IDENTIFIER COLON function_block_body END_ACTION;
