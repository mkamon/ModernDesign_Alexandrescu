enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
add_definitions( "-Wall -pthread -std=c++17 -g" )

include_directories(src/...)
add_library( ..._lib
        src/....cpp
        )

add_executable( test testSource.cpp )
target_link_libraries( test ..._lib gtest gtest_main ${GTEST_LIBRARIES} pthread)
add_test( test test )
