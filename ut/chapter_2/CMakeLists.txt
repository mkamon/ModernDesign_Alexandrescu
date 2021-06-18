add_executable( TestCompileTimeAssert testCTAssert.cpp )
target_link_libraries( TestCompileTimeAssert  gtest gtest_main ${GTEST_LIBRARIES} pthread commonLib)
add_test( NAME TestCompileTimeAssert COMMAND TestCompileTimeAssert )

add_executable( TestMapToType testMapToType.cpp )
target_link_libraries( TestMapToType gtest gtest_main ${GTEST_LIBRARIES} pthread commonLib)
add_test( NAME TestMapToType COMMAND TestMapToType )

add_executable( TestConvertibility testConversion.cpp )
target_link_libraries( TestConvertibility gtest gtest_main ${GTEST_LIBRARIES} pthread commonLib)
add_test( NAME TestConvertibility COMMAND TestConvertibility )

add_executable( TestTypeTraits testTypeTraits.cpp )
target_link_libraries( TestTypeTraits gtest gtest_main ${GTEST_LIBRARIES} pthread commonLib)
add_test( NAME TestTypeTraits COMMAND TestTypeTraits )
