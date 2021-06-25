add_executable( TestTypeList testTypeList.cpp )
target_link_libraries( TestTypeList gtest gtest_main ${GTEST_LIBRARIES} pthread commonLib)
add_test( NAME TestTypeList COMMAND TestTypeList )

add_executable( TestSpecialTypeList testSpecialTypeList.cpp )
target_link_libraries( TestSpecialTypeList gtest gtest_main ${GTEST_LIBRARIES} pthread commonLib)
add_test( NAME TestSpecialTypeList COMMAND TestSpecialTypeList )

add_executable( TestGenScatterHierarchy testGenScatterHierarchy.cpp )
target_link_libraries(TestGenScatterHierarchy  gtest gtest_main ${GTEST_LIBRARIES} pthread commonLib)
add_test( NAME TestGenScatterHierarchy COMMAND TestGenScatterHierarchy )
