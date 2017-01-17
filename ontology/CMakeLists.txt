cmake_minimum_required (VERSION 3.0)
project (ontology)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 11)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

add_executable(ontology ${SOURCES})
