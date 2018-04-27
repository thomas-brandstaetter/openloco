test: debug
	cd build/debug/ && ctest

memcheck: debug
	cd build/debug/ && ctest -T


experimental: debug
	cd build/debug/ && ctest -D Experimental

nightly: debug
	cd build/debug/ && ctest -D Nightly

.PHONY: test memcheck experimental nightly
