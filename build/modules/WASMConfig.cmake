#######################################
# CMAKE INScore WASM library
#######################################
cmake_minimum_required(VERSION 3.4.0)

set (CMAKE_BUILD_TYPE Release)

option ( EMCCDEBUG		"Activate emcc debug information"	off )

get_filename_component(ROOT ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)
set (SRCDIR 	${ROOT}/src)
set (EMCCSRCDIR ${SRCDIR}/emcc)
set (INSCOREDIR ${SRCDIR}/inscore)
set (HTMLVIEWDIR ${SRCDIR}/view/HTMLView)

#######################################
# set wasm src, headers and definitions
file (GLOB WASM_SRC ${EMCCSRCDIR}/bindings/*.cpp 
					${EMCCSRCDIR}/faustweb/*.cpp 
					${HTMLVIEWDIR}/*.cpp)
file (GLOB WASM_HEADERS ${EMCCSRCDIR}/bindings/*.h  
					${EMCCSRCDIR}/faustweb/*.h 
					${HTMLVIEWDIR}/*.h)
set  (WASM_INCLUDE_DIRS 
		${EMCCSRCDIR}/bindings
		${EMCCSRCDIR}/faustweb
		${INSCOREDIR}/osc
		${HTMLVIEWDIR}
)
set  (WASM_DEFINITIONS -DEMCC -DHTMLVIEW -DNO_OSCSTREAM ${EMCCDEBUGOPTION})

#######################################
# set emcc compiler and options
set ( HAVE_FLAG_SEARCH_PATHS_FIRST 0)
set ( CMAKE_CXX_STANDARD 11)
set ( CMAKE_OSX_DEPLOYMENT_TARGET	"")
set ( CMAKE_OSX_SYSROOT 		"")
set ( CMAKE_CXX_COMPILER 	"emcc")
set ( CMAKE_CXX_LINK_FLAGS "")
set ( WASM_LINK_FLAGS "--bind -O3 --memory-init-file 0 -s LINKABLE=1 -s WASM=1 -s EXPORT_NAME=\"'INScoreModule'\" -s MODULARIZE=1 -s ASSERTIONS=1 -s ALLOW_MEMORY_GROWTH=1 -s DISABLE_EXCEPTION_CATCHING=1  -s EXTRA_EXPORTED_RUNTIME_METHODS='[\"UTF8ToString\"]'")

if (EMCCDEBUG)
	set (WASM_COMPILE_FLAGS "-s ASSERTIONS=1 -s SAFE_HEAP=1 -s STACK_OVERFLOW_CHECK=1 -s DEMANGLE_SUPPORT=1")
	message (STATUS "EMCC Debug options are on")
else()
	set (WASM_COMPILE_FLAGS -O3)
endif()
