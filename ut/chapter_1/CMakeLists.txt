add_executable( TestCreatorPolicies testCreatorPolicies.cpp )
target_link_libraries( TestCreatorPolicies  gtest gtest_main ${GTEST_LIBRARIES} pthread commonLib)
add_test( NAME TestCreatorPolicies COMMAND TestCreatorPolicies )

add_executable( TestSmartPtr testSmartPtr.cpp )
target_link_libraries( TestSmartPtr  gtest gtest_main ${GTEST_LIBRARIES} pthread commonLib)
add_test( NAME TestSmartPtr COMMAND TestSmartPtr )
