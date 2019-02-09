#!/bin/bash

CC=/opt/local/bin/clang
CXX=/opt/local/bin/clang++
echo "$PWD/../"
cd $PWD/../build_mac_xcode
cmake --build .
