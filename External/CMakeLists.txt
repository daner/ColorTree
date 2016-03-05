project(mongoose C)
file(GLOB MONGOOSE_SOURCES mongoose/mongoose.c
						   mongoose/mongoose.h)

add_library(mongoose STATIC ${MONGOOSE_SOURCES})
