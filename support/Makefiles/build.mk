DEBUG_DIR=/build/debug
CC=/opt/local/bin/clang-mp-6.0
CXX=/opt/local/bin/clang++-mp-6.0
CMAKE_PREFIX_PATH=/opt/local:/opt/local/libexec/llvm-6.0
CMAKE_FLAGS="-DCMAKE_PREFIX_PATH=$(CMAKE_PREFIX_PATH)"

debug:
	mkdir -p build/debug
	cd build/debug && CC=$(CC) CXX=$(CXX) cmake $(CMAKE_FLAGS) -DCMAKE_BUILD_TYPE=DEBUG -GNinja ../.. && ninja

release:
	mkdir -p build/release
	cd build/release && CC=$(CC) CXX=$(CXX) cmake -DCMAKE_PREFIX_PATH=$(CMAKE_PREFIX_PATH) -DCMAKE_BUILD_TYPE=RELEASE -GNinja ../.. && ninja

compilecommands:
	mkdir -p build/debug
	cd build/debug && CC=$(CC) CXX=$(CC) cmake -DCMAKE_PREFIX_PATH=$(CMAKE_PREFIX_PATH) -DCMAKE_BUILD_TYPE=DEBUG -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ../..
	mv build/debug/compile_commands.json support/

clean-debug:
	rm -rf build/debug/*

clean-release:
	rm -rf build/release/*