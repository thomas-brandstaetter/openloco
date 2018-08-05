BUILD_DIR=build/coverage

#CMAKE_FLAGS=-DCMAKE_C_COMPILER=/opt/local/bin/gcc-mp-7 -DCMAKE_CXX_COMPILER=/opt/local/bin/g++-mp-7 -DCMAKE_BUILD_TYPE=COVERAGE
#CMAKE_FLAGS=-DCMAKE_VERBOSE_MAKEFILE:BOOL=ON -DCMAKE_C_COMPILER=/opt/local/bin/gcc-mp-7 -DCMAKE_CXX_COMPILER=/opt/local/bin/g++-mp-7 -DCMAKE_BUILD_TYPE=COVERAGE

cov: coverage

coverage:
	mkdir -p build/coverage
	cd build/coverage &&  -DCMAKE_BUILD_TYPE=COVERAGE ../.. && cmake --build

