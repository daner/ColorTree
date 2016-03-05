project(jsoncpp CXX)
file(GLOB JSONCPP_SOURCES jsoncpp.cpp 
						  json/json.h
						  json/json-forwards.h)

add_library(jsoncpp STATIC ${JSONCPP_SOURCES})
set_target_properties(jsoncpp PROPERTIES FOLDER "External")