DEBUG_DIR=/build/debug

build_dirs:
	mkdir -p build/debug
	mkdir -p build/coverage
	mkdir -p build/xcode-debug
	mkdir -p build/msvs-debug

debug: build_dirs
	cd build/debug && $(SET_CXX) cmake -DCMAKE_BUILD_TYPE=DEBUG  $(SET_CM_CXX) ../.. && make

release: build_dirs
	cd build/release && $(SET_CXX) cmake -DCMAKE_BUILD_TYPE=RELEASE  $(SET_CM_CXX) ../.. && make



compilecommands: build_dirs
	cd build/debug && $(SET_CXX) cmake -DCMAKE_BUILD_TYPE=DEBUG  $(SET_CM_CXX) -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ../..
	mv build/debug/compile_commands.json support/
