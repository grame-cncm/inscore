cmake_minimum_required(VERSION 2.6)
project(Interlude)

#######################################
# cmake build types configuration
set (CMAKE_CONFIGURATION_TYPES Debug Release)

#######################################
# versions management
set (ITLFWKVERS 0.61)
set (ITLFWKSTRVERS "v.0.61")
set (ITLFWKSSTRVERS "0.61")
set (ITLTEXTVERS 0.61)
set (ITLTEXTSTRVERS "v.0.61")
set (ITLTEXTSSTRVERS "0.61")
set (ITLAPPVERS 0.61)
set (ITLAPPSTRVERS "v.0.61")
set (ITLAPPSSTRVERS "0.61")

#######################################
if(WIN32)
	add_definitions(-DWINVER=0x0400 -DWIN32)
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
	
	set (CMAKE_OSX_ARCHITECTURES "i386")
	set (CMAKE_C++_FLAGS -mmacosx-version-min=10.4)
endif(APPLE)

#######################################
# set directories, src and headers.
set (ITL ${CMAKE_CURRENT_SOURCE_DIR}/../src)
set (ITLFOLDERS  controller events lib model view mapping interface graph signal ITLParser)
set (RSRC  "${ITL}/../rsrc")
set (LOCALLIB  "${ITL}/../lib")
set (OSC_PATH  "${LOCALLIB}/oscpack")
set (GUIDO_PATH  "${LOCALLIB}/GuidoEngine")
set (GUIDOQT_PATH  "${LOCALLIB}/GuidoQt")

if(MSVC)
	set (ITLFOLDERS  ${ITLFOLDERS} ../win32/dirent)
endif(MSVC)

foreach(folder ${ITLFOLDERS})
	set(SRC ${SRC} "${ITL}/${folder}/*.cpp")			# add source files
endforeach(folder)
set(SRC ${SRC} "${ITL}/atomic/*.cpp")
if(MSVC)
	enable_language(RC)
	set(SRC ${SRC} ../win32/Interlude.rc)
endif(MSVC)
file (GLOB CORESRC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${SRC})

foreach(folder ${ITLFOLDERS})
	set(HEADERS ${HEADERS} "${ITL}/${folder}/*.h")		# add header files
endforeach(folder)
file (GLOB COREH RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${HEADERS})

foreach(folder ${ITLFOLDERS})
	set(INCL ${INCL} "${ITL}/${folder}")				# add include folders
endforeach(folder)
set(INCL ${INCL} "${ITL}/atomic")


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
  set(QTDIR "/usr/local/Trolltech/Qt-4.6.2")
  set(QTLIBS "-L${QTDIR}/lib -lQtCore -lQtGui -lphonon" )
  set (QT_INCLUDE_DIR "${QTDIR}/include")
  set (QT_QTCORE_INCLUDE_DIR "${QT_INCLUDE_DIR}/QtCore")
  set (QT_QTGUI_INCLUDE_DIR "${QT_INCLUDE_DIR}/QtGui")
  set (QT_PHONON_INCLUDE_DIR "${QT_INCLUDE_DIR}/phonon")
endif(APPLE OR WIN32)

if(APPLE)
	set (QTLIBS "-framework QtCore -framework QtGui -framework phonon" )
	set (CORE_FOUNDATION "-framework CoreFoundation")
endif(APPLE)

if(WIN32)
	if(MINGW)
		set(QTLIBS "${QT_LIBRARY_DIR}/libQtCore4.a" "${QT_LIBRARY_DIR}/libQtGui4.a" "${QT_LIBRARY_DIR}/libQtXml4.a" "${QT_LIBRARY_DIR}/phonon4.lib" )
	else(MINGW)
		set(QTLIBS "${QT_LIBRARY_DIR}/QtCore4.lib" "${QT_LIBRARY_DIR}/QtGui4.lib" "${QT_LIBRARY_DIR}/QtXml4.lib" "${QT_LIBRARY_DIR}/phonon4.lib" )
	endif(MINGW)
endif(WIN32)

set (QTHEADERS "${QT_INCLUDE_DIR}" "${QT_QTCORE_INCLUDE_DIR}" "${QT_QTGUI_INCLUDE_DIR}" "${QT_PHONON_INCLUDE_DIR}")
file (GLOB PUBLICHEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "${ITL}/interface/*.h")

#######################################
# set libraries
if(WIN32)
	if(MINGW)
		set(OSCPACK  ${OSC_PATH}/MinGW/liboscpack.a)
		set(GUIDOQT  ${LOCALLIB}/GuidoQt/win32/libGuidoQt.a)
		set(GUIDO    ${LOCALLIB}/GuidoEngine/win32/libGUIDOEngine.dll.a)
	else(MINGW)
		set(OSCPACK  ${OSC_PATH}/oscpack.lib)
		set(GUIDOQT  ${LOCALLIB}/GuidoQt/win32/GuidoQt.lib)
		set(GUIDO    ${LOCALLIB}/GuidoEngine/win32/GUIDOEngine.lib)
		set(ITLLIBS  winmm.lib ws2_32.lib)
	endif(MINGW)
endif(WIN32)

if(APPLE)
	set(OSCPACK  ${OSC_PATH}/liboscpack.a)
	set(GUIDOQT  ${ITL}/../lib/GuidoQt/macosx/libGuidoQt.a)
	set(GUIDO    ${ITL}/../lib/GuidoEngine/macosx/GUIDOEngine.framework)
elseif(UNIX)
	set(OSCPACK  -L${OSC_PATH}/cmake -loscpack)
	set(GUIDOQT  -L${ITL}/../lib/GuidoQt/linux -lGuidoQt)
	set(GUIDO    -lGUIDOEngine)
endif(APPLE)

set(ITLLIBS  ${ITLLIBS} ${OSCPACK} ${GUIDOQT} ${GUIDO} ${QTLIBS} ${CORE_FOUNDATION} )

#######################################
# moc settings
FIND_PACKAGE(Qt4)
#message ("Qt4 output: ${QT_CONFIG}")
set (MOC_HEADERS ${ITL}/view/VSceneView.h ${ITL}/model/QFileWatcher.h)
QT_WRAP_CPP (Interlude MOC_FILES ${MOC_HEADERS})

#######################################
# set targets
include_directories(${INCL} ${OSC_PATH} ${GUIDO_PATH}/include ${GUIDOQT_PATH}/include ${QTHEADERS} )

add_library( Interlude SHARED ${CORESRC} ${COREH} ${MOC_FILES})
set_source_files_properties (${COREH} PROPERTIES HEADER_FILE_ONLY TRUE)
set_target_properties (Interlude PROPERTIES VERSION ${ITLFWKVERS}
						MACOSX_FRAMEWORK_SHORT_VERSION_STRING ${ITLFWKSTRVERS}
						MACOSX_FRAMEWORK_BUNDLE_VERSION ${ITLFWKSSTRVERS}
						PUBLIC_HEADER "${PUBLICHEADERS}")
target_link_libraries( Interlude ${ITLLIBS} )
if(MINGW)
	target_link_libraries( Interlude winmm ws2_32 )
endif(MINGW)


add_executable( InterludeTextViewer  MACOSX_BUNDLE ${ITL}/interlude.cpp )
target_link_libraries( InterludeTextViewer ${QTLIBS} ${GUIDO})
set_target_properties (InterludeTextViewer PROPERTIES COMPILE_FLAGS -DTEXTVIEW)
set_target_properties (InterludeTextViewer PROPERTIES VERSION ${ITLTEXTVERS}
							MACOSX_BUNDLE_SHORT_VERSION_STRING ${ITLTEXTSTRVERS}
							MACOSX_BUNDLE_BUNDLE_VERSION ${ITLTEXTSSTRVERS})

add_executable( InterludeSceneViewer  MACOSX_BUNDLE ${ITL}/interlude.cpp ../win32/Viewer/InterludeSceneViewer.rc)
target_link_libraries( InterludeSceneViewer ${QTLIBS} ${GUIDO})
set_target_properties (InterludeSceneViewer PROPERTIES VERSION ${ITLAPPVERS}
							MACOSX_BUNDLE_ICON_FILE ${RSRC}/ITLViewer.icns
							MACOSX_BUNDLE_SHORT_VERSION_STRING ${ITLAPPSTRVERS}
							MACOSX_BUNDLE_BUNDLE_VERSION ${ITLAPPSSTRVERS})
if(WIN32)
set_target_properties (InterludeSceneViewer PROPERTIES 
	LINK_FLAGS_RELEASE /subsystem:windows
	LINK_FLAGS_DEBUG /subsystem:console)
endif(WIN32)

if(WIN32)
set_target_properties (InterludeSceneViewer PROPERTIES 
	LINK_FLAGS_RELEASE /subsystem:windows
	LINK_FLAGS_DEBUG /subsystem:console)
endif(WIN32)

if(APPLE)
	set_target_properties (Interlude PROPERTIES FRAMEWORK TRUE FRAMEWORK_VERSION ${ITLFWKVERS})
endif(APPLE)

target_link_libraries( InterludeTextViewer Interlude)
add_dependencies(InterludeTextViewer Interlude)
target_link_libraries( InterludeSceneViewer Interlude)
add_dependencies(InterludeSceneViewer Interlude)

#######################################
# install setup
if(APPLE)
set(FRMWK  FRAMEWORK DESTINATION "/Library/Frameworks" CONFIGURATIONS Release)
endif(APPLE)

set (LIBDEST /usr/lib)
if(${CMAKE_SYSTEM_PROCESSOR} STREQUAL "x86_64")
  set (LIBDEST /usr/lib64)
  message (STATUS "64 bits system detected : setting install dir to ${LIBDEST}")
endif(${CMAKE_SYSTEM_PROCESSOR} STREQUAL "x86_64")

install ( TARGETS Interlude
	RUNTIME DESTINATION bin 
    	LIBRARY DESTINATION ${LIBDEST} 
    	ARCHIVE DESTINATION ${LIBDEST} 
    	${FRMWK}
    	PUBLIC_HEADER DESTINATION include/interlude
)


