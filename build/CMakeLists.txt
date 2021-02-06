cmake_minimum_required(VERSION 3.4.0)

project(INScore)

get_filename_component(ROOT ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)

#######################################
# versions management
file (STRINGS "${ROOT}/version.txt" VERSION)
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
option ( MODEL 		"Generates the core model library" off )


#######################################
# Check options 
if (QTVIEW AND HTMLVIEW)
	message (FATAL "Incompatible options: can't generate both QTVIEW and HTMLVIEW")
endif()
if (IOS)
	message (STATUS "Generates project for iOS (overrides other options)")
	set (WASM off)
	set (ANDROID off)
	set (QTVIEW on)
	set (MODEL  off)
endif()
if (WASM)
	message (STATUS "Generates project for WASM (overrides other options)")
	set (ANDROID off)
	set (QTVIEW off)
	set (IOS off)
	set (MODEL  off)
endif()
if (MODEL)
	message (STATUS "Generates project for core model library (overrides other options)")
	set (ANDROID off)
	set (QTVIEW off)
	set (IOS off)
	set (WASM  off)
endif()

#######################################
# set directories for src and headers.
set (SRCDIR  	 ${ROOT}/src)
set (INSCOREDIR  ${SRCDIR}/inscore)
set (INSCORE2DIR ${SRCDIR}/inscore2) 
set (MAPPINGDIR  ${SRCDIR}/libmapping/src)
set (VIEWSDIR    ${SRCDIR}/view)
set (JSON        ${SRCDIR}/json)
set (PUBLICDIR   ${INSCOREDIR}/interface)

set (LOCALLIB 	 ${ROOT}/lib)
set (QRENCODE 	 ${LOCALLIB}/qrencode)
set (GUIDOLIB 	 ${ROOT}/modules/guidolib)
set (LIBXML 	 ${ROOT}/modules/libmusicxml)

set (INSCOREDIRS 
	${INSCOREDIR}/ITLParser
	${INSCOREDIR}/controller
	${INSCOREDIR}/events
	${INSCOREDIR}/expression
	${INSCOREDIR}/expression/parser
	${INSCOREDIR}/interface
	${INSCOREDIR}/lib
	${INSCOREDIR}/mapping
	${INSCOREDIR}/model
	${INSCOREDIR}/scripting
	${INSCOREDIR}/signal
	${INSCOREDIR}/view

	${INSCORE2DIR}
	${INSCORE2DIR}/eval
	${INSCORE2DIR}/parser
	${INSCORE2DIR}/sorter

	${MAPPINGDIR}/misc
	${MAPPINGDIR}/parser
	${MAPPINGDIR}/relations
	${MAPPINGDIR}/segments
	
	${JSON}
#	${JSON}/parser
)

#######################################
# set sources and headers files
foreach(DIR ${INSCOREDIRS})
	file (GLOB DIRSRC 	${DIR}/*.cpp)
	set (CORESRC ${CORESRC} ${DIRSRC})
endforeach()

foreach(DIR ${INSCOREDIRS})
	file (GLOB DIRH 	${DIR}/*.h)
	set (COREHEADERS ${COREHEADERS} ${DIRH})
endforeach()

foreach(DIR ${INSCOREDIRS})
	set (INCDIRS ${INCDIRS} ${DIR})
endforeach()

#######################################
# guidoar settings
set (GUIDOAR_DIR ${CMAKE_CURRENT_SOURCE_DIR}/modules)
find_package(GUIDOAR REQUIRED)
set (SRC ${CORESRC} ${GUIDOAR_SRC})
set (HEADERS ${COREHEADERS} ${GUIDOAR_HEADERS})
set (INCDIRS ${INCDIRS} ${GUIDOAR_INCLUDE_DIRS} ${GUIDOLIB}/src/engine/include)

file (GLOB PUBLICHEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "${PUBLICDIR}/*.h")


set (CMAKE_CXX_STANDARD 11)
#######################################
# set definitions
set ( DEFS ${DEFS} -DINScore_EXPORTS -DJSON_ONLY)
if (WIN32)
	set ( DEFS ${DEFS} -DWINDOWS -DMSVC  -D_USE_MATH_DEFINES NOMINMAX -D_CRT_SECURE_NO_WARNINGS -DGUIDOAR_EXPORTS)
elseif (APPLE)
	if (IOS)
		set ( DEFS ${DEFS} -DINSCORE_IOS)
	else()
		set ( DEFS ${DEFS} -DMACOS)
	endif()
elseif(UNIX)
	set ( DEFS ${DEFS} -D__LINUX__ -DOSC_HOST_LITTLE_ENDIAN)
endif()


#######################################
# Output folders 
set (BINDIR ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set (LIBDIR ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set (LIBTYPE SHARED)  # by default, generates shared libraries

#######################################
# Qt View settings
if (QTVIEW)
	set (QTVIEW_DIR ${CMAKE_CURRENT_SOURCE_DIR}/modules)
	find_package(QTVIEW REQUIRED)

	set (OSC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/modules)
	find_package(OSC REQUIRED)

	set (DEFS ${DEFS} ${QTVIEW_DEFINITIONS})
	set (SRC ${SRC} ${QTVIEW_SRC} ${OSC_SRC})
	set (HEADERS ${HEADERS} ${QTVIEW_HEADERS} ${OSC_HEADERS})
	set (INCDIRS ${INCDIRS} ${QTVIEW_INCLUDE_DIRS} ${QT_INCLUDE_DIRS} ${OSC_INCLUDE_DIRS})
	set (LIBS ${LIBS} ${QT_LIBRARIES})

	if (WIN32)
		set (INCDIRS ${INCDIRS}  ${ROOT}/win32/dirent)
	else()
		set (INCDIRS ${INCDIRS} "/usr/local/include" ) # libmicrohttp settings
	endif()

	if (IOS)
		set (IOS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/modules)
		find_package(IOS REQUIRED)
		
		set (DEFS ${DEFS} ${IOS_DEFINITIONS})
		set (SRC ${SRC} ${IOS_SRC})
		set (HEADERS ${HEADERS} ${IOS_HEADERS})
		set (INCDIRS ${INCDIRS} ${IOS_INCLUDE_DIRS})
		set (LIBS ${LIBS} ${GUIDOLIB}/build/lib/libGUIDOEngine.a)
	elseif (APPLE)
		set (LIBS ${LIBS} -F${GUIDOLIB}/build/lib "-framework GUIDOEngine")
	endif()

	file (GLOB QRCSRC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "${QRENCODE}/*.c")
	file (GLOB QRCH RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "${QRENCODE}/*.h")
	set (SRC ${SRC} ${QRCSRC})
	set (HEADERS ${HEADERS} ${QRCH})
	set (INCDIRS ${INCDIRS} ${QRENCODE})
	set ( DEFS ${DEFS} -DHAVE_CONFIG_H)  # HAVE_CONFIG_H defined for the qrencode library

	if (WIN32)
		enable_language(RC)
		set(SRC ${SRC} ${ROOT}/win32/INScore.rc)
		set (LIBS ${LIBS} ${GUIDOLIB}/build/lib/GUIDOEngine64.lib winmm.lib ws2_32.lib)
	else()
		set (LIBS ${LIBS} -L/usr/local/lib -lmicrohttpd)
	endif()

	#######################################
	# library settings 
	set (target INScore)
	add_library(${target} ${LIBTYPE} ${SRC} ${HEADERS} ${PUBLICHEADERS})
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
	if (UNIX AND NOT APPLE)
		set (GUIDO_LIBRARIES -L/usr/local/lib -lGUIDOEngine)
	endif()
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
		MACOSX_BUNDLE_BUNDLE_NAME ${viewer}
		MACOSX_BUNDLE_BUNDLE_VERSION "v.${VERSION}"
		MACOSX_BUNDLE_SHORT_VERSION_STRING "${VERSION}"
		MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/Info.plist
		RUNTIME_OUTPUT_DIRECTORY  ${BINDIR}
		RUNTIME_OUTPUT_DIRECTORY_RELEASE  ${BINDIR}
	)
	add_dependencies(${viewer} ${target})

endif(QTVIEW)

#######################################
# WASM settings
if (WASM)
	set (WASM_DIR ${CMAKE_CURRENT_SOURCE_DIR}/modules)
	find_package(WASM REQUIRED)
	set (SRC ${SRC} ${WASM_SRC})
	set (HEADERS ${HEADERS} ${WASM_HEADERS})
	set (INCDIRS ${INCDIRS} ${WASM_INCLUDE_DIRS})
	set (DEFS    ${DEFS}    ${WASM_DEFINITIONS})

	set (target wasm)
	add_executable(${target} EXCLUDE_FROM_ALL ${SRC} ${HEADERS})
	target_include_directories (${target} PRIVATE ${INCDIRS})
	target_compile_definitions (${target} PRIVATE ${DEFS})
	set_target_properties (${target} PROPERTIES
		OUTPUT_NAME libINScore
		LINK_FLAGS ${WASM_LINK_FLAGS}
		COMPILE_FLAGS ${WASM_COMPILE_FLAGS} 
		RUNTIME_OUTPUT_DIRECTORY ${LIBDIR}
		SUFFIX ".js" )
endif(WASM)

#######################################
# Core model library settings
if (MODEL)
	set (MODELVIEWDIR ${SRCDIR}/view/VoidView)
	file (GLOB MODEL_SRC 		${MODELVIEWDIR}/*.cpp)
	file (GLOB MODEL_HEADERS  ${MODELVIEWDIR}/*.h)
	set (DEFS  ${DEFS} -DNO_OSCSTREAM -DNOVIEW)
	set (SRC ${SRC} ${MODEL_SRC})
	set (HEADERS ${HEADERS} ${MODEL_HEADERS})
	set (INCDIRS ${INCDIRS} ${MODELVIEWDIR} ${INSCOREDIR}/osc)

	if(APPLE)
		set (LIBS ${LIBS} -F${GUIDOLIB}/build/lib "-framework GUIDOEngine")
	elseif (UNIX)
		set (LIBS ${LIBS}  -L/usr/local/lib -lGUIDOEngine)
	elseif (WIN32)
		enable_language(RC)
		set (SRC ${SRC} ${ROOT}/win32/INScore.rc)
		set (LIBS ${LIBS} ${GUIDOLIB}/build/lib/GUIDOEngine64.lib winmm.lib ws2_32.lib)
	endif()

	set (target INScoreModel)
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
	)

	set (testappl INScoreModelTest)
	add_executable( ${testappl} ${ROOT}/tools/TestModel/main.cpp )
	target_include_directories (${testappl} PRIVATE ${INSCOREDIR}/interface)
	target_link_libraries( ${testappl} ${target})
	set_target_properties(${testappl}  PROPERTIES
		RUNTIME_OUTPUT_DIRECTORY ${BINDIR}
		RUNTIME_OUTPUT_DIRECTORY_RELEASE ${BINDIR})
	add_dependencies(${testappl} ${target})
endif(MODEL)
