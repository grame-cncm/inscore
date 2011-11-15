cmake_minimum_required(VERSION 2.6)
project(INScore)

#######################################
# cmake build types configuration
set (CMAKE_CONFIGURATION_TYPES Debug Release)

set (TARGET	INScore)
set (APPLTARGET	INScoreViewer)
#######################################
# versions management
set (INSFWKVERS 0.96)
set (INSFWKSTRVERS "v.0.96")
set (INSFWKSSTRVERS "0.96")
set (INSTEXTVERS 0.96)
set (INSTEXTSTRVERS "v.0.96")
set (INSTEXTSSTRVERS "0.96")
set (INSAPPVERS 0.96)
set (INSAPPSTRVERS "v.0.96")
set (INSAPPSSTRVERS "0.96")

#######################################
if(WIN32)
if(MSVC)
	add_definitions(-DMSVC -D_USE_MATH_DEFINES)
endif(MSVC)
else(WIN32)
	add_definitions(-Wall)
endif(WIN32)

if(APPLE)
	if (${CMAKE_SYSTEM_VERSION} VERSION_LESS 9.0.0)
		set (CMAKE_OSX_SYSROOT /Developer/SDKs/MacOSX10.4u.sdk)
	else (${CMAKE_SYSTEM_VERSION} VERSION_LESS 9.0.0)
		set (CMAKE_OSX_SYSROOT /Developer/SDKs/MacOSX10.5.sdk)
	endif (${CMAKE_SYSTEM_VERSION} VERSION_LESS 9.0.0)

#if (NOT (JAVASCRIPT STREQUAL "yes"))
	set (CMAKE_OSX_ARCHITECTURES "i386 x86_64")
#endif (NOT (JAVASCRIPT STREQUAL "yes"))
	set (CMAKE_C++_FLAGS -mmacosx-version-min=10.4)
endif(APPLE)

#######################################
# set directories, src and headers.
set (ROOT ${CMAKE_CURRENT_SOURCE_DIR}/../src)
set (INSFOLDERS  controller events lib model view mapping interface graph signal signal/faust ITLParser scripting)
set (RSRC  "${ROOT}/../rsrc")
set (LOCALLIB  "${ROOT}/../lib")
set (OSC_PATH  "${LOCALLIB}/oscpack")
set (GUIDO_PATH  "${LOCALLIB}/GuidoEngine")
set (GUIDOQT_PATH  "${LOCALLIB}/GuidoQt")


set (SCRIPT "")
set (SCRIPTINCL "")
#######################################
# lua support
if (LUA STREQUAL "yes")
	message (STATUS "lua will be supported - Use -DLUA=no to change.")
	add_definitions(-DLUA)
	if (WIN32)
		set(SCRIPTS ${SCRIPTS} ${LOCALLIB}/lua/win32/lua.lib)
		set(SCRIPTINCL ${SCRIPTINCL} ${LOCALLIB}/lua/win32/)
	else(WIN32)
		set(SCRIPTS ${SCRIPTS} -llua)
		set(SCRIPTINCL ${SCRIPTINCL} /usr/local/include)
	endif (WIN32)
else (LUA STREQUAL "yes")
	message (STATUS "lua will not be supported - Use -DLUA=yes to change")
endif (LUA STREQUAL "yes")

#######################################
# javascript support
if (JAVASCRIPT STREQUAL "yes")
	message (STATUS "javascript will be supported - Use -DJAVASCRIPT=no to change.")
	add_definitions(-DJAVASCRIPT)
	if (WIN32)
		set(SCRIPTS ${SCRIPTS} "${LOCALLIB}/javascript/win32/javascript.lib")
	else(WIN32)
		if(APPLE)
			set(SCRIPTS ${SCRIPTS} -L${LOCALLIB}/javascript/MacOS -lmozjs185-1.0)
			set(SCRIPTINCL ${SCRIPTINCL} ${LOCALLIB}/javascript/MacOS)
		else(APPLE)
			set(SCRIPTS ${SCRIPTS} -lmozjs185-1.0)
		endif(APPLE)
	endif (WIN32)
else (JAVASCRIPT STREQUAL "yes")
	message (STATUS "javascript will not be supported - Use -DJAVASCRIPT=yes to change")
endif (JAVASCRIPT STREQUAL "yes")

#######################################
#
if(MSVC)
	set (INSFOLDERS  ${INSFOLDERS} ../win32/dirent)
endif(MSVC)

foreach(folder ${INSFOLDERS})
	set(SRC ${SRC} "${ROOT}/${folder}/*.cpp")			# add source files
endforeach(folder)
set(SRC ${SRC} "${ROOT}/atomic/*.cpp")
if(MSVC)
	enable_language(RC)
	set(SRC ${SRC} ../win32/${TARGET}.rc)
endif(MSVC)
file (GLOB CORESRC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${SRC})

foreach(folder ${INSFOLDERS})
	set(HEADERS ${HEADERS} "${ROOT}/${folder}/*.h")		# add header files
endforeach(folder)
file (GLOB COREH RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${HEADERS})

foreach(folder ${INSFOLDERS})
	set(INCL ${INCL} "${ROOT}/${folder}")				# add include folders
endforeach(folder)
set(INCL ${INCL} "${ROOT}/atomic" ${SCRIPTINCL})


#######################################
# qt setup

if(APPLE OR WIN32)
  set(DESIRED_QT_VERSION 4.7)
  FIND_PACKAGE(QT4 REQUIRED)
 #message("QT_LIBRARY_DIR ${QT_LIBRARY_DIR}")
 #message("QT_INCLUDE_DIR ${QT_INCLUDE_DIR}")
 #message("QT_QTCORE_INCLUDE_DIR ${QT_QTCORE_INCLUDE_DIR}")
 #message("QT_QTGUI_INCLUDE_DIR ${QT_QTGUI_INCLUDE_DIR}")

else(APPLE OR WIN32)
  set(DESIRED_QT_VERSION 4.6)
  FIND_PACKAGE(Qt4 REQUIRED)
  set (QTLIBS "-lQtCore -lQtGui -lQtSvg -lphonon" )
endif(APPLE OR WIN32)

if(APPLE)
	set (QTLIBS "-framework QtCore -framework QtGui -framework QtSvg -framework phonon" )
	set (CORE_FOUNDATION "-framework CoreFoundation")
endif(APPLE)

if(WIN32)
	if(MINGW)
		set(QTLIBS "${QT_LIBRARY_DIR}/libQtCore4.a" "${QT_LIBRARY_DIR}/libQtGui4.a"  "${QT_LIBRARY_DIR}/libQtSvg4.a" "${QT_LIBRARY_DIR}/libQtXml4.a" "${QT_LIBRARY_DIR}/libphonon4.a" )
	else(MINGW)
		set(QTLIBS "${QT_LIBRARY_DIR}/QtCore4.lib" "${QT_LIBRARY_DIR}/QtGui4.lib"  "${QT_LIBRARY_DIR}/QtSvg4.lib" "${QT_LIBRARY_DIR}/QtXml4.lib" "${QT_LIBRARY_DIR}/phonon4.lib" )
	endif(MINGW)
endif(WIN32)

set (QTHEADERS "${QT_INCLUDE_DIR}" "${QT_QTCORE_INCLUDE_DIR}" "${QT_QTGUI_INCLUDE_DIR}" "${QT_QTSVG_INCLUDE_DIR}" "${QT_PHONON_INCLUDE_DIR}")
file (GLOB PUBLICHEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${ROOT}/interface/INScore.h)

#######################################
# set libraries
if(WIN32)
	if(MINGW)
		set(OSCPACK  ${OSC_PATH}/MinGW/liboscpack.a)
		set(GUIDOQT  ${LOCALLIB}/GuidoQt/win32/libGuidoQt.a)
		set(GUIDO    ${LOCALLIB}/GuidoEngine/win32/libGUIDOEngine.dll.a)
	else(MINGW)
		set(OSCPACK  ${OSC_PATH}/cmake/release/oscpack.lib)
		set(GUIDOQT  ${LOCALLIB}/GuidoQt/win32/GuidoQt.lib)
		set(GUIDO    ${LOCALLIB}/GuidoEngine/win32/GUIDOEngine.lib)
		set(INSLIBS  winmm.lib ws2_32.lib)
	endif(MINGW)
endif(WIN32)

if(APPLE)
	set(OSCPACK  ${OSC_PATH}/cmake/Release/liboscpack.a)
	set(GUIDOQT  ${ROOT}/../lib/GuidoQt/macosx/libGuidoQt.a)
	set(GUIDO    ${ROOT}/../lib/GuidoEngine/macosx/GUIDOEngine.framework)
elseif(UNIX)
	set(OSCPACK  -L${OSC_PATH}/cmake -loscpack)
	set(GUIDOQT  -L${ROOT}/../lib/GuidoQt/linux -lGuidoQt)
	set(GUIDO    -lGUIDOEngine)
endif(APPLE)

set(INSLIBS  ${INSLIBS} ${OSCPACK} ${GUIDOQT} ${GUIDO} ${SCRIPTS} ${QTLIBS} ${CORE_FOUNDATION} )

#######################################
# moc settings
set (MOC_HEADERS ${ROOT}/view/VSceneView.h ${ROOT}/model/QFileWatcher.h)
QT_WRAP_CPP (${TARGET} MOC_FILES ${MOC_HEADERS})
QT_WRAP_CPP (${APPLTARGET} APPL_MOC_FILES ${ROOT}/INScoreAppl.h)

SET(QtApp_RCCS  ${ROOT}/../rsrc/inscore.qrc)
#SET(INScoreQRC  inscore.qrc)
QT4_ADD_RESOURCES(INScoreQRC ${QtApp_RCCS})

#######################################
# set targets
include_directories(${INCL} ${OSC_PATH} ${GUIDO_PATH}/include ${GUIDOQT_PATH}/include ${QTHEADERS} )

add_library( ${TARGET} SHARED ${CORESRC} ${COREH} ${MOC_FILES})
set_source_files_properties (${COREH} PROPERTIES HEADER_FILE_ONLY TRUE)
set_target_properties (${TARGET} PROPERTIES VERSION ${INSFWKVERS}
						MACOSX_FRAMEWORK_SHORT_VERSION_STRING ${INSFWKSTRVERS}
						MACOSX_FRAMEWORK_BUNDLE_VERSION ${INSFWKSSTRVERS}
						PUBLIC_HEADER "${PUBLICHEADERS}"
)
target_link_libraries( ${TARGET} ${INSLIBS} )
if(MINGW)
	target_link_libraries( ${TARGET} winmm ws2_32 )
endif(MINGW)


add_executable( ${APPLTARGET}  MACOSX_BUNDLE ${ROOT}/INScoreAppl.cpp ${APPL_MOC_FILES}  ../win32/Viewer/${APPLTARGET}.rc ${INScoreQRC})
target_link_libraries( ${APPLTARGET} ${QTLIBS} ${GUIDO})
set_target_properties (${APPLTARGET} PROPERTIES VERSION ${INSAPPVERS}
							MACOSX_BUNDLE_ICON_FILE ${RSRC}/${APPLTARGET}.icns
							MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/Info.plist"
							MACOSX_BUNDLE_SHORT_VERSION_STRING ${INSAPPSTRVERS}
							MACOSX_BUNDLE_BUNDLE_VERSION ${INSAPPSSTRVERS})
if(WIN32)
set_target_properties (${APPLTARGET} PROPERTIES
	LINK_FLAGS_RELEASE /subsystem:windows
	LINK_FLAGS_DEBUG /subsystem:console)
endif(WIN32)

if(APPLE)
	set_target_properties (${TARGET} PROPERTIES FRAMEWORK TRUE FRAMEWORK_VERSION ${INSFWKVERS})
endif(APPLE)

target_link_libraries( ${APPLTARGET} ${TARGET})
add_dependencies(${APPLTARGET} ${TARGET})

#######################################
# install setup
if(APPLE)
set(FRMWK  FRAMEWORK DESTINATION "/Library/Frameworks" CONFIGURATIONS Release)
set(APPBUNDLE BUNDLE DESTINATION "/Applications/INScore-${INSAPPVERS}"  CONFIGURATIONS Release)
endif(APPLE)

if (WIN32)

else (WIN32)
install ( TARGETS ${TARGET}
    	LIBRARY DESTINATION /usr/local/lib
     	PUBLIC_HEADER DESTINATION /usr/local/include
   		${FRMWK}
)
install ( TARGETS ${APPLTARGET}
	RUNTIME DESTINATION /usr/bin
    ${APPBUNDLE}
)
endif (WIN32)

