
cmake_minimum_required(VERSION 3.8.0 FATAL_ERROR)

get_filename_component(ROOT ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)
set (SRCDIR  	 ${ROOT}/src)
set (INSCOREDIR  ${SRCDIR}/inscore)
set (INSCORE2DIR ${SRCDIR}/inscore2)
set (MAPDIR      ${SRCDIR}/libmapping)
set (QARCHIVE 	 ${SRCDIR}/QArchive)
set (IBUNDLEDIR  ${ROOT}/tools/iBundle)

#######################################
# viewer settings
set(CMAKE_AUTORCC ON)
file (GLOB VIEWER_SRC 		RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${SRCDIR}/inscoreviewer/qtview/*.cpp)
file (GLOB VIEWER_HEADERS 	RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${SRCDIR}/inscoreviewer/qtview/*.h)
#file (GLOB VIEWER_LUGINS 	RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${LIBXML}/build/lib/libmusicxml2*.dylib)
if (UNIX AND NOT APPLE)
	set (GUIDO_LIBRARIES -L/usr/local/lib -lGUIDOEngine)
endif()
set (VIEWER_LIBS ${target} ${QT_LIBRARIES} ${GUIDO_LIBRARIES})
set (VIEWER_INCLUDE_DIRS ${SRCDIR}/inscore/interface 
	${QTVIEW_INCLUDE_DIRS} 
	"${GUIDOLIB}/src/engine/include")

set(MACOSX_BUNDLE_ICON_FILE INScoreViewer.icns)
set(VIEWER_ICON "${ROOT}/rsrc/INScoreViewer.icns")
set_source_files_properties(${VIEWER_ICON} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
#set_source_files_properties(${APPPLUGINS} PROPERTIES MACOSX_PACKAGE_LOCATION "PlugIns")

set (VIEWER_RSRC "${ROOT}/rsrc/inscore.qrc"  ${VIEWER_ICON})

if (WIN32)
	enable_language(RC)
	set(VIEWER_SRC ${VIEWER_SRC} ${ROOT}/win32/Viewer/INScoreViewer.rc)
	set(EXE WIN32)
elseif(APPLE)
	set(EXE MACOSX_BUNDLE)
endif()

message (STATUS "Includes INScoreViewer")

