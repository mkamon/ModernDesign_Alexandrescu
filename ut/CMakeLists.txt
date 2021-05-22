enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
add_definitions( "-Wall -pthread -std=c++17 -g" )

include_directories(${CMAKE_SOURCE_DIR}/src)

add_executable( test testMain.cpp )
target_link_libraries( test dummyLib gtest gtest_main ${GTEST_LIBRARIES} pthread)
add_test( test test )
