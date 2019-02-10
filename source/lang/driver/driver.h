#pragma once
/**
 * @author Thomas Brandstaetter
 * @date 14.02.2018
 */


#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <ast/ast.h>

#include <driver/file.h>



namespace openloco {
namespace lang {

    class Driver {
    public:

        /** \addtogroup Object lifecycle */
        /** @{ */
        Driver() :
            _tokens(),
            _current_file(nullptr),
            _debug(false)
        {
        }

        virtual ~Driver()
        {
        }

        /** @} */

        /** \addtogroup Parsing */
        /** @{ */

        int parse(std::istream& in, std::ostream& out = std::cout);
        int parse(File& infile, std::ostream& out = std::cout);

        /** @} */

        void setDebug(bool value) { _debug = value; }


    private:

        std::vector<std::string> _tokens;
        File* _current_file;
        bool _debug;

        ast::root _ast_root;
    };
}}
