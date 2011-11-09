#######################################
# CMAKE for lua
# D. Fober <fober@grame.fr>
#######################################

project(lua)
cmake_minimum_required(VERSION 2.6)

if(WIN32)
	add_definitions(-DWINVER=0x0500)
	add_definitions(-D_CRT_SECURE_NO_DEPRECATE)
else(WIN32)
	add_definitions(-Wall -fPIC)
	set(LIBS -lm)
endif(WIN32)

if(APPLE)
	set (CMAKE_OSX_ARCHITECTURES "x86_64 i386")
	set(CMAKE_OSX_SYSROOT /Developer/SDKs/MacOSX10.5.sdk)
	set(CMAKE_C++_FLAGS -mmacosx-version-min=10.4)
endif(APPLE)

#######################################
# SET MAIN DIRECTORY.
set(SRC ${CMAKE_CURRENT_SOURCE_DIR}/../src)

# SET INCLUDES
#include_directories( .. )

# SET SOURCES
FILE(GLOB LUA_SRC "${SRC}/l[^u]*.c" "${SRC}/print.c" "${SRC}/lundump.c")

#######################################
ADD_LIBRARY( lua STATIC ${LUA_SRC} )
target_link_libraries( lua ${LIBS})
set_target_properties (lua PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${SRC})

#######################################
add_executable( mlua  ${SRC}/lua.c )
target_link_libraries( mlua lua)
add_dependencies(mlua lua)
set_target_properties (mlua PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${SRC}  OUTPUT_NAME lua )

add_executable( luac  ${SRC}/luac.c )
target_link_libraries( luac lua)
add_dependencies(luac lua)
set_target_properties (luac PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${SRC})
