#######################################
# CMAKE INScore core library
#######################################
cmake_minimum_required(VERSION 3.4.0)

set(HAVE_FLAG_SEARCH_PATHS_FIRST 0)
project(INScoreJS)

set (CMAKE_BUILD_TYPE Release)

get_filename_component(BUILD ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)
get_filename_component(ROOT ${BUILD} DIRECTORY)

option ( EMCC		"Generates the wasm library"	on )

#######################################
# versions management
set (VERSION 1.2.6)
macro (get_major_minor_patch version)
	string( REGEX REPLACE "([0-9]*)\\.([0-9]*)\\.([0-9]*)" "\\1"  VERSION_MAJOR ${version} )
	string( REGEX REPLACE "([0-9]*)\\.([0-9]*)\\.([0-9]*)" "\\2"  VERSION_MINOR ${version} )
	string( REGEX REPLACE "([0-9]*)\\.([0-9]*)\\.([0-9]*)" "\\3"  VERSION_PATCH ${version} )
endmacro()
get_major_minor_patch( ${VERSION} )
set (SOVERS ${VERSION_MAJOR})
set (STRVERS "v.1.2.6.0")
message (STATUS "Configuring version ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

#######################################
# Output folders 
set (BINDIR ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set (LIBDIR ${CMAKE_CURRENT_SOURCE_DIR}/lib)

set (CMAKE_CXX_STANDARD 11)

#######################################
# set emcc compiler and options
if (EMCC)

option ( EMCCDEBUG		"Activate emcc debug information"	off )

set ( CMAKE_OSX_DEPLOYMENT_TARGET	"")
set ( CMAKE_OSX_SYSROOT 		"")
set ( CMAKE_CXX_COMPILER 	"emcc")
set ( CMAKE_CXX_LINK_FLAGS "")
set (WASM_LINK_FLAGS "--bind -O3 --memory-init-file 0 -s LINKABLE=1 -s WASM=1 -s EXPORT_NAME=\"'INScoreModule'\" -s MODULARIZE=1 -s ASSERTIONS=1 -s ALLOW_MEMORY_GROWTH=1 -s DISABLE_EXCEPTION_CATCHING=1  -s EXTRA_EXPORTED_RUNTIME_METHODS='[\"UTF8ToString\"]'")

file (GLOB EMCCSRC 	bindings/*.cpp)
set (LIBDIR ${CMAKE_CURRENT_SOURCE_DIR}/../lib)
set (SRC  ${SRC} ${EMCCSRC})
set (INCDIRS  ${INCDIRS} bindings)
set (DEFS ${DEFS} "-DOSC_HOST_LITTLE_ENDIAN" "-DEMCC" ${EMCCDEBUGOPTION})

if (EMCCDEBUG)
	set (EMCC_COMPILE_OPTION "-s ASSERTIONS=1 -s SAFE_HEAP=1 -s STACK_OVERFLOW_CHECK=1 -s DEMANGLE_SUPPORT=1")
	message (STATUS "EMCC Debug options are on")
else()
	set (EMCC_COMPILE_OPTION -O3)
endif()
endif()

#######################################
# set directories, src and headers.
set (SRCDIR      ${ROOT}/src)
set (INSCOREDIR  ${SRCDIR}/inscore)
set (INSCOREDIRS ITLParser events lib model scripting signal controller expression expression/parser interface mapping view signal)
set (INSCORE2DIR ${SRCDIR}/inscore2)
if (USEOSC)
set (INSCOREDIRS ${INSCOREDIRS} osc)
endif()
set (MAPPINGDIR  ${SRCDIR}/libmapping/src)
set (VIEWSDIR    ${SRCDIR}/view)
set (PUBLICDIR   ${INSCOREDIR}/inerface)
set (LOCALLIB 	 ${ROOT}/lib)
set (OSCPACK     ${LOCALLIB}/oscpack)
set (JSON        ${SRCDIR}/json)
if (win32) 
	set (OSCIP ${OSCPACK}/ip/win32 )
else()     
	set (OSCIP ${OSCPACK}/ip/posix )
endif()

set (GUIDOAR      ${ROOT}/guidoar/src)



#######################################
# set sources and headers files
foreach(DIR ${INSCOREDIRS})
file (GLOB DIRSRC 	${INSCOREDIR}/${DIR}/*.cpp)
	set (CORESRC ${CORESRC} ${DIRSRC})
endforeach()

file (GLOB COREHEADERS 		"${INSCOREDIR}/*/*.h" "${INSCOREDIR}/signal/faust/*.h" "${INSCOREDIR}/expression/parser/*.h")
file (GLOB CORE2SRC 		"${INSCORE2DIR}/*.cpp" "${INSCORE2DIR}/*/*.cpp" )
file (GLOB CORE2HEADERS 	"${INSCORE2DIR}/*.h" "${INSCORE2DIR}/*/*.h")
file (GLOB PUBLICHEADERS 	"${PUBLICDIR}/*.h")

file (GLOB MAPSRC 		"${MAPPINGDIR}/*/*.cpp" )
file (GLOB MAPHEADERS 	"${MAPPINGDIR}/*/*.h" )
file (GLOB MISCSRC 		"${JSON}/*.cpp" )
file (GLOB MISCHEADERS 	"${JSON}/*.h" )

message (STATUS "Generates INScore library with HTML view")
file (GLOB VIEWSRC 		"${VIEWSDIR}/HTMLVIEW/*.cpp")
file (GLOB VIEWHEADERS  "${VIEWSDIR}/HTMLVIEW/*.h")
set  (INCDIRS ${INCDIRS} ${VIEWSDIR}/HTMLVIEW)

set (SRC ${SRC}	${CORESRC} ${CORE2SRC} ${MAPSRC} ${OSCSRC} ${MISCSRC} ${VIEWSRC} )
set (HEADERS ${COREHEADERS} ${CORE2HEADERS} ${MAPHEADERS} ${OSCHEADERS} ${MISCHEADERS} ${VIEWHEADERS} )

set (DEFS ${DEFS} -DHTMLVIEW)
set (DEFS ${DEFS} -DNO_OSCSTREAM)

#######################################
# guidoar part
set (GUIDOARFOLDERS  interface guido guido/abstract lib operations visitors parser)

foreach(folder ${GUIDOARFOLDERS})
	set(ARCPP ${ARCPP} "${GUIDOAR}/${folder}/*.cpp")			# add source files
endforeach(folder)
file (GLOB ARSRC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${ARCPP})
set (SRC ${SRC}	${ARSRC} )

foreach(folder ${GUIDOARFOLDERS})
	set(ARH ${ARH} "${GUIDOAR}/${folder}/*.h")		# add header files
endforeach(folder)
file (GLOB ARHEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${ARH})
set (HEADERS ${HEADERS}	${ARHEADERS} )

set (DEFS ${DEFS} -DHAS_LIBMAPPING_SMARTP)

####################################
# include directories
set (INCDIRS  ${INCDIRS}
	${INSCOREDIR}/controller ${INSCOREDIR}/events ${INSCOREDIR}/expression ${INSCOREDIR}/expression/parser ${INSCOREDIR}/parser
	${INSCOREDIR}/httpserver ${INSCOREDIR}/interface ${INSCOREDIR}/ITLParser
	${INSCOREDIR}/lib ${INSCOREDIR}/mapping ${INSCOREDIR}/model
	${INSCOREDIR}/scripting ${INSCOREDIR}/sensors ${INSCOREDIR}/signal ${INSCOREDIR}/signal/faust
	${INSCOREDIR}/view ${INSCOREDIR}/web ${INSCOREDIR}/osc
	${INSCORE2DIR} ${INSCORE2DIR}/eval ${INSCORE2DIR}/parser ${INSCORE2DIR}/sorter)

set (INCDIRS ${INCDIRS} ${MAPPINGDIR}/misc ${MAPPINGDIR}/parser ${MAPPINGDIR}/relations ${MAPPINGDIR}/segments)
set (INCDIRS ${INCDIRS} ${JSON})
set (INCDIRS ${INCDIRS} ${LOCALLIB}/GuidoEngine/include ${LOCALLIB}/GuidoAR/include)

foreach(folder ${GUIDOARFOLDERS})
	set(INCDIRS ${INCDIRS} "${GUIDOAR}/${folder}")
endforeach(folder)

#######################################
# set libraries and definitions
set (DEFS ${DEFS} -DHAVE_CONFIG_H=1 -DJSON_ONLY -DINScore_EXPORTS)
if(APPLE)
	set (LIBS ${LIBS} "-L/usr/local/lib -lmicrohttpd")
	set (LIBS ${LIBS} "-F${LOCALLIB}/GuidoEngine/macosx/ -F${LOCALLIB}/GuidoAR/macosx/")
	set (LIBS ${LIBS} "-framework GUIDOEngine -framework GuidoAR -framework CoreFoundation")
	set (DEFS ${DEFS} -DMACOS)
elseif (UNIX)
	set (LIBS ${LIBS} "-lGUIDOEngine -lguidoar")
	set (DEFS ${DEFS} "-DOSC_HOST_LITTLE_ENDIAN -D__LINUX__")
elseif (WIN32)
	enable_language(RC)
	set (SRC ${SRC} ${ROOT}/win32/INScore.rc)
	set (LIBS ${LIBS} "winmm.lib" "ws2_32.lib" "${LOCALLIB}/GuidoEngine/win64/GUIDOEngine64.lib" "${LOCALLIB}/GuidoAR/win64/guidoar.lib")
	set (INCDIRS ${INCDIRS} ${ROOT}/win32/dirent)
	set (DEFS ${DEFS} "-DMSVC -D_USE_MATH_DEFINES -DNOMINMAX -D_CRT_SECURE_NO_WARNINGS -DWINDOWS")
endif()

#######################################
# describe targets
if (EMCC)
set (target emcc)
message (STATUS "Generates project for emcc")
add_executable(${target} EXCLUDE_FROM_ALL ${SRC} ${HEADERS})
target_include_directories (${target} PRIVATE ${INCDIRS})
target_compile_definitions (${target} PRIVATE ${DEFS})
set_target_properties (${target} PROPERTIES
		OUTPUT_NAME libINScore
		LINK_FLAGS ${WASM_LINK_FLAGS}
		COMPILE_FLAGS ${EMCC_COMPILE_OPTION} 
		RUNTIME_OUTPUT_DIRECTORY ${LIBDIR}
		SUFFIX ".js" )

else ()
set (target INScoreModel)
message (STATUS "Generates project for native compiler")
add_library(${target} SHARED ${SRC} ${HEADERS})
target_compile_definitions (${target} PRIVATE ${DEFS})
target_include_directories (${target} PRIVATE ${INCDIRS})
target_link_libraries (${target} ${LIBS})
set_target_properties (${target} PROPERTIES
		RUNTIME_OUTPUT_DIRECTORY  ${LIBDIR}
		RUNTIME_OUTPUT_DIRECTORY_RELEASE  ${LIBDIR}
		ARCHIVE_OUTPUT_DIRECTORY  ${LIBDIR}
		ARCHIVE_OUTPUT_DIRECTORY_RELEASE  ${LIBDIR}
		LIBRARY_OUTPUT_DIRECTORY ${LIBDIR}
		LIBRARY_OUTPUT_DIRECTORY_RELEASE ${LIBDIR}
		PUBLIC_HEADER "${PUBLICHEADERS}"
		VERSION ${VERSION}
		SOVERSION ${SOVERS}
		MACOSX_FRAMEWORK_SHORT_VERSION_STRING ${STRVERS}
		MACOSX_FRAMEWORK_BUNDLE_VERSION ${VERSION} )

add_executable( inscoretest ${CMAKE_CURRENT_SOURCE_DIR}/tests/main.cpp )
target_include_directories (inscoretest PRIVATE ${INSCOREDIR}/interface)
target_link_libraries( inscoretest ${target})
set_target_properties(inscoretest  PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${BINDIR}
	RUNTIME_OUTPUT_DIRECTORY_RELEASE ${BINDIR})
add_dependencies(inscoretest ${target})

endif()
