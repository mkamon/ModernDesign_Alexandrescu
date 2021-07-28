
add_executable( TestFunctor testFunctor.cpp )
target_link_libraries(TestFunctor gtest gtest_main ${GTEST_LIBRARIES} pthread commonLib)
add_test( NAME TestFunctor COMMAND TestFunctor )
