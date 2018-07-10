#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <ast/ast.h>

#include <driver/file.h>


/**
 * .rst
 * ``
 *                          ┌────────────────┐
 *                          │    <facade>    │
 *                          │     driver     │
 *                          └────────────────┘
 *                              │         │
 *                              │         │
 *                        ┌─────┘         └───┐
 *                        |                   │
 * ┌─────────┐      ┌────────────┐      ┌─────────────┐
 * │   ast   │------│   parser   │------│   scanner   │
 * └─────────┘      └────────────┘      └─────────────┘
 *      |                  |                    |
 *      |                  |                    |
 *      |                  |                    |
 *      |                  |                    |
 * ┌─────────────┐    ┌───────────┐        ┌──────────┐      ┌────────────────────────┐
 * │   codegen   │    │   error   │────────│   file   │──────│   file_stream_buffer   │
 * └─────────────┘    └───────────┘        └──────────┘      └────────────────────────┘
 *``
 */

namespace openloco {
namespace lang {

    class parser;

    class driver {
    public:

        /** \addtogroup Object lifecycle */
        /** @{ */
        driver() :
            _tokens(),
            _debug(false),
            _current_file(nullptr)
        {
        }

        virtual ~driver()
        {
        }

        /** @} */

        /** \addtogroup Parsing */
        /** @{ */

        int parse(std::istream& in, std::ostream& out = std::cout);
        int parse(file& infile, std::ostream& out = std::cout);

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
        file* _current_file;
        bool _debug;

        ast::root _ast_root;
    };
}}
