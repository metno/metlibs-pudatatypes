
TESTS = puDatatypesTest

check_PROGRAMS = puDatatypesTest

puDatatypesTest_SOURCES = \
    MiCoordinatesTest.cc
puDatatypesTest_LDFLAGS =
puDatatypesTest_CPPFLAGS = \
    $(AM_CPPFLAGS) -I$(top_srcdir) -DTOP_SRCDIR=\"$(top_srcdir)\" \
    $(gtest_CFLAGS)

puDatatypesTest_req_libs = $(top_builddir)/puDatatypes/libpuDatatypes.la \
    $(top_builddir)/puTools/libpuTools.la \
    $(top_builddir)/puCtools/libpuCtools.la

puDatatypesTest_LDADD = \
    -lgtest_main \
    $(puDatatypesTest_req_libs) \
    -lproj -lboost_date_time -llog4cpp -lpthread \
    $(gtest_LIBS)

puDatatypesTest_DEPENDENCIES = $(puDatatypesTest_req_libs)
