# CMakeLists.txt --- CMake project settings
#    ex) cmake -G "Visual Studio 9 2008"
#    ex) cmake -DCMAKE_BUILD_TYPE=Release -G "MSYS Makefiles"
##############################################################################

# CMake minimum version
cmake_minimum_required(VERSION 2.4)

# project name and language
project(MyProject CXX)

# libTypeSystem.a
add_library(TypeSystem STATIC TypeSystem.cpp Misc.cpp)
