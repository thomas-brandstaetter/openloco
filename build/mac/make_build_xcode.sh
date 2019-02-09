#!/bin/bash

CC=/opt/local/bin/clang
CXX=/opt/local/bin/clang++

echo $CC
echo $CXX

CMAKE_PREFIX_PATH=/opt/local
CMAKE_FLAGS="-DCMAKE_PREFIX_PATH=$CMAKE_PREFIX_PATH -DCMAKE_XCODE_ATTRIBUTE_C_COMPILER=$CC -DCMAKE_XCODE_ATTRIBUTE_CXX_COMPILER=$CXX -DCMAKE_C_COMPILER=$CC -DCMAKE_CXX_COMPILER=$CXX"

PWD=$(pwd)
echo "PWD: $PWD"
echo "$CMAKE_FLAGS"

mkdir -p $PWD/../build_mac_xcode
cd $PWD/../build_mac_xcode

cmake $CMAKE_FLAGS -GXcode ../openloco/
