find_package( GTest REQUIRED )
include_directories(${GTEST_INCLUDE_DIRS})

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/src/Common)
include_directories(${CMAKE_SOURCE_DIR}/src/byBook)

add_subdirectory(chapter_1)

add_executable( testMain testMain.cpp )
target_link_libraries( testMain  gtest gtest_main ${GTEST_LIBRARIES} pthread dummyLib)
add_test( NAME testMain COMMAND testMain )
