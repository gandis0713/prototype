GOOGLETEST_DIR = C:/googletest-master

GTEST_SRCDIR = $$GOOGLETEST_DIR/googletest
GMOCK_SRCDIR = $$GOOGLETEST_DIR/googlemock

INCLUDEPATH *= \
    $$GTEST_SRCDIR \
    $$GTEST_SRCDIR/include \
    $$GMOCK_SRCDIR \
    $$GMOCK_SRCDIR/include

SOURCES += \
    $$GTEST_SRCDIR/src/gtest-all.cc \
    $$GMOCK_SRCDIR/src/gmock-all.cc
