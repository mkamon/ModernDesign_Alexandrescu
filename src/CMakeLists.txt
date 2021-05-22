
#include_directories(src/...)
add_library( dummyLib
        Dummy.cpp
        )

add_executable( main main.cpp )
target_link_libraries( main dummyLib gtest gtest_main ${GTEST_LIBRARIES} pthread)
