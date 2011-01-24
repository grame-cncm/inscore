cmake_minimum_required(VERSION 2.6)
project(INScore)

#######################################
# cmake build types configuration
set (CMAKE_CONFIGURATION_TYPES Debug Release)

set (TARGET	INScore)
#######################################
# versions management
set (INSFWKVERS 0.63)
set (INSFWKSTRVERS "v.0.63")
set (INSFWKSSTRVERS "0.63")
set (INSTEXTVERS 0.63)
set (INSTEXTSTRVERS "v.0.63")
set (INSTEXTSSTRVERS "0.63")
set (INSAPPVERS 0.63)
set (INSAPPSTRVERS "v.0.63")
set (INSAPPSSTRVERS "0.63")

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

	set (CMAKE_OSX_ARCHITECTURES "i386 x86_64")
	set (CMAKE_C++_FLAGS -mmacosx-version-min=10.4)
endif(APPLE)

#######################################
# set directories, src and headers.
set (ROOT ${CMAKE_CURRENT_SOURCE_DIR}/../src)
set (INSFOLDERS  controller events lib model view mapping interface graph signal ITLParser)
set (RSRC  "${ROOT}/../rsrc")
set (LOCALLIB  "${ROOT}/../lib")
set (OSC_PATH  "${LOCALLIB}/oscpack")
set (GUIDO_PATH  "${LOCALLIB}/GuidoEngine")
set (GUIDOQT_PATH  "${LOCALLIB}/GuidoQt")

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
set(INCL ${INCL} "${ROOT}/atomic")


#######################################
# qt setup

if(APPLE OR WIN32)
  set(DESIRED_QT_VERSION 4.6)
  FIND_PACKAGE(QT REQUIRED)
# message("QT_LIBRARY_DIR ${QT_LIBRARY_DIR}")
# message("QT_INCLUDE_DIR ${QT_INCLUDE_DIR}")
# message("QT_QTCORE_INCLUDE_DIR ${QT_QTCORE_INCLUDE_DIR}")
# message("QT_QTGUI_INCLUDE_DIR ${QT_QTGUI_INCLUDE_DIR}")

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
		set(QTLIBS "${QT_LIBRARY_DIR}/libQtCore4.a" "${QT_LIBRARY_DIR}/libQtGui4.a"  "${QT_LIBRARY_DIR}/libQtSvg4.a" "${QT_LIBRARY_DIR}/libQtXml4.a" "${QT_LIBRARY_DIR}/phonon4.lib" )
	else(MINGW)
		set(QTLIBS "${QT_LIBRARY_DIR}/QtCore4.lib" "${QT_LIBRARY_DIR}/QtGui4.lib"  "${QT_LIBRARY_DIR}/QtSvg4.lib" "${QT_LIBRARY_DIR}/QtXml4.lib" "${QT_LIBRARY_DIR}/phonon4.lib" )
	endif(MINGW)
endif(WIN32)

set (QTHEADERS "${QT_INCLUDE_DIR}" "${QT_QTCORE_INCLUDE_DIR}" "${QT_QTGUI_INCLUDE_DIR}" "${QT_QTSVG_INCLUDE_DIR}" "${QT_PHONON_INCLUDE_DIR}")
file (GLOB PUBLICHEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "${ROOT}/interface/*.h")

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

set(INSLIBS  ${INSLIBS} ${OSCPACK} ${GUIDOQT} ${GUIDO} ${QTLIBS} ${CORE_FOUNDATION} )

#######################################
# moc settings
set (MOC_HEADERS ${ROOT}/view/VSceneView.h ${ROOT}/model/QFileWatcher.h)
QT_WRAP_CPP (${TARGET} MOC_FILES ${MOC_HEADERS})

#######################################
# set targets
include_directories(${INCL} ${OSC_PATH} ${GUIDO_PATH}/include ${GUIDOQT_PATH}/include ${QTHEADERS} )

add_library( ${TARGET} SHARED ${CORESRC} ${COREH} ${MOC_FILES})
set_source_files_properties (${COREH} PROPERTIES HEADER_FILE_ONLY TRUE)
set_target_properties (${TARGET} PROPERTIES VERSION ${INSFWKVERS}
						MACOSX_FRAMEWORK_SHORT_VERSION_STRING ${INSFWKSTRVERS}
						MACOSX_FRAMEWORK_BUNDLE_VERSION ${INSFWKSSTRVERS}
#						PUBLIC_HEADER "${PUBLICHEADERS}"
)
target_link_libraries( ${TARGET} ${INSLIBS} )
if(MINGW)
	target_link_libraries( ${TARGET} winmm ws2_32 )
endif(MINGW)


add_executable( ${TARGET}Viewer  MACOSX_BUNDLE ${ROOT}/INScore.cpp ../win32/Viewer/${TARGET}Viewer.rc)
target_link_libraries( ${TARGET}Viewer ${QTLIBS} ${GUIDO})
set_target_properties (${TARGET}Viewer PROPERTIES VERSION ${INSAPPVERS}
							MACOSX_BUNDLE_ICON_FILE ${RSRC}/${TARGET}Viewer.icns
							MACOSX_BUNDLE_SHORT_VERSION_STRING ${INSAPPSTRVERS}
							MACOSX_BUNDLE_BUNDLE_VERSION ${INSAPPSSTRVERS})
if(WIN32)
set_target_properties (${TARGET}Viewer PROPERTIES
	LINK_FLAGS_RELEASE /subsystem:windows
	LINK_FLAGS_DEBUG /subsystem:console)
endif(WIN32)

if(WIN32)
set_target_properties (${TARGET}Viewer PROPERTIES
	LINK_FLAGS_RELEASE /subsystem:windows
	LINK_FLAGS_DEBUG /subsystem:console)
endif(WIN32)

if(APPLE)
	set_target_properties (${TARGET} PROPERTIES FRAMEWORK TRUE FRAMEWORK_VERSION ${INSFWKVERS})
endif(APPLE)

target_link_libraries( ${TARGET}Viewer ${TARGET})
add_dependencies(${TARGET}Viewer ${TARGET})

#######################################
# install setup
if(APPLE)
set(FRMWK  FRAMEWORK DESTINATION "/Library/Frameworks" CONFIGURATIONS Release)
set(APPBUNDLE BUNDLE DESTINATION "/Applications/INScore-${INSAPPVERS}"  CONFIGURATIONS Release)
endif(APPLE)

install ( TARGETS ${TARGET}
    	LIBRARY DESTINATION /usr/lib
    	${FRMWK}
)
install ( TARGETS ${TARGET}Viewer
	RUNTIME DESTINATION /usr/bin
    ${APPBUNDLE}
)
install ( FILES debian/inscore.desktop
    	  DESTINATION /usr/share/applications
)
install ( FILES debian/icons/48x48/inscore.png
    	  DESTINATION /usr/share/icons/hicolor/48x48/apps
)
install ( FILES debian/icons/128x128/inscore.png
    	  DESTINATION /usr/share/icons/hicolor/128x128/apps
)
install ( FILES ../package/INScore-${INSAPPVERS}.tgz
    	  DESTINATION /usr/share/inscore
)


#######################################
# packaging
if(UNIX AND NOT APPLE)
  set (SYSNAME "ubuntu-maverick")
endif(UNIX AND NOT APPLE)

if (${CMAKE_SYSTEM_PROCESSOR} STREQUAL "x86_64")
  set (CPACK_DEBIAN_PACKAGE_ARCHITECTURE "amd64" )
  set(CPACK_PACKAGE_FILE_NAME "INScore-${INSAPPVERS}-${SYSNAME}-x86_64" )
else (${CMAKE_SYSTEM_PROCESSOR} STREQUAL "x86_64")
  set (CPACK_DEBIAN_PACKAGE_ARCHITECTURE "i386" )
  set(CPACK_PACKAGE_FILE_NAME "INScore-${INSAPPVERS}-${SYSNAME}-i386" )
endif (${CMAKE_SYSTEM_PROCESSOR} STREQUAL "x86_64")

set(CPACK_PACKAGE_NAME "INScore")
set(CPACK_PACKAGE_CONTACT "D. Fober <fober@grame.fr>")
set(CPACK_PACKAGE_VENDOR "Grame")
set(CPACK_PACKAGE_VERSION_MAJOR 0)
set(CPACK_PACKAGE_VERSION_MINOR 6)
set(CPACK_PACKAGE_VERSION_PATCH 3)
set(CPACK_SET_DESTDIR "ON")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "INScore - Interactive, Augmented Music Scores.") 
set(CPACK_PACKAGE_DESCRIPTION_FILE "../package/readme.txt")
set(CPACK_RESOURCE_FILE_LICENSE "../package/rsrc/license.txt")

set (CPACK_DEBIAN_PACKAGE_NAME "INScore" )
set (CPACK_DEBIAN_PACKAGE_SECTION "sound" )
set (CPACK_DEBIAN_PACKAGE_HOMEPAGE "http://inscore.sourceforge.net")
set (CPACK_DEBIAN_PACKAGE_DEPENDS "guidoengine-devel (>= 1.4.0), libc6 (>= 2.12.1), libgcc1 (>= 4.5.1), libphonon4 (>= 4.4.2), libqt4-svg (>= 4.7.0), libqtcore4 (>= 4.7.0), libqtgui4 (>= 4.7.0), libstdc++6 (>= 4.5.1)" )

set (CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA "debian/scripts/preinst;debian/scripts/postinst;debian/scripts/postrm")
include(CPack)

