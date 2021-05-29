
#include_directories(src/...)
add_subdirectory(Common)
add_library( dummyLib
        Dummy.cpp
        )

add_executable( main main.cpp )
target_link_libraries( main dummyLib commonLib)
