#pragma once

/**
 * @author Thomas Brandstätter 
 * @date 29.04.18.
 */

#include <vector>
#include <string>
#include <iostream>

#include <location.hh>

#include "file.h"

namespace openloco {
namespace lang {

    class error
    {
    public:
        typedef enum struct error_type_
        {
             E_undefined = 0
            ,E_custom
            ,E_nested_comments
            ,E_ambiguous_enumerated_value
            ,E_value_exceeds_subrange
            ,E_missing_configuration
            ,E_modify_constant
            ,E_global_external_constant_missmatch
            ,E_use_direct_or_external_variables
            ,E_variable_not_properly_mapped
            ,E_ambiguous_values_by_in_out
            ,E_type_conversion
            ,E_numeric_result_exceeds_data_type
            ,E_numeric_result_div_zero
            ,E_negative_shift
            ,E_mixed_input_data_types
            ,E_selector_out_of_range_mux
            ,E_invalid_character_position
            ,E_exceed_max_string_length
            ,E_less_zero_string_function
            ,E_exceeds_range_data_type
            ,E_no_value_for_fb_input
            ,E_no_value_for_inout
            ,E_zero_initial_steps
            ,E_more_initial_steps
            ,E_user_modify_step_state
            ,E_user_modify_time
            ,E_side_effect_transition_condition
            ,E_action_control_contention
            ,E_simultaneously_true_non_prioritized_transitions
            ,E_unsafe_sfc
            ,E_unreadable_sfc
            ,E_type_conflict
            ,in_var_access
            ,E_task_fails_to_schedule
            ,E_task_fails_meet_deadline
            ,E_numeric_exceeds_range
            ,E_result_and_operand_not_same_type
            ,E_div_by_zero
            ,E_numeric_exceeds_range_data_type
            ,E_invalid_data_type_operation
            ,E_return_without_value
            ,E_iteration_fails_to_terminate
            ,E_same_identifier_used_as_connector_and_element_name
            ,E_uninitialized_feedback_variable
        } error_type;

        /**
         * Holds error messages according to error_type
         */
        static const std::vector<std::string> error_messages;

        static const std::vector<std::string> error_subclauses;

    public:
        static error make_error(error_type type, class file& file, location loc);
        static error make_custom_error(std::string message, class file& file, location loc);

    public:
        void print(std::ostream& is = std::cerr);

    private:

        error(file& file, location loc) : _file(file), _loc(loc)
        {
        }

        error_type _type;
        std::string _subclass;
        std::string _message;
        class file& _file;
        location _loc;


    };

}}