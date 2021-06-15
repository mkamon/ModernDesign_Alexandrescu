add_executable( TestCompileTimeAssert testCTAssert.cpp )
target_link_libraries( TestCompileTimeAssert  gtest gtest_main ${GTEST_LIBRARIES} pthread commonLib)
add_test( NAME TestCompileTimeAssert COMMAND TestCompileTimeAssert )

add_executable( TestMapToType testMapToType.cpp )
target_link_libraries( TestMapToType gtest gtest_main ${GTEST_LIBRARIES} pthread commonLib)
add_test( NAME TestMapToType COMMAND TestMapToType )
