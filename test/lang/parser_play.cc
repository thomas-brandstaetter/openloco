#include <lang/driver.h>

#include <fstream>
#include <iostream>
#include <string>

int
main(int argc, char** argv) {

    if (argc > 2)
        exit(EXIT_FAILURE);

    openloco::lang::driver d;
    int result;

    if (argc == 2) {
        std::ifstream file { argv[1] };
        assert(file.is_open());
        result = d.parse(file);
    }
    else { result = d.parse(); }

    return result;
}
