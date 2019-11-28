# CMakeList.txt : CMake project for RechOP, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)


project(RechOP)

add_subdirectory(parseur)
# Add source to this project's executable
add_executable (RechOP "RechOP.cpp" "RechOP.h" "parseur/parseur.cpp")

# TODO: Add tests and install targets if needed.
