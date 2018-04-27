/**
 * @author Thomas Brandstätter 
 * @date 15.04.18.
 */

#include <lang/driver.h>

#include <fstream>
#include <iostream>
#include <string>

static int
get_desired_result(std::string& filename);

static void
synopsis();

static
char *program_name;

int
main(int argc, char** argv) {

    program_name = argv[0];
    if (argc != 2 ) {
        synopsis();
        exit(EXIT_FAILURE);
    }


    openloco::lang::driver d;
    std::string filename { argv[1] };
    int desired_result = get_desired_result(filename);
    int result;

    std::ifstream file { argv[1] };
    assert(file.is_open());
    result = d.parse(file);

    return (result == desired_result) ? EXIT_SUCCESS : EXIT_FAILURE;
}

void
synopsis() {
    std::cerr
        << "Synopsis\n"
        << program_name << " <test_file>"
        << std::endl;
}


int
get_desired_result(std::string& filename) {
    char last_char = filename.back();
    return static_cast<int>(last_char - '0');
}