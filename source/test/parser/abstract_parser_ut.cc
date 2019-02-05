#pragma once


#include <ostream>

#include <gtest/gtest.h>

#include <lang/driver.h>
#include <parser.hh>
#include <lang/scanner.h>


class abstract_parser_ut : public ::testing::Test {
protected:
    abstract_parser_ut() { }
    virtual ~abstract_parser_ut() { }

    void TearDown() { }

    class openloco::lang::driver driver;
    std::stringstream input;
};