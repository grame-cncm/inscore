cmake_minimum_required(VERSION 3.8.0 FATAL_ERROR)

project(INScore)

#######################################
# versions management
set (VERSION 1.2.7)
set (STRVERS "1.2.7")
macro (get_major_minor_patch version)
	string( REGEX REPLACE "([0-9]*)\\.([0-9]*)\\.([0-9]*)" "\\1"  VERSION_MAJOR ${version} )
	string( REGEX REPLACE "([0-9]*)\\.([0-9]*)\\.([0-9]*)" "\\2"  VERSION_MINOR ${version} )
	string( REGEX REPLACE "([0-9]*)\\.([0-9]*)\\.([0-9]*)" "\\3"  VERSION_PATCH ${version} )
endmacro()
get_major_minor_patch( ${VERSION} )
set (SOVERS ${VERSION_MAJOR})
message (STATUS "Configuring INScore version ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

#######################################
# Options 
option ( IOS 		"Generates project for iOS" off )
option ( WASM 		"Generates an emcc based Makefile" off )
option ( ANDROID 	"Generates an android Makefile" off )
option ( QTVIEW 	"Includes Qt view" on )
option ( HTMLVIEW 	"Includes HTML view" off )



get_filename_component(ROOT ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)
set (SRCDIR  	${ROOT}/src)
set (GUIDOLIB 	${ROOT}/modules/guidolib)
set (LIBXML 	${ROOT}/modules/libmusicxml)
set (LOCALLIB 	${ROOT}/lib)
set (QRENCODE 	${LOCALLIB}/qrencode)
set (JSON   	${SRCDIR}/json)
set (MAPPINGS 	${SRCDIR}/libmapping)
set (IBUNDLE 	${SRCDIR}/QArchive)
if (WIN32)
	set ( DEFS ${DEFS} -DWINDOWS -DMSVC  -D_USE_MATH_DEFINES NOMINMAX -D_CRT_SECURE_NO_WARNINGS -DGUIDOAR_EXPORTS)
elseif (APPLE)
	if (IOS)
		set ( DEFS ${DEFS} -DINSCORE_IOS)
	else()
		set ( DEFS ${DEFS} -DMACOS)
	endif()
endif()

set (CMAKE_CXX_STANDARD 11)


#######################################
# guidoar settings
set (GUIDOAR_DIR ${CMAKE_CURRENT_SOURCE_DIR}/modules)
find_package(GUIDOAR REQUIRED)

#######################################
# Qt settings
set (QTVIEW_DIR ${CMAKE_CURRENT_SOURCE_DIR}/modules)
find_package(QTVIEW REQUIRED)

#######################################
# OSC settings
set (OSC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/modules)
find_package(OSC REQUIRED)

#message ("GUIDOAR_HEADERS ${GUIDOAR_HEADERS}")

# HAVE_CONFIG_H defined for the qrencode library
set ( DEFS ${DEFS} ${QTVIEW_DEFINITIONS} -DINScore_EXPORTS -DHAVE_CONFIG_H -DJSON_ONLY)

#######################################
# set sources and headers files
file (GLOB SRC           RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} 
	"${SRCDIR}/inscore/*/*.cpp" 
	"${SRCDIR}/inscore/plugins/*/*.cpp" 
	"${SRCDIR}/inscore/signal/faust/*.cpp" 
	"${SRCDIR}/inscore/expression/parser/*.cpp" 
	"${SRCDIR}/inscore2/*.cpp" 
	"${SRCDIR}/inscore2/*/*.cpp"
	"${MAPPINGS}/src/*/*.cpp"
	"${IBUNDLE}/*.cpp"
	"${JSON}/*.cpp"
	"${QRENCODE}/*.c"
)
set (SRC ${SRC} ${GUIDOAR_SRC} ${QTVIEW_SRC} ${OSC_SRC})

file (GLOB HEADERS       RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} 
	"${SRCDIR}/inscore/*/*.h" 
	"${SRCDIR}/inscore/plugins/*/*.h" 
	"${SRCDIR}/inscore/signal/faust/*.h" 
	"${SRCDIR}/inscore/expression/parser/*.h" 
	"${SRCDIR}/inscore2/*.h" 
	"${SRCDIR}/inscore2/*/*.h"
	"${MAPPINGS}/src/*/*.h"
	"${IBUNDLE}/*.h"
	"${JSON}/*.h"
	"${QRENCODE}/*.h"
)
set (HEADERS ${HEADERS} ${GUIDOAR_HEADERS} ${QTVIEW_HEADERS} ${OSC_HEADERS})


file (GLOB PUBLICHEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "${SRCDIR}/inscore/interface/*.h")

#######################################
# set includes
set (INCL ${INCL} 
	"${SRCDIR}/inscore/*" 
	"${SRCDIR}/inscore/plugins/*" 
	"${SRCDIR}/inscore/signal/faust" 
	"${SRCDIR}/inscore/expression/parser" 
	"${SRCDIR}/inscore2" "${SRCDIR}/inscore2/eval" "${SRCDIR}/inscore2/parser" "${SRCDIR}/inscore2/sorter"
	"${MAPPINGS}/src/*"
	"${GUIDOLIB}/src/engine/include"
	"${JSON}"
	"${QRENCODE}"
)
file (GLOB INCDIRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${INCL})
set (INCDIRS ${INCDIRS} ${GUIDOAR_INCLUDE_DIRS} ${QTVIEW_INCLUDE_DIRS} ${QT_INCLUDE_DIRS} ${OSC_INCLUDE_DIRS})

#message ("INCDIRS ${INCDIRS}")

if (WIN32)
	set (INCDIRS ${INCDIRS}  ${ROOT}/win32/dirent)
endif()

#######################################
# libmicrohttp settings
set (INCDIRS ${INCDIRS} "/usr/local/include" )

if (APPLE AND NOT IOS)
	set (LIBS ${LIBS} -F${GUIDOLIB}/build/lib "-framework GUIDOEngine")
endif()
if (WIN32)
	enable_language(RC)
	set(SRC ${SRC} ${ROOT}/win32/INScore.rc)
	set (LIBS ${LIBS} ${GUIDOLIB}/build/lib/GUIDOEngine64.lib winmm.lib ws2_32.lib)
else()
	set (LIBS ${LIBS} -L/usr/local/lib -lmicrohttpd)
endif()
set (LIBS ${LIBS} ${QTVIEW_LIBRARIES} ${QT_LIBRARIES})

#######################################
# Output folders 
set (BINDIR ${CMAKE_CURRENT_SOURCE_DIR}/cmbin)
set (LIBDIR ${CMAKE_CURRENT_SOURCE_DIR}/cmlib)

set (target INScore)
add_library(${target} SHARED ${SRC} ${HEADERS} ${PUBLICHEADERS})
target_compile_definitions (${target} PRIVATE ${DEFS})
target_include_directories (${target} PRIVATE ${INCDIRS})
target_link_libraries (${target} PRIVATE ${LIBS})
set_target_properties (${target} PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY  ${LIBDIR}
	RUNTIME_OUTPUT_DIRECTORY_RELEASE  ${LIBDIR}
	ARCHIVE_OUTPUT_DIRECTORY  ${LIBDIR}
	ARCHIVE_OUTPUT_DIRECTORY_RELEASE  ${LIBDIR}
	LIBRARY_OUTPUT_DIRECTORY ${LIBDIR}
	LIBRARY_OUTPUT_DIRECTORY_RELEASE ${LIBDIR}
	PUBLIC_HEADER "${PUBLICHEADERS}"
	VERSION ${VERSION}
	SOVERSION ${SOVERS})


#######################################
# viewer settings

set(CMAKE_AUTORCC ON)
file (GLOB APPSRC 		RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${SRCDIR}/inscoreviewer/qtview/*.cpp)
file (GLOB APPHEADERS 	RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${SRCDIR}/inscoreviewer/qtview/*.h)
#file (GLOB APPPLUGINS 	RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${LIBXML}/build/lib/libmusicxml2*.dylib)
set (APPLIBS ${target} ${QT_LIBRARIES} ${GUIDO_LIBRARIES})
set (APP_INCLUDES ${SRCDIR}/inscore/interface ${QTVIEW_INCLUDE_DIRS} "${GUIDOLIB}/src/engine/include")

set(MACOSX_BUNDLE_ICON_FILE INScoreViewer.icns)
set(VIEWER_ICON "${ROOT}/rsrc/INScoreViewer.icns")
set_source_files_properties(${VIEWER_ICON} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
#set_source_files_properties(${APPPLUGINS} PROPERTIES MACOSX_PACKAGE_LOCATION "PlugIns")

set (APP_RSRC "${ROOT}/rsrc/inscore.qrc"  ${VIEWER_ICON})

if (WIN32)
	enable_language(RC)
	set(APPSRC ${APPSRC} ${ROOT}/win32/Viewer/INScoreViewer.rc)
	set(EXE WIN32)
elseif(APPLE)
	set(EXE MACOSX_BUNDLE)
endif()
 
set (viewer INScoreViewer)
add_executable(${viewer} ${EXE} ${APPSRC} ${APPHEADERS} ${APP_RSRC})
target_compile_definitions (${viewer} PRIVATE ${DEFS})
target_include_directories (${viewer} PRIVATE ${APP_INCLUDES})
target_link_libraries (${viewer} PRIVATE ${APPLIBS})
set_target_properties (${viewer} PROPERTIES
    BUNDLE true
#    MACOSX_BUNDLE_GUI_IDENTIFIER fr.grame.INScore
    MACOSX_BUNDLE_BUNDLE_NAME ${viewer}
    MACOSX_BUNDLE_BUNDLE_VERSION "v.${VERSION}"
    MACOSX_BUNDLE_SHORT_VERSION_STRING "${VERSION}"
    MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/Info.plist
	RUNTIME_OUTPUT_DIRECTORY  ${BINDIR}
	RUNTIME_OUTPUT_DIRECTORY_RELEASE  ${BINDIR}
)
add_dependencies(${viewer} ${target})

