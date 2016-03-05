cmake_minimum_required(VERSION 3.0)

project(ColorTree CXX)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(COLORTREE_DIR ${PROJECT_SOURCE_DIR})
set(COLORTREE_EXTERNAL_DIR ${COLORTREE_DIR}/External)

include_directories(${COLORTREE_EXTERNAL_DIR}/mongoose)
include_directories(${COLORTREE_EXTERNAL_DIR}/jsoncpp)

file(GLOB_RECURSE ALL_SOURCES Source/*.h 
							  Source/*.cpp
							  Source/*.c)

							  						  
add_executable(colortree ${ALL_SOURCES})
target_link_libraries(colortree mongoose jsoncpp)


add_subdirectory(External)
