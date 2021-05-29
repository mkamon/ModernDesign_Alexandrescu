cmake_minimum_required (VERSION 3.0)
project( ModernDesign_AAlexandrescu )

add_definitions( "-Wall -pthread -std=c++17 -g" )
add_subdirectory(src)

enable_testing()
include(CTest)
add_subdirectory(ut)
