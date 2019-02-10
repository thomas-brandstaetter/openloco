#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>

#include <driver/driver.h>

#include <antlr-gen/olccLexer.h>
#include <antlr-gen/olccParser.h>
#include <antlr4-runtime.h>


namespace openloco {
namespace lang {


    int
    Driver::parse(std::istream &in, std::ostream &out)
    {
        antlr4::ANTLRInputStream is {in};
        olccLexer lexer {&is};
        antlr4::CommonTokenStream tokens {&lexer};

        tokens.fill();
        for (auto token : tokens.getTokens())
            std::cout << token->toString() << std::endl;
//        olccParser parser {&tokens};
//        parser.setBuildParseTree(true);
//
//        antlr4::tree::ParseTree *tree = parser.library_element_declaration();
//
//        std::cout << tree->toStringTree() << std::endl;

        return 0;
    }

    int
    Driver::parse(File& infile, std::ostream &out)
    {
        // openloco::lang::FileStreambuffer fsb { infile };
        // std::istream is { &fsb };
        return 1;
    }
}}
