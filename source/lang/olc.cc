#include <src/lang/driver/driver.h>

#include <fstream>
#include <iostream>
#include <string>

int
main(int argc, char** argv) {

    openloco::lang::driver d;
    int result;

    if (argc == 2) {
        std::ifstream file { argv[1] };
        if (!file.is_open()) {
            std::cerr << "file: " << argv[1] << " could not be opened." << std::endl;
            return 3;
        }

        result = d.parse(file);
    }
    else { result = d.parse(); }

    return result;
}
