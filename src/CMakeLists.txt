
INCLUDE_DIRECTORIES(${BOOST_INCLUDE_DIRS})
ADD_DEFINITIONS(-W -Wall)
LINK_DIRECTORIES(${BOOST_LIBRARY_DIRS})

########################################################################

SET(pudatatypes_SOURCES
  miCoordinates.cc
  miLine.cc 
  miPosition.cc
  miRegions.cc
)

METNO_HEADERS (pudatatypes_HEADERS pudatatypes_SOURCES ".cc" ".h")
LIST(APPEND pudatatypes_HEADERS
  puDatatypesVersion.h
)

########################################################################

ADD_LIBRARY(pudatatypes SHARED
  ${pudatatypes_SOURCES}
)

SET_TARGET_PROPERTIES(pudatatypes PROPERTIES
  VERSION ${PUDATATYPES_PVERSION_FULL}
  SOVERSION "${PUDATATYPES_VERSION_MAJOR}"
  OUTPUT_NAME "${lib_name}"
)

TARGET_LINK_LIBRARIES(pudatatypes
  ${BOOST_LIBRARIES}
)

INSTALL(TARGETS pudatatypes
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

INSTALL(FILES ${pudatatypes_HEADERS}
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/metlibs/puDatatypes
)
