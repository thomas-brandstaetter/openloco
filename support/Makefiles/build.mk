DEBUG_DIR=/build/debug


debug:
	mkdir -p build/debug
	cd build/debug && cmake -DCMAKE_BUILD_TYPE=DEBUG -GNinja ../.. && ninja

release:
	mkdir -p build/release
	cd build/release && cmake -DCMAKE_BUILD_TYPE=RELEASE -GNinja ../.. && ninja

compilecommands:
	mkdir -p build/debug
	cd build/debug && $(SET_CXX) cmake -DCMAKE_BUILD_TYPE=DEBUG  $(SET_CM_CXX) -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ../..
	mv build/debug/compile_commands.json support/
