#######################################
# CMAKE INScore core library
#######################################
project(INScore)
cmake_minimum_required(VERSION 2.6)

set (CMAKE_BUILD_TYPE Release)
set (target INScoreModel)

get_filename_component(BUILD ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)
get_filename_component(ROOT ${BUILD} DIRECTORY)

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
# Output options
option ( NOVIEW    	"Compiles with no view"	 	on )
option ( SVGVIEW	"Compiles with svg view"	off )
option ( FRMWK		"Generates a framework (MacOS)"	off )
option ( USEOSC		"Include OSC layer"	on )
option ( EMCC		"Use emcc compiler"	off )

#######################################
# Output folders 
set (BINDIR ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set (LIBDIR ${CMAKE_CURRENT_SOURCE_DIR}/lib)

set (CMAKE_CXX_STANDARD 11)

#######################################
# set directories, src and headers.
set (SRCDIR      ${ROOT}/src)
set (INSCOREDIR  ${SRCDIR}/inscore)
set (INSCOREDIRS ITLParser events lib model scripting signal controller expression expression/parser interface mapping view)
set (INSCORE2DIR ${SRCDIR}/inscore2)
if (USEOSC)
set (INSCOREDIRS ${INSCOREDIRS} osc)
endif()
set (MAPPINGDIR  ${SRCDIR}/libmapping/src)
set (VIEWSDIR    ${SRCDIR}/view)
set (PUBLICDIR   ${INSCOREDIR}/inerface)
set (LOCALLIB 	 ${ROOT}/lib)
set (OSCPACK     ${LOCALLIB}/oscpack)
#set (QRENCODE    ${LOCALLIB}/qrencode)
set (JSON        ${SRCDIR}/json)
if (win32) 
	set (OSCIP ${OSCPACK}/ip/win32 )
else()     
	set (OSCIP ${OSCPACK}/ip/posix )
endif()


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

set (SRC 	 ${CORESRC} ${CORE2SRC} ${MAPSRC} ${OSCSRC} ${MISCSRC} ${VIEWSRC} )
set (HEADERS ${COREHEADERS} ${CORE2HEADERS} ${MAPHEADERS} ${OSCHEADERS} ${MISCHEADERS} ${VIEWHEADERS} )

if (USEOSC)
	message (STATUS "Generates INScore library with OSC layer")
	file (GLOB OSCSRC 		"${OSCPACK}/ip/*.cpp" "${OSCPACK}/osc/*.cpp" "${OSCIP}/*.cpp" )
	file (GLOB OSCHEADERS 	"${OSCPACK}/ip/*.h" "${OSCPACK}/osc/*.h" "${OSCIP}/*.h" )
	set (SRC 	 ${SRC} ${OSCSRC} )
	set (HEADERS ${HEADERS} ${OSCHEADERS} )
	set  (INCDIRS ${INCDIRS} ${OSCPACK})
else()
	message (STATUS "Generates INScore library with no OSC layer")
	set (DEFS ${DEFS} "-DNO_OSCSTREAM")
endif()

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
if (USEOSC)
set (INCDIRS ${INCDIRS} ${OSC})
endif()

if (NOVIEW)
	message (STATUS "Generates INScore library with no view")
	file (GLOB VIEWSRC 		RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "${VIEWSDIR}/VoidView/*.cpp")
	file (GLOB VIEWHEADERS 	RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "${VIEWSDIR}/VoidView/*.h")
	set  (INCDIRS ${INCDIRS} ${VIEWSDIR}/VoidView)
endif()
if (SVGVIEW)
	message (STATUS "Generates INScore library with SVG view")
	file (GLOB VIEWSRC 		RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "${VIEWSDIR}/SVGView/*.cpp")
	file (GLOB VIEWHEADERS 	RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "${VIEWSDIR}/SVGView/*.h")
endif()

#########################################
# mac os specific part
#########################################
if(APPLE)
	if (NOT DEFINED DEPLOYMENT_TARGET_VERSION)
		set ( DEPLOYMENT_TARGET_VERSION  10.11)
	endif()
	if (DEPLOYMENT_TARGET)
		set (CMAKE_OSX_DEPLOYMENT_TARGET ${DEPLOYMENT_TARGET_VERSION})
	endif()
	set (CMAKE_MACOSX_RPATH on)
endif()

#######################################
# set libraries and definitions
set (DEFS ${DEFS} -DHAVE_CONFIG_H=1 -DJSON_ONLY -DINScore_EXPORTS -DMODELONLY)
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
set (FRMWKFLAG	FALSE)
if (FRMWK)
	set (FRMWKFLAG	TRUE)
endif()


if (EMCC)
	message (STATUS "Generates project for emcc")
	add_subdirectory (emcc)
else()

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
		FRAMEWORK ${FRMWKFLAG}
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

