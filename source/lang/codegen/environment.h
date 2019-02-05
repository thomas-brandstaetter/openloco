#pragma once
//
// Created by Thomas Brandstätter on 02/08/2018.
//


#include <map>
#include <string>

class Environment
{

    const std::string &lookup(std::string variable_name) const;

private:
    std::map<std::string, std::string> variables;

};
