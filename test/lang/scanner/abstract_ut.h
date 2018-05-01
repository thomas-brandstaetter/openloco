#pragma once

#include <sstream>
#include <iostream>

#include <gtest/gtest.h>

#include <driver/driver.h>
#include <scanner/scanner.h>

#include <parser.hh>


class abstract_scanner_ut : public ::testing::Test {
protected:
    abstract_scanner_ut() : scanner(this->driver) {
        scanner.set_debug(1);
    }
    virtual ~abstract_scanner_ut() { }

    class openloco::lang::driver driver;
    class openloco::lang::scanner scanner;
    std::stringstream input;
};


