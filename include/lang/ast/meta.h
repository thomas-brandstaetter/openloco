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
    class class_info final {

    protected:

        /**
         * @return The class name of the ast object.
         */
        std::string class_name () const
        {
            const std::type_info& ti = typeid(decltype(this));
            const char *name = ti.name();

            char *res;
#ifdef HAVE_CXA_DEMANGLE
            char buf[1024];
            size_t size = sizeof(buf);
            int status;

            res = abi::__cxa_demangle(name, buf, &size, &status);
            buf[size - 1] = '\0';
#else
            res = const_cast<char *>(name);
#endif

            return res;
        }
    };

}}}}