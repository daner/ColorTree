project(mongoose C)
file(GLOB MONGOOSE_SOURCES mongoose.c
						   mongoose.h)

add_definitions(/wd4273 /wd4996 /wd4267 /wd4244 /wd4013 /wd4311)
add_library(mongoose STATIC ${MONGOOSE_SOURCES})
set_target_properties(mongoose PROPERTIES FOLDER "External")