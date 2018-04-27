XCODE_DEBUG_DIR=/build/xcode-debug


xcode: build_dirs
	cd $(XCODE_DEBUG_DIR) && $(SET_CXX) cmake -DCMAKE_BUILD_TYPE=DEBUG  $(SET_CM_CXX) -G "Xcode" ../..

xo:
	open $(XCODE_DEBUG_DIR)/openloco.xcodeproj
