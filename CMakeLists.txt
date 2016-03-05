cmake_minimum_required(VERSION 3.0)

add_subdirectory(External)

project(ColorTree)

file(GLOB_RECURSE ALL_SOURCES Source/*.h Source/*.cpp)

add_executable(colortree ${ALL_SOURCES})
target_link_libraries(colortree mongoose)


