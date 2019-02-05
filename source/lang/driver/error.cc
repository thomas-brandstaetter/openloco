/**
 * @author Thomas Brandstätter 
 * @date 29.04.18.
 */

#include <algorithm>
#include <string>
#include <sstream>
#include <vector>

#include <driver/error.h>


namespace openloco {
namespace lang {

    const std::vector<std::string> Error::error_messages = {
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
        "Same identifier used as connector label and element name", "Uninitialized feedback variable"
    };

    const std::vector<std::string> Error::error_subclauses = {
        "0", "1", "2.1.5", "2.3.3.1", "2.3.3.1", "2.4.1.1", "2.4.3", "2.4.3", "2.5.1", "2.5.1.1", "2.5.1.1",
        "2.5.1.5.1", "2.5.1.5.2", "2.5.1.5.2", "2.5.1.5.3", "2.5.1.5.4", "2.5.1.5.4", "2.5.1.5.5", "2.5.1.5.5",
        "2.5.1.5.5", "2.5.1.5.6", "2.5.2.2", "2.5.2.2", "2.6.2", "2.6.2", "2.6.2", "2.6.2", "2.6.3", "2.6.4.5",
        "2.6.5", "2.6.5", "2.6.5", "2.7.1", "2.7.2", "3.2.2", "3.2.2", "3.3.1", "3.3.1", "3.3.1", "3.3.2.1",
        "3.3.2.4", "4.1.1", "4.1.3"
    };


    Error
    Error::make_error(error_type type, class File& file)
    {
        Error error {file};

        error._type = type;
        std::vector<std::string>::size_type idx = static_cast<std::vector<std::string>::size_type>(type);
        error._message = error_messages[idx];
        error._subclass = error_subclauses[idx];

        return error;
    }

    Error
    Error::make_scanner_error(std::string &message, class File& file)
    {
        return std::move(make_custom_error(message, file));
    };

    Error
    Error::make_custom_error(std::string &message, class File& file)
    {
        Error error {file};
        error_type type = Error::error_type::E_custom;
        std::vector<std::string>::size_type idx = static_cast<std::vector<std::string>::size_type>(type);

        error._type = type;
        error._subclass = Error::error_subclauses[idx];
        error._message = error_messages[idx];

        return error;
    }

    void
    Error::print(std::ostream& os)
    {
        std::stringstream ss;

        int error_number = static_cast<int>(_type);

        ss << "E." << error_number
           << " [" << Error::error_subclauses[error_number] << "]: "
           << Error::error_messages[error_number]
           << " at: " << "_loc" << "\n\n";


//        const unsigned int
//            begin_ln = _loc.begin.line,
//            end_ln = _loc.end.line,
//            begin_col = _loc.begin.column - 1,
//            end_col = _loc.end.column -1,
//            width = std::max<unsigned int>(end_col - begin_col, 1); // show at least one '^'

        /*
         * suppose begin_ln <= end_ln invariant
         */

//        File::LineNumber cur_ln = begin_ln;
//        do {
//            ss << _file.get_line(cur_ln)
//               << std::string(begin_col, ' ')
//               << std::string(width, '^');
//
//            cur_ln++;
//        } while (cur_ln < end_ln);

        ss << "\n\n";

        os << ss.str();
    }
}}
