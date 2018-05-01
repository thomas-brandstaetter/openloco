/**
 * @author Thomas Brandstätter 
 * @date 29.04.18.
 */

#include <string>
#include <vector>

#include <src/lang/driver/error.h>



std::vector<std::string> openloco::lang::error::error_messages = {
    "Undefined Error", "", "Nested comments", "Ambiguous enumerated value",
    "Value of a variable exceeds the specified subrange",
    "Missing configuration of an incomplete address specification (\"*\" notation)",
    "Attempt by a program organization unit to modify a variable which has been declared CONSTANT",
    "Declaration of a variable as VAR_GLOBAL CONSTANT in a containing element having a contained element in which the same variable is declared VAR_EXTERNAL without the CONSTANT qualifier.",
    "Improper use of directly represented or external variables in functions",
    "A VAR_IN_OUT variable is not “properly mapped”", "Ambiguous value caused by a VAR_IN_OUT connection",
    "Type conversion errors", "Numerical result exceeds range for data type", "Division by zero",
    "N input is less than zero in a bit-shift function", "Mixed input data types to a selection function",
    "Selector (K) out of range for MUX function", "Invalid character position specified",
    "Result exceeds maximum string length", "ANY_INT input is less than zero in a string function",
    "Result exceeds range for data type",
    "No value specified for a function block instance used as input variable",
    "No value specified for an in-out variable", "Zero initial steps in SFC network",
    "More than one initial steps in SFC network", "User program attempts to modify step state",
    "User program attempts to modify time", "Side effects in evaluation of transition condition",
    "Action control contention error",
    "Simultaneously true, non-prioritized transitions in a selection divergence",
    "Unsafe SFC", "Unreachable SFC", "Data type conflict in VAR_ACCESS",
    "A task fails to be scheduled or to meet its execution deadline",
    "Numerical result exceeds range for data type", "Current result and operand not of same data type",
    "Division by zero", "Numerical result exceeds range for data type", "Invalid data type for operation",
    "Return from function without value assigned", "Iteration fails to terminate",
    "Same 11_identifier used as connector label and element name", "Uninitialized feedback variable"
};

std::vector<std::string> openloco::lang::error::error_subclauses = {
    "0", "1", "2.1.5", "2.3.3.1", "2.3.3.1", "2.4.1.1", "2.4.3", "2.4.3", "2.5.1", "2.5.1.1", "2.5.1.1",
    "2.5.1.5.1", "2.5.1.5.2", "2.5.1.5.2", "2.5.1.5.3", "2.5.1.5.4", "2.5.1.5.4", "2.5.1.5.5", "2.5.1.5.5",
    "2.5.1.5.5", "2.5.1.5.6", "2.5.2.2", "2.5.2.2", "2.6.2", "2.6.2", "2.6.2", "2.6.2", "2.6.3", "2.6.4.5",
    "2.6.5", "2.6.5", "2.6.5", "2.7.1", "2.7.2", "3.2.2", "3.2.2", "3.3.1", "3.3.1", "3.3.1", "3.3.2.1",
    "3.3.2.4", "4.1.1", "4.1.3"
};







openloco::lang::error
openloco::lang::error::error_with_type(error_type type) {
    openloco::lang::error error;

    error._type = type;
    std::vector<std::string>::size_type idx = static_cast<std::vector<std::string>::size_type>(type);
    error._message = error_messages[idx];
    error._subclass = error_subclauses[idx];

    return error;
}

openloco::lang::error
openloco::lang::error::custom_error(std::string message) {

    openloco::lang::error error;
    error_type type = error::error_type::E_custom;
    std::vector<std::string>::size_type idx = static_cast<std::vector<std::string>::size_type>(type);

    error._type = type;
    error._subclass = error::error_subclauses[idx];
    error._message = error_messages[idx];

    return error;
}