
INCLUDE_DIRECTORIES(${BOOST_INCLUDE_DIRS})
ADD_DEFINITIONS(-W -Wall)
LINK_DIRECTORIES(${BOOST_LIBRARY_DIRS})

METNO_FIND_GTEST()

INCLUDE_DIRECTORIES(
  "${CMAKE_SOURCE_DIR}/src"
)

ADD_EXECUTABLE(pudatatypes_test
  MiCoordinatesTest.cc
)

TARGET_LINK_LIBRARIES(pudatatypes_test
  pudatatypes
  ${GTEST_LIBRARY}
  ${GTEST_MAIN_LIBRARY}
  Threads::Threads
)

ADD_TEST(NAME pudatatypes_test
  COMMAND pudatatypes_test --gtest_color=yes
)
