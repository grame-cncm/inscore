cmake_minimum_required(VERSION 3.4.0)
project (inscoreemcc)

set ( CMAKE_OSX_DEPLOYMENT_TARGET	"")
set ( CMAKE_OSX_SYSROOT 		"")
set ( CMAKE_CXX_COMPILER 	"emcc")


####################################
# emscripten support
set (WASM_LINK_FLAGS "--bind -O3 --memory-init-file 0 -s LINKABLE=1 -s WASM=1 -s EXPORT_NAME=\"'INScoreModule'\" -s MODULARIZE=1 -s ASSERTIONS=1 -s ALLOW_MEMORY_GROWTH=1 -s DISABLE_EXCEPTION_CATCHING=1")
set (SRC  ${SRC} ${SRCDIR}/emcc/exports.cpp)
set (DEFS ${DEFS} "-DOSC_HOST_LITTLE_ENDIAN" "-DEMCC")

####################################
# Add the different targets
add_executable(wasmlib EXCLUDE_FROM_ALL ${SRC} ${HEADERS})
target_include_directories (wasmlib PRIVATE ${INCDIRS})
target_compile_definitions (wasmlib PRIVATE ${DEFS})
set_target_properties (wasmlib PROPERTIES
		OUTPUT_NAME libINScore
		LINK_FLAGS ${WASM_LINK_FLAGS}
		COMPILE_FLAGS -O3 
		RUNTIME_OUTPUT_DIRECTORY ${LIBDIR}
		SUFFIX ".js" )
