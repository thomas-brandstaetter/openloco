
clean:
	rm -rf build/*

clean-win:
	cd build\msvs-debug && del /S /Q /F *
