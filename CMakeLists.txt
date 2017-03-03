PROJECT(metlibs-pudatatypes)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8.11)

SET(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
INCLUDE(MetnoUtils)
INCLUDE(MetnoGTestUtils)

METNO_PVERSION_DEFINES(PUDATATYPES "src/puDatatypesVersion.h")

FIND_PACKAGE(Boost REQUIRED)

SET(lib_name "metlibs-pudatatypes")

METNO_GEN_PKGCONFIG(metlibs-pudatatypes.pc.in "${lib_name}.pc"
  "${PKGS}" "" "" "")

CONFIGURE_FILE(puDatatypes.pc.in puDatatypes.pc @ONLY)
INSTALL(FILES ${CMAKE_BINARY_DIR}/puDatatypes.pc DESTINATION "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}/pkgconfig")

ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(test)
