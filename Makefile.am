# $Id$

pkgname = puDatatypes

include $(top_srcdir)/metlibs.mk

lib_LTLIBRARIES = libpuDatatypes.la

libpuDatatypes_la_SOURCES = \
	miCoordinates.cc \
	miLine.cc  \
	miPosition.cc \
	miRegions.cc

libpuDatatypes_la_CPPFLAGS = \
	${PARAMETER_CPPFLAGS} \
	${PUTOOLS_CPPFLAGS}

libpuDatatypes_la_LDFLAGS = ${VERSION_INFO}
if ENABLE_SHARED_LIBRARY
libpuDatatypes_la_LDFLAGS += \
	${PARAMETER_LDFLAGS} \
	${PUTOOLS_LDFLAGS}
libpuDatatypes_la_LIBADD = \
	${PARAMETER_LIBS} \
	${PUTOOLS_LIBS}
endif

pkg_includedir = ${includedir}/puDatatypes

pkg_include_HEADERS = \
	miCoordinates.h\
	miLine.h  \
	miParameter.h  \
	miPosition.h  \
	miRegions.h  \
	tsData.h  \
	tsFunctions.h

