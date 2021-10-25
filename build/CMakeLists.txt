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
option ( QT6 		"Use Qt version 6" off )

if (NOT WASM)
set (CMAKE_BUILD_RPATH ../lib)
set (CMAKE_SKIP_BUILD_RPATH FALSE)
endif()

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
# set sub modules path
set (CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} modules)

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
	${INSCOREDIR}/communication
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
find_package(GUIDOAR REQUIRED)
set (SRC ${CORESRC} ${GUIDOAR_SRC})
set (HEADERS ${COREHEADERS} ${GUIDOAR_HEADERS})
set (INCDIRS ${INCDIRS} ${GUIDOAR_INCLUDE_DIRS})

#######################################
# guido settings
find_package(GUIDO REQUIRED)
set (INCDIRS ${INCDIRS} ${GUIDO_INCLUDE_DIRS})
set (LIBS ${LIBS} ${GUIDO_LIBRARIES})

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
		set (CMAKE_C++_FLAGS -mmacosx-version-min=10.13)
		set (CMAKE_LDFLAGS -mmacosx-version-min=10.13)
		set (CMAKE_OSX_DEPLOYMENT_TARGET 10.13)
		set (MACOSX_DEPLOYMENT_TARGET 10.13)
	endif()
elseif(UNIX)
	set ( DEFS ${DEFS} -D__LINUX__)
endif()
include (TestBigEndian)
TEST_BIG_ENDIAN (BIGENDIAN)
if (NOT BIGENDIAN)
	set ( DEFS ${DEFS} -DOSC_HOST_LITTLE_ENDIAN -D__LITTLE_ENDIAN__)
endif()


#######################################
# android section
if (ANDROID)
	find_package(Android REQUIRED)
endif()

#######################################
# Output folders 
set (BINDIR ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set (LIBDIR ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set (LIBTYPE SHARED)  # by default, generates shared libraries

#######################################
# Qt View settings
if (QTVIEW)
	find_package(QTVIEW REQUIRED)
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
		find_package(IOS REQUIRED)
		
		set (DEFS ${DEFS} ${IOS_DEFINITIONS})
		set (SRC ${SRC} ${IOS_SRC})
		set (HEADERS ${HEADERS} ${IOS_HEADERS})
		set (INCDIRS ${INCDIRS} ${IOS_INCLUDE_DIRS})
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
		set (LIBS ${LIBS} winmm.lib ws2_32.lib)
	else()
		set (LIBS ${LIBS} -L/usr/local/lib -lmicrohttpd)
	endif()

	#######################################
	# library settings 
	set (libtarget INScore)
	add_library(${libtarget} ${LIBTYPE} ${SRC} ${HEADERS} ${PUBLICHEADERS})
	target_compile_definitions (${libtarget} PRIVATE ${DEFS})
	target_include_directories (${libtarget} PRIVATE ${INCDIRS})
	target_link_libraries (${libtarget} PRIVATE ${LIBS})
	set_target_properties (${libtarget} PROPERTIES
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
	find_package(VIEWER REQUIRED)

	if (WIN32)
		set(EXE WIN32)
	elseif(APPLE)
		set(EXE MACOSX_BUNDLE)
	endif()
 
	set (viewer INScoreViewer)
	add_executable(${viewer} ${EXE} ${VIEWER_SRC} ${VIEWER_HEADERS} ${VIEWER_RSRC})
	target_compile_definitions (${viewer} PRIVATE ${DEFS})
	target_include_directories (${viewer} PRIVATE ${VIEWER_INCLUDE_DIRS} ${GUIDO_INCLUDE_DIRS})
	target_link_libraries (${viewer} PRIVATE ${VIEWER_LIBS} ${libtarget})
	set_target_properties (${viewer} PROPERTIES
		BUNDLE true
		MACOSX_BUNDLE_BUNDLE_NAME ${viewer}
		MACOSX_BUNDLE_BUNDLE_VERSION "v.${VERSION}"
		MACOSX_BUNDLE_SHORT_VERSION_STRING "${VERSION}"
		MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/Info.plist
		RUNTIME_OUTPUT_DIRECTORY  ${BINDIR}
		RUNTIME_OUTPUT_DIRECTORY_RELEASE  ${BINDIR}
	)
	add_dependencies(${viewer} ${libtarget})

	#######################################
	# ibundle settings
if (NOT IOS)
	find_package(IBUNDLE REQUIRED)

	set (ibundle IBundle)
	add_executable(${ibundle} ${IBUNDLE_SRC} ${IBUNDLE_HEADERS})
	target_compile_definitions (${ibundle} PRIVATE ${IBUNDLE_DEFS})
	target_include_directories (${ibundle} PRIVATE ${INCDIRS} ${IBUNDLE_INCLUDE_DIRS})
	target_link_libraries (${ibundle} PRIVATE ${IBUNDLE_LIBRARIES})
	set_target_properties (${ibundle} PROPERTIES
		RUNTIME_OUTPUT_DIRECTORY  ${BINDIR}
		RUNTIME_OUTPUT_DIRECTORY_RELEASE  ${BINDIR}
	)
endif()

endif(QTVIEW)

#######################################
# WASM settings
if (WASM)
	find_package(WASM REQUIRED)
	set (SRC ${SRC} ${WASM_SRC})
	set (HEADERS ${HEADERS} ${WASM_HEADERS})
	set (INCDIRS ${INCDIRS} ${WASM_INCLUDE_DIRS})
	set (DEFS    ${DEFS}    ${WASM_DEFINITIONS})

	set (wasmtarget wasm)
	add_executable(${wasmtarget} EXCLUDE_FROM_ALL ${SRC} ${HEADERS})
	target_include_directories (${wasmtarget} PRIVATE ${INCDIRS})
	target_compile_definitions (${wasmtarget} PRIVATE ${DEFS})
	set_target_properties (${wasmtarget} PROPERTIES
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

	if (WIN32)
		enable_language(RC)
		set (SRC ${SRC} ${ROOT}/win32/INScore.rc)
	endif()

	set (modeltarget INScoreModel)
	add_library(${modeltarget} SHARED ${SRC} ${HEADERS})
	target_compile_definitions (${modeltarget} PRIVATE ${DEFS})
	target_include_directories (${modeltarget} PRIVATE ${INCDIRS})
	target_link_libraries (${modeltarget} ${LIBS})
	set_target_properties (${modeltarget} PROPERTIES
			RUNTIME_OUTPUT_DIRECTORY  ${LIBDIR}
			RUNTIME_OUTPUT_DIRECTORY_RELEASE  ${LIBDIR}
			ARCHIVE_OUTPUT_DIRECTORY  ${LIBDIR}
			ARCHIVE_OUTPUT_DIRECTORY_RELEASE  ${LIBDIR}
			LIBRARY_OUTPUT_DIRECTORY ${LIBDIR}
			LIBRARY_OUTPUT_DIRECTORY_RELEASE ${LIBDIR}
			VERSION ${VERSION}
			SOVERSION ${SOVERS}
	)

	set (testappl INScoreModelTest)
	add_executable( ${testappl} ${ROOT}/tools/TestModel/main.cpp )
	target_include_directories (${testappl} PRIVATE ${INSCOREDIR}/interface)
	target_link_libraries( ${testappl} ${modeltarget})
	set_target_properties(${testappl}  PROPERTIES
		RUNTIME_OUTPUT_DIRECTORY ${BINDIR}
		RUNTIME_OUTPUT_DIRECTORY_RELEASE ${BINDIR})
	add_dependencies(${testappl} ${modeltarget})
endif(MODEL)


#######################################
# install target
#######################################
if (NOT QTVIEW)
	RETURN()
endif()

if (APPLE)
	set (CMAKE_INSTALL_PREFIX $ENV{HOME}/INScore-${VERSION})
endif()
if (DEFINED PREFIX)
	set (CMAKE_INSTALL_PREFIX ${PREFIX})
endif()

message (STATUS "Install location is ${CMAKE_INSTALL_PREFIX}, use -DPREFIX option to change")

####################################
if (PACK)
	set (CMAKE_INSTALL_PREFIX .)
endif()

if (APPLE OR WIN32)
	set (INSTALL_BIN 		${CMAKE_INSTALL_PREFIX})
	set (INSTALL_LIB 		${CMAKE_INSTALL_PREFIX}/dev)
	set (INSTALL_INC 		${CMAKE_INSTALL_PREFIX}/dev/include)
	set (INSTALL_SAMPLES 	${CMAKE_INSTALL_PREFIX}/Examples)
	set (INSTALL_GMN_SAMPLES 	${CMAKE_INSTALL_PREFIX}/GMN-Examples)
	set (INSTALL_BUNDLES 	${CMAKE_INSTALL_PREFIX}/Bundles)
	set (INSTALL_TOOLS 		${CMAKE_INSTALL_PREFIX}/Tools)
	set (INSTALL_INTERFACES 	${CMAKE_INSTALL_PREFIX})
	set (INSTALL_DOC 		${CMAKE_INSTALL_PREFIX}/Documentation)
else()
	set (INSTALL_BIN 		${CMAKE_INSTALL_PREFIX}/bin)
	set (INSTALL_LIB 		${CMAKE_INSTALL_PREFIX}/lib)
	set (INSTALL_INC 		${CMAKE_INSTALL_PREFIX}/include/inscore)
	set (INSTALL_SHARED 	${CMAKE_INSTALL_PREFIX}/share)
	set (INSTALL_SAMPLES 	${INSTALL_SHARED}/inscore/examples)
	set (INSTALL_GMN_SAMPLES 	${INSTALL_SHARED}/inscore/GMN-Examples)
	set (INSTALL_BUNDLES 	${INSTALL_SHARED}/inscore/bundles)
	set (INSTALL_TOOLS 		${INSTALL_SHARED}/inscore/tools)
	set (INSTALL_INTERFACES ${INSTALL_SHARED}/inscore)
	set (INSTALL_DOC 		${INSTALL_SHARED}/inscore/doc)
endif()
set (installtargets 	${viewer} ${ibundle} ${libtarget})


####################################
# install compiled resources

if (APPLE)
install ( CODE "message (STATUS \"Call macdeployqt\")"
		  CODE "execute_process ( COMMAND macdeployqt ${BINDIR}/${viewer}.app )"
)
endif()

install ( TARGETS ${installtargets}
	RUNTIME DESTINATION ${INSTALL_BIN}
	BUNDLE DESTINATION  ${INSTALL_BIN}
    LIBRARY DESTINATION ${INSTALL_LIB}
    ARCHIVE DESTINATION ${INSTALL_LIB}
    PUBLIC_HEADER DESTINATION ${INSTALL_INC}
)

if(WIN32)
string( REPLACE ";" " -" MODULES "${QTMODULES}")
string( REPLACE "Core" " -Core" MODULES "${MODULES}")
string( TOLOWER  "${MODULES}" MODULES)
if (PACK)
	set (DEPLOYLOCATION "_CPack_Packages/win64/NSIS64/INScore-${VERSION}-win64")
else ()
	set (DEPLOYLOCATION ${INSTALL_BIN})
endif()
install ( CODE "message (STATUS \"Call windeployqt\" \"${MODULES}\")"
		  CODE "execute_process ( COMMAND windeployqt  ${MODULES} ${DEPLOYLOCATION}/${viewer}.exe )"
)
endif()

####################################
# install readme and changelog
if (APPLE OR WIN32)
install (
    FILES   ${ROOT}/package/ReadMe.html ${ROOT}/src/changelog.txt DESTINATION ${CMAKE_INSTALL_PREFIX}
    PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ
)
endif()

####################################
# install documentation
install (
    DIRECTORY     ${ROOT}/package/doc/ DESTINATION ${INSTALL_DOC}
    FILE_PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ
    DIRECTORY_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
    	GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
    PATTERN ".DS_Store" EXCLUDE
)


####################################
# install examples
set (EXEMPLES 	"Jeu est au autre"
				M-sync-scores
				MP-Turenas
				MP-cursors
				MP-first-demo
				MP-graphsig-sinus
				MP-graphsig-var
				MP-interaction
				MP-sync-cars
				MP-sync-train
				Max-tools
				Perception
				PureData-tools
				Standalone
)
foreach (EX ${EXEMPLES})
	set (EXFOLDERS ${EXFOLDERS} ${ROOT}/scripts/${EX})
endforeach()
install (
    DIRECTORY     ${EXFOLDERS} DESTINATION ${INSTALL_SAMPLES}
    FILE_PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ
    DIRECTORY_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
    	GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
    PATTERN ".DS_Store" EXCLUDE
    PATTERN "Paths.pdf" EXCLUDE
)
install (
    FILES   ${ROOT}/scripts/readme.md DESTINATION ${INSTALL_SAMPLES}
    PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ
)

####################################
# install guido examples
install (
    DIRECTORY   ${GUIDOLIB}/gmn-examples/examples/ DESTINATION ${INSTALL_GMN_SAMPLES}
    FILE_PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ
    DIRECTORY_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
    	GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
    PATTERN ".DS_Store" EXCLUDE
    PATTERN "ShetMusic" EXCLUDE
)

####################################
# install bundles
file (GLOB BUNDLES 	${ROOT}/scripts/mobile/*.ibundle)
install (
    FILES   ${BUNDLES} DESTINATION ${INSTALL_BUNDLES}
    PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ
)

####################################
# install tools
install (
    DIRECTORY     "${ROOT}/scripts/Tools/drawmap" DESTINATION ${INSTALL_TOOLS}
    FILE_PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ
    DIRECTORY_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
    	GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
    PATTERN ".DS_Store" EXCLUDE
    PATTERN ".*.jpg" EXCLUDE
)

####################################
# install interfaces
install (
    DIRECTORY     "${ROOT}/interfaces" DESTINATION ${INSTALL_INTERFACES}
    FILE_PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ
    DIRECTORY_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
    	GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
    PATTERN ".DS_Store" EXCLUDE
)

####################################
# install fonts
if (UNIX AND NOT APPLE)
	set (INSTALL_FONTS ${CMAKE_INSTALL_PREFIX}/share/fonts/inscore)
else ()
	set (INSTALL_FONTS ${CMAKE_INSTALL_PREFIX}/Fonts)
endif()
set (FONTS ${GUIDOLIB}/src/guido2.ttf ${ROOT}/rsrc/fonts/Carlito-Regular.ttf)
install (
    FILES   ${FONTS} DESTINATION ${INSTALL_FONTS}
    PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ
)

####################################
# install libmusicxml
if (APPLE)
	file (GLOB OLIBS ${CMAKE_CURRENT_SOURCE_DIR}/lib/libmusicxml2.*)
	set (INSTALL_OLIB ${INSTALL_BIN}/${viewer}.app/Contents/Frameworks)
elseif (WIN32)
	set (OLIBS ${GUIDO_DLL} ${LIBXML}/build/lib/musicxml2.dll)
	set (INSTALL_OLIB ${INSTALL_BIN})
else ()
	file (GLOB OLIBS ${CMAKE_CURRENT_SOURCE_DIR}/lib/libmusicxml2.*  ${CMAKE_CURRENT_SOURCE_DIR}/lib/libGUIDOEngine.*)
	set (INSTALL_OLIB ${INSTALL_LIB})
endif()
install (
	FILES   ${OLIBS} DESTINATION ${INSTALL_OLIB}
	PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ
)

####################################
# install linux specific files
if (UNIX AND NOT APPLE)
	set (URSRC ${ROOT}/package/rsrc/share)
	install ( FILES   ${URSRC}/applications/inscore.desktop DESTINATION ${INSTALL_SHARED}/applications PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ )
	install ( FILES   ${URSRC}/icons/hicolor/128x128/apps/inscore.png DESTINATION ${INSTALL_SHARED}/icons/hicolor/128x128/apps PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ )
	install ( FILES   ${URSRC}/icons/hicolor/48x48/apps/inscore.png DESTINATION ${INSTALL_SHARED}/icons/hicolor/48x48/apps PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ )
endif()

####################################
# cpack section
####################################
set (CPACK_PACKAGE_NAME   "INScore")
set (CPACK_PACKAGE_VENDOR "GRAME")
set (CPACK_PACKAGE_DESCRIPTION_SUMMARY "INScore - an environment for the design of interactive, augmented, dynamic music scores.")
set (CPACK_PACKAGE_VERSION   ${VERSION})
set (CPACK_PACKAGE_VERSION_MAJOR   ${VERSION_MAJOR})
set (CPACK_PACKAGE_VERSION_MINOR   ${VERSION_MINOR})
set (CPACK_PACKAGE_VERSION_PATCH   ${VERSION_PATCH})

set (CPACK_MONOLITHIC_INSTALL true)
set (CPACK_RESOURCE_FILE_LICENSE  ${ROOT}/src/license.txt)
set (CPACK_PACKAGE_INSTALL_DIRECTORY  INScore)

####################################
# NSIS specific section
set (CPACK_NSIS_INSTALL_ROOT "C:\\\\Program Files")
set (CPACK_NSIS_MODIFY_PATH on)
set (CPACK_NSIS_MUI_ICON "${ROOT}/rsrc/ITLViewer.ico")

include (CPack)
