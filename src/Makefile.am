lib_LTLIBRARIES = libpuDatatypes.la

libpuDatatypes_la_SOURCES=\
	miCoordinates.cc\
	miLine.cc  \
	miPosition.cc\
	miRegions.cc

libpuDatatypes_la_CXXFLAGS = ${parameter_CFLAGS} ${puTools_CFLAGS}
libpuDatatypes_la_LDFLAGS = ${parameter_LIBS} ${puTools_LIBS} ${VERSION_INFO}

INSTALL=install -p # tells install to preserve timestamp
DEFAULT_INCLUDES=-I${srcdir}/../include
