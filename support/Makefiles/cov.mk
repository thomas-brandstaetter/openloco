BUILD_DIR=build/coverage

coverage:
	mkdir -p build/coverage
	cd build/coverage && \
	C=gcc  cmake -DCMAKE_C_COMPILER=/opt/local/bin/gcc-mp-7 -DCMAKE_CXX_COMPILER=/opt/local/bin/g++-mp-7 -DCMAKE_BUILD_TYPE=COVERAGE  ../.. -GNinja && ninja

