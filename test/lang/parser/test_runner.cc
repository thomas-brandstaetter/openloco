/**
 * @author Thomas Brandstätter 
 * @date 15.04.18.
 */

#include <driver/driver.h>
#include <driver/file.h>

#include <cassert>
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
main(int argc, char** argv)
{

    program_name = argv[0];
    if (argc != 2) {
        synopsis();
        exit(1);
    }

    openloco::lang::driver driver;
    std::string filename {argv[1]};
    int desired_result = get_desired_result(filename);
    int result;

    std::ifstream file {argv[1]};
    if (!file.is_open()) {
        std::cerr << "File not found: " << filename;
        exit(3);
    }

    openloco::lang::file f;
    f.open(file);
    result = driver.parse(f);

    return (result == desired_result) ? 0 : 1;
}

void
synopsis() {
    std::cerr
        << "SYNOPSIS\n"
        << program_name << " <filename>.<desired-result>\n"
        << "\n"
        << "desired-result: return code the program ends with" << std::endl;
}


int
get_desired_result(std::string& filename) {
    char last_char = filename.back();
    return static_cast<int>(last_char - '0');
}
