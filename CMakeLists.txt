cmake_minimum_required(VERSION 3.0)

add_subdirectory(External)

project(ColorTree CXX)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(COLORTREE_DIR ${PROJECT_SOURCE_DIR})
set(COLORTREE_EXTERNAL_DIR ${COLORTREE_DIR}/External)

include_directories(${COLORTREE_EXTERNAL_DIR}/mongoose)
include_directories(${COLORTREE_EXTERNAL_DIR}/jsoncpp)
include_directories(${COLORTREE_EXTERNAL_DIR}/glm/include)
include_directories(${COLORTREE_EXTERNAL_DIR}/glew/include)
include_directories(${COLORTREE_EXTERNAL_DIR}/glfw/include)

file(GLOB_RECURSE SHADERS Resources/Shaders/*)
file(GLOB_RECURSE WEB Resources/Web/*)

file(GLOB_RECURSE ALL_SOURCES Source/*.h Source/*.cpp)

source_group("Source" FILES ${ALL_SOURCES})
source_group(Resources\\Shaders FILES ${SHADERS})
source_group(Resources\\Web FILES ${WEB})					  					
			
add_definitions(-DGLEW_STATIC)
										
add_executable(colortree ${ALL_SOURCES} ${WEB} ${SHADERS})
target_link_libraries(colortree glew mongoose jsoncpp glfw opengl32.lib)

add_custom_target(COPY ALL COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/Resources $<TARGET_FILE_DIR:colortree>/Resources)

