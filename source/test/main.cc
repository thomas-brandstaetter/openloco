#include <iostream>

#include <driver.h>

int main() {

    mp::driver d;
    int result = d.parse(std::cin, std::cout);

    return result;
}