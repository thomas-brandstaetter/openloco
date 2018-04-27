#include <lang/driver.h>
#include <lang/scanner.h>

int
main(int, char**) {

    openloco::lang::driver d;
    openloco::lang::scanner s(d);

    openloco::lang::parser::symbol_type result = s.yylex(d);

    return 0;
}
