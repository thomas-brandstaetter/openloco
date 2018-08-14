XCODE_DEBUG_DIR=build/xcode-debug


xcode:
	mkdir -p $(XCODE_DEBUG_DIR)
	cd $(XCODE_DEBUG_DIR) && CC=$(CC) CXX=$(CXX) cmake -DCMAKE_BUILD_TYPE=DEBUG -G "Xcode" ../..

xo:
	open $(XCODE_DEBUG_DIR)/openloco.xcodeproj


clean-xcode:
	rm -rf build/xcode-debug/*