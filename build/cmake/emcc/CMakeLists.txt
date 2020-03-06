cmake_minimum_required(VERSION 3.4.0)
project (inscoreemcc)

set ( CMAKE_OSX_DEPLOYMENT_TARGET	"")
set ( CMAKE_OSX_SYSROOT 		"")
set ( CMAKE_CXX_COMPILER 	"emcc")

option ( EMCCDEBUG		"Activate emcc debug information"	off )
if (EMCCDEBUG)
	set (EMCC_COMPILE_OPTION "-s ASSERTIONS=1 -s SAFE_HEAP=1 -s STACK_OVERFLOW_CHECK=1 -s DEMANGLE_SUPPORT=1")
	message (STATUS "EMCC Debug options are on")
else()
	set (EMCC_COMPILE_OPTION -O3)
endif()


####################################
# emscripten support
set (WASM_LINK_FLAGS "--bind -O3 --memory-init-file 0 -s LINKABLE=1 -s WASM=1 -s EXPORT_NAME=\"'INScoreModule'\" -s MODULARIZE=1 -s ASSERTIONS=1 -s ALLOW_MEMORY_GROWTH=1 -s DISABLE_EXCEPTION_CATCHING=1")
file (GLOB EMCCSRC 	${SRCDIR}/emcc/*.cpp)

set (SRC  ${SRC} ${EMCCSRC})
set (INCDIRS  ${INCDIRS} ${SRCDIR}/emcc)
set (DEFS ${DEFS} "-DOSC_HOST_LITTLE_ENDIAN" "-DEMCC" ${EMCCDEBUGOPTION})

####################################
# Add the different targets
add_executable(wasmlib EXCLUDE_FROM_ALL ${SRC} ${HEADERS})
target_include_directories (wasmlib PRIVATE ${INCDIRS})
target_compile_definitions (wasmlib PRIVATE ${DEFS})
set_target_properties (wasmlib PROPERTIES
		OUTPUT_NAME libINScore
		LINK_FLAGS ${WASM_LINK_FLAGS}
		COMPILE_FLAGS ${EMCC_COMPILE_OPTION} 
		RUNTIME_OUTPUT_DIRECTORY ${LIBDIR}
		SUFFIX ".js" )
