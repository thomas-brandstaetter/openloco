
SET_CXX=CXX=/opt/local/bin/clang++
SET_CM_CXX=-DCMAKE_CXX_COMPILER=/opt/local/bin/clang++


include support/Makefiles/os.mk
include support/Makefiles/build.mk
include support/Makefiles/cov.mk
include support/Makefiles/clean.mk
include support/Makefiles/test.mk