pkglib_LTLIBRARIES = libpudatatypes.la

libpudatatypes_la_SOURCES=\
	miCoordinates.cc\
	miLine.cc  \
	miPosition.cc\
	miRegions.cc

libpudatatypes_la_CXXFLAGS = ${parameter_CFLAGS} ${puTools_CFLAGS}
libpudatatypes_la_LDFLAGS = ${parameter_LIBS} ${puTools_LIBS} ${VERSION_INFO}

INSTALL=install -p # tells install to preserve timestamp
