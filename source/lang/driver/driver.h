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

    class parser;

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

        void set_debug(bool value) { _debug = value; }

        /** /addgroup Gathering */
        /** @{ */

        /**
         * Build a pushdown automaton while parsing.
         *
         * @details Needs invocation in the parser code.
         *
         * @param token The token to add.
         */
        void add_token(std::string token);

        void set_root(ast::root root)   { _ast_root = root; }
        ast::root& get_root()           { return _ast_root; }
        /** @} */

        friend class parser;
        friend class scanner;

    private:

        std::vector<std::string> _tokens;
        File* _current_file;
        bool _debug;

        ast::root _ast_root;
    };
}}
