CC=/opt/local/bin/clang
CXX=/opt/local/bin/clang
CMAKE_PREFIX_PATH=/opt/local
CMAKE_FLAGS="-DCMAKE_PREFIX_PATH=$(CMAKE_PREFIX_PATH)"

debug:
	mkdir -p build/debug && \
		cd build/debug && \
		cmake $(CMAKE_FLAGS) -DCMAKE_C_COMPILER=$(CC) -DCMAKE_CXX_COMPILER=$(CXX)  -DCMAKE_BUILD_TYPE=DEBUG -GNinja ../.. && \
		cmake --build .

release:
	mkdir -p build/release && \
		cd build/release && \
		cmake -DCMAKE_PREFIX_PATH=$(CMAKE_PREFIX_PATH) -DCMAKE_C_COMPILER=$(CC) -DCMAKE_CXX_COMPILER=$(CXX)  -DCMAKE_BUILD_TYPE=RELEASE -GNinja ../.. && \
		cmake --build .

compilecommands:
	mkdir -p build/debug
	cd build/debug && \
		cmake -DCMAKE_PREFIX_PATH=$(CMAKE_PREFIX_PATH) -DCMAKE_C_COMPILER=$(CC) -DCMAKE_CXX_COMPILER=$(CXX) -DCMAKE_BUILD_TYPE=DEBUG -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ../..
	mv build/debug/compile_commands.json support/

clean-debug:
	rm -rf build/debug/*

clean-release:
	rm -rf build/release/*
