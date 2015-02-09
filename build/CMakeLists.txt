cmake_minimum_required(VERSION 2.6)
project(INScore)

#######################################
# cmake build types configuration
set (CMAKE_CONFIGURATION_TYPES Debug Release)

set (TARGET	INScore)
set (APPLTARGET	INScoreViewer)

#######################################
# versions management
set (INSFWKVERS 1.10)
set (INSFWKSTRVERS "v.1.10")
set (INSAPPVERS 1.10)
set (INSAPPSTRVERS "v.1.10")
set (SOVERS 1)


#######################################
# Options disabled by default
option ( NOVIEW 	"compiles a viewer with no view (for debug purpose)" off )
option ( LUA 		"embed a lua engine" off )
option ( DIST 		"compiles universal binaries (x86_64 i386) - MacOSX only" off )
option ( QJS 		"use the QJSEngine for javascript support" off )

#######################################
if(WIN32)
	if (${CMAKE_GENERATOR} MATCHES ".*Win64")
		set (TARGET	INScore64)
		set (X64 -D__x86_64__)
	endif()

	if(${CMAKE_GENERATOR} STREQUAL "Visual Studio 10")
		set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc")
	endif()
	add_definitions(-DMSVC -D_USE_MATH_DEFINES ${X64})
else()
	add_definitions(-Wall)
	if (NOT APPLE)
		add_definitions(-fPIC)
	endif()
endif()

if(APPLE)
#######################################
#   iOS support
	if ( IOS )
		message (STATUS "Generates project for iOS - Use -DIOS=no to change.")
		set (CMAKE_XCODE_EFFECTIVE_PLATFORMS "iPhoneOS")
		set (CMAKE_OSX_ARCHITECTURES "armv7 armv7s armv7")
		set (CMAKE_OSX_SYSROOT "iphoneos")
		set (libtype STATIC)
	else ()
		 if ( DIST )
			message (STATUS "All architectures will be compiled - Use -DDIST=no to change.")
			set (CMAKE_OSX_ARCHITECTURES "x86_64 i386")
		 else ()
			message (STATUS "Only the current architecture will be compiled - Use -DDIST=yes to change.")
		 endif ()
		 # drag & drop doesn't work with macosx10.10 sdk on yosemite
		 if (CMAKE_OSX_SYSROOT STREQUAL /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.10.sdk)
			 set (CMAKE_OSX_SYSROOT /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.9.sdk)
			 message (STATUS "Changing SDK to MacOSX10.9.sdk")
		 endif()
		 set (CMAKE_OSX_DEPLOYMENT_TARGET 10.6)
		 set (MACOSX_DEPLOYMENT_TARGET 10.6)
		 set (CMAKE_C++_FLAGS -mmacosx-version-min=10.6)
	endif()
endif()

#######################################
# set directories, src and headers.
set (ROOT ${CMAKE_CURRENT_SOURCE_DIR}/../src)
set (MAP ${ROOT}/libmapping)
set (INSFOLDERS  controller events lib model view mapping interface graph signal signal/faust ITLParser scripting)
set (INSFOLDERS  ${INSFOLDERS} plugins/gesturefollower)
set (INSFOLDERS  ${INSFOLDERS} plugins/faustDSP)
set (LIBMAPFOLDERS libmapping/src/misc libmapping/src/parser libmapping/src/relations libmapping/src/segments)
set (RSRC  "${ROOT}/../rsrc")
set (LOCALLIB  "${ROOT}/../lib")
set (OSC_PATH  "${LOCALLIB}/oscpack")
set (GUIDO_PATH  "${LOCALLIB}/GuidoEngine")
set (GUIDOQT_PATH  "${LOCALLIB}/GuidoQt")

#######################################
# validation support
if ( NOVIEW )
	message (STATUS "Compiled with no view - Use -DNOVIEW=off to change.")
	add_definitions(-DNOVIEW)
	set (INSFOLDERS  ${INSFOLDERS} VoidView)
else()
	message (STATUS "Using standard Qt view - Use -DNOVIEW=on to change")
endif()


set (SCRIPT "")
set (SCRIPTINCL "")
#######################################
# lua support
if (LUA)
	message (STATUS "lua will be supported - Use -DLUA=off to change.")
	add_definitions(-DLUA)
	if (WIN32)
		set(SCRIPTS ${SCRIPTS} ${LOCALLIB}/lua/win32/lua.lib)
		set(SCRIPTINCL ${SCRIPTINCL} ${LOCALLIB}/lua/win32/)
	elif(APPLE)
		set(SCRIPTS ${SCRIPTS} -llua)
		set(SCRIPTINCL ${SCRIPTINCL} /usr/local/include)
	else ()
		EXECUTE_PROCESS ( COMMAND "pkg-config" "--cflags" "lua"
			OUTPUT_VARIABLE TMP
			ERROR_VARIABLE TMP
		)
		string(STRIP ${TMP} LUACFG)
		add_definitions(${LUACFG})
		EXECUTE_PROCESS ( COMMAND "pkg-config" "--libs" "lua"
			OUTPUT_VARIABLE TMP
			ERROR_VARIABLE TMP
		)
		string(STRIP ${TMP} LUACFG)
		set(SCRIPTS ${SCRIPTS} ${LUACFG})
	endif()
else()
	message (STATUS "lua will not be supported - Use -DLUA=on to change")
endif()

#######################################
# javascript support
if(QJS)
	message (STATUS "Qt Javascript engine will be used. Use -DQJS=off to change")
	add_definitions(-DQTJSENGINE)
else()
	message (STATUS "V8 Javascript engine will be used. Use -DQJS=on to change to QJSEngine")
	add_definitions(-DV8ENGINE)
	if (WIN32)
		set(SCRIPTS ${SCRIPTS} "${LOCALLIB}/javascript/v8/win32/v8.lib")
		set(SCRIPTINCL ${SCRIPTINCL} ${LOCALLIB}/javascript/v8/include)
	else()
		if(APPLE)
			set(SCRIPTINCL ${SCRIPTINCL} ${LOCALLIB}/javascript/v8/include)
			set(SCRIPTS ${SCRIPTS} -L${LOCALLIB}/javascript/v8/MacOS -lv8)
		else()
			set(SCRIPTS ${SCRIPTS} -lv8) # on linux, use of the v8 package
		endif()
	endif ()
endif ()

#######################################
#
if(MSVC)
	set (INSFOLDERS  ${INSFOLDERS} ../win32/dirent)
endif(MSVC)

foreach(folder ${INSFOLDERS})
	set(SRC ${SRC} "${ROOT}/${folder}/*.cpp")			# add source files
endforeach()
foreach(folder ${LIBMAPFOLDERS})
	set(SRC ${SRC} "${ROOT}/${folder}/*.cpp")			# add source files
endforeach()
set(SRC ${SRC} "${ROOT}/atomic/*.cpp")

if(MSVC)
	enable_language(RC)
	set(SRC ${SRC} ../win32/${TARGET}.rc)
endif()
file (GLOB CORESRC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${SRC})

foreach(folder ${INSFOLDERS})
	set(HEADERS ${HEADERS} "${ROOT}/${folder}/*.h")		# add header files
endforeach()
file (GLOB COREH RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${HEADERS})

foreach(folder ${INSFOLDERS} ${LIBMAPFOLDERS})
	set(INCL ${INCL} "${ROOT}/${folder}")				# add include folders
endforeach()
set(INCL ${INCL} "${ROOT}/atomic" ${SCRIPTINCL})


#######################################
# qt setup
if (NOT DEFINED QTVERSION) 
set (QTVERSION 5)
endif()

message (STATUS "Using Qt version ${QTVERSION} - Use -DQTVERSION=vers to change.")

set (MOC_HEADERS ${ROOT}/view/VSceneView.h ${ROOT}/model/QFileWatcher.h  ${ROOT}/view/VLogWindow.h)
if (QTVERSION EQUAL "5")
	set (MOC_HEADERS ${MOC_HEADERS} ${ROOT}/view/VVideoView.h ${ROOT}/controller/QFileDownloader.h)
	set(DESIRED_QT_VERSION 5.0)
	FIND_PACKAGE(Qt5Widgets REQUIRED)
	FIND_PACKAGE(Qt5Svg REQUIRED)
	FIND_PACKAGE(Qt5PrintSupport REQUIRED)
	FIND_PACKAGE(Qt5Multimedia REQUIRED)
	FIND_PACKAGE(Qt5MultimediaWidgets REQUIRED)
	FIND_PACKAGE(Qt5Qml REQUIRED)
	if(APPLE OR WIN32)
	  set(QTLIBS ${Qt5Core_LIBRARIES}  ${Qt5Gui_LIBRARIES} ${Qt5Widgets_LIBRARIES} ${Qt5Svg_LIBRARIES} ${Qt5PrintSupport_LIBRARIES} ${Qt5Multimedia_LIBRARIES} ${Qt5MultimediaWidgets_LIBRARIES}  ${Qt5Qml_LIBRARIES})	
	else()
	  set(QTLIBS "-lQt5Core -lQt5Gui -lQt5Widgets -lQt5Svg -lQt5PrintSupport -lQt5Multimedia -lQt5MultimediaWidgets  -lQt5Qml")	
	endif()

	set (QTHEADERS ${Qt5Widgets_INCLUDE_DIRS} ${Qt5Svg_INCLUDE_DIRS} 	${Qt5PrintSupport_INCLUDE_DIRS}  ${Qt5Multimedia_INCLUDE_DIRS}  ${Qt5MultimediaWidgets_INCLUDE_DIRS} ${Qt5Qml_INCLUDE_DIRS})
else ()   # assume we're using Qt4
	add_definitions(-DUSEPHONON)

	if(APPLE OR WIN32)
	  set(DESIRED_QT_VERSION 4.7)
	  FIND_PACKAGE(QT4 REQUIRED)
	else()
	  set(DESIRED_QT_VERSION 4.6)
	  FIND_PACKAGE(Qt4 REQUIRED)
	  set (QTLIBS "-lQtCore -lQtGui -lQtSvg -lphonon" )
	endif()
	
	if(APPLE)
		set (QTLIBS "-framework QtCore -framework QtGui -framework QtSvg -framework phonon" )
	endif()
	
	if(WIN32)
		set(QTLIBS "${QT_LIBRARY_DIR}/QtCore4.lib" "${QT_LIBRARY_DIR}/QtGui4.lib"  "${QT_LIBRARY_DIR}/QtSvg4.lib" "${QT_LIBRARY_DIR}/QtXml4.lib" "${QT_LIBRARY_DIR}/phonon4.lib" )
	endif()
	
	set (QTHEADERS "${QT_INCLUDE_DIR}" "${QT_QTCORE_INCLUDE_DIR}" "${QT_QTGUI_INCLUDE_DIR}" "${QT_QTSVG_INCLUDE_DIR}" "${QT_PHONON_INCLUDE_DIR}")

endif()

if(APPLE)
	set (CORE_FOUNDATION "-framework CoreFoundation")
endif()
file (GLOB PUBLICHEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${ROOT}/interface/INScore.h)

#######################################
# set libraries
if(WIN32)
	if(MINGW)
		set(OSCPACK  ${OSC_PATH}/MinGW/liboscpack.a)
		set(GUIDOQT  ${LOCALLIB}/GuidoQt/win32/libGuidoQt.a)
		set(GUIDO    ${LOCALLIB}/GuidoEngine/win32/libGUIDOEngine.dll.a)
	else()
		set(OSCPACK  ${OSC_PATH}/cmake/release/oscpack.lib)
		set(GUIDOQT  optimized ${LOCALLIB}/GuidoQt/win32/GuidoQt.lib debug ${LOCALLIB}/GuidoQt/win32/GuidoQtD.lib)
		set(GUIDO    ${LOCALLIB}/GuidoEngine/win32/GUIDOEngine.lib)
		set(INSLIBS  winmm.lib ws2_32.lib)
	endif()
endif()

if(APPLE)
	if ( IOS )
		message (STATUS "Generates project for iOS - Use -DIOS=no to change.")
		set(OSCPACK  ${OSC_PATH}/build/iOS/Release-iphoneos/liboscpack.a)
		set(GUIDOQT  ${ROOT}/../lib/GuidoQt/ios/libGuidoQt.a)
		set(GUIDO    ${ROOT}/../lib/GuidoEngine/ios/libGUIDOEngine.a)
	else()
		message (STATUS "Generates project for iOS - Use -DIOS=yes to change.")
		set(OSCPACK  ${OSC_PATH}/build/MacOS/Release/liboscpack.a)
		set(GUIDOQT  ${ROOT}/../lib/GuidoQt/macosx/libGuidoQt.a)
		set(GUIDO    ${ROOT}/../lib/GuidoEngine/macosx/GUIDOEngine.framework)
	endif()
elseif(UNIX)
	set(OSCPACK  -L${OSC_PATH}/cmake -loscpack)
	set(GUIDOQT  -L${ROOT}/../lib/GuidoQt/linux -lGuidoQt)
	set(GUIDO    -lGUIDOEngine)
endif()

set(INSLIBS  ${INSLIBS} ${OSCPACK} ${SCRIPTS} ${QTLIBS} ${CORE_FOUNDATION} ${GUIDO} ${GUIDOQT} )

#######################################
# moc settings
QT_WRAP_CPP (${TARGET} MOC_FILES ${MOC_HEADERS})
QT_WRAP_CPP (${APPLTARGET} APPL_MOC_FILES ${ROOT}/INScoreAppl.h )

SET(QtApp_RCCS  ${ROOT}/../rsrc/inscore.qrc)
if (QTVERSION EQUAL "5")
	QT5_ADD_RESOURCES(INScoreQRC ${QtApp_RCCS})
else()
	QT4_ADD_RESOURCES(INScoreQRC ${QtApp_RCCS})
endif()

#######################################
# set targets
include_directories(${INCL} ${OSC_PATH} ${GUIDO_PATH}/include ${GUIDOQT_PATH}/include ${QTHEADERS} )

if (IOS)
	add_library( ${TARGET} STATIC ${CORESRC} ${COREH} ${MOC_FILES})
else()

	add_library( ${TARGET} SHARED ${CORESRC} ${COREH} ${MOC_FILES})
	set_source_files_properties (${COREH} PROPERTIES HEADER_FILE_ONLY TRUE)
	set_target_properties (${TARGET} PROPERTIES 
				VERSION ${INSFWKVERS}
				SOVERSION ${SOVERS}
				MACOSX_FRAMEWORK_SHORT_VERSION_STRING ${INSFWKSTRVERS}
				MACOSX_FRAMEWORK_BUNDLE_VERSION ${INSFWKVERS}
				PUBLIC_HEADER "${PUBLICHEADERS}"
	)
	target_link_libraries( ${TARGET} ${INSLIBS} )
endif()

if(MINGW)
	target_link_libraries( ${TARGET} winmm ws2_32 )
endif()


set(INScoreIcon ${CMAKE_CURRENT_SOURCE_DIR}/../rsrc/INScoreViewer.icns)
set_source_files_properties(${INScoreIcon} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")

if (NOVIEW)
	set (APPLTARGET  INScoreNOView)
	add_executable( ${APPLTARGET}  ${ROOT}/INScoreNoView.cpp )
else()
	add_executable( ${APPLTARGET}  MACOSX_BUNDLE ${INScoreIcon} ${ROOT}/INScoreAppl.cpp ${APPL_MOC_FILES}  ../win32/Viewer/${APPLTARGET}.rc ${INScoreQRC})
endif()

#target_link_libraries( ${APPLTARGET} ${QTLIBS} ${GUIDO})
set_target_properties (${APPLTARGET} PROPERTIES VERSION ${INSAPPVERS}
							MACOSX_BUNDLE_ICON_FILE INScoreViewer.icns
							MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/Info.plist"
							MACOSX_BUNDLE_SHORT_VERSION_STRING ${INSAPPSTRVERS}
							MACOSX_BUNDLE_BUNDLE_VERSION ${INSAPPVERS})
if(WIN32)
set_target_properties (${APPLTARGET} PROPERTIES
	LINK_FLAGS_RELEASE /subsystem:windows
	LINK_FLAGS_DEBUG /subsystem:console)
elseif(UNIX AND NOT APPLE)
	set_target_properties (${APPLTARGET} PROPERTIES OUTPUT_NAME inscoreviewer)
endif()

if(APPLE)
	set_target_properties (${TARGET} PROPERTIES FRAMEWORK TRUE FRAMEWORK_VERSION ${INSFWKVERS})
endif()

target_link_libraries( ${APPLTARGET} ${TARGET} ${QTLIBS} ${GUIDO})
add_dependencies(${APPLTARGET} ${TARGET})

#include ( report.cmake )

#######################################
# install setup
if (NOT IOS)
if(APPLE)
set(FRMWK  FRAMEWORK DESTINATION "/Library/Frameworks" CONFIGURATIONS Release)
set(APPBUNDLE BUNDLE DESTINATION "/Applications/INScore-${INSAPPVERS}"  CONFIGURATIONS Release)
endif()

if (WIN32)

else (WIN32)
install ( TARGETS ${TARGET}
    	LIBRARY DESTINATION /usr/lib
     	PUBLIC_HEADER DESTINATION /usr/local/include
   		${FRMWK}
)
install ( TARGETS ${APPLTARGET}
	RUNTIME DESTINATION /usr/bin
    ${APPBUNDLE}
)
endif ()
endif ()

