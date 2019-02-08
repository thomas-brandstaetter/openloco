#pragma once
/**
 * @author Thomas Brandstätter
 * @date 03.06.18
 */

#include <cxxabi.h>
#include <sstream>
#include <string>
#include <typeinfo>


namespace openloco {
namespace lang {
namespace ast {
namespace meta {

    /**
     * class_info
     *
     * Provide meta information about the ast object, in order to improve introspection capabilities at runtime.
     *
     *
     * Provided informations are
     *  - class_name
     */
    class ClassInfo final {

    protected:

        /**
         * @return The class name of the ast object.
         */
        std::string className () const
        {
            const std::type_info& ti = typeid(decltype(this));
            const char *name = ti.name();

            char *className;
#ifdef HAVE_CXA_DEMANGLE
            char buf[1024];
            size_t size = sizeof(buf);
            int status;

            className = abi::__cxa_demangle(name, buf, &size, &status);
            if (size > 1024)
            {
                size = 1024;
            }
            buf[size - 1] = '\0';
#else
            className = const_cast<char *>(name);
#endif

            return className;
        }
    };

}}}}
