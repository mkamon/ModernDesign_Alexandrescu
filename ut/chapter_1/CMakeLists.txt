add_executable( TestCreatorPolicies testCreatorPolicies.cpp )
target_link_libraries( TestCreatorPolicies  gtest gtest_main ${GTEST_LIBRARIES} pthread commonLib)
add_test( NAME TestCreatorPolicies COMMAND TestCreatorPolicies )
