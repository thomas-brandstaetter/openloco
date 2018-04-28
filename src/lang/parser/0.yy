#line 1 "0.yy"
file
    : library_element_name END { YYACCEPT; }
    | library_element_declaration END { YYACCEPT; }
    ;

    // -----------------------------------------------------------------------
    // B.0 Programming model
    // -----------------------------------------------------------------------

library_element_name: IDENTIFIER;
    //    : data_type_name
    //    | function_name
    //    | function_block_type_name
    //    | program_type_name
    //    | resource_type_name
    //    | configuration_name
    //    ;

library_element_declaration
    : data_type_declaration
    | function_declaration
    | function_block_declaration
    | program_declaration
//    | configuration_declaration
    ;
