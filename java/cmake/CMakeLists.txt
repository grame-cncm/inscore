#######################################
# CMAKE guidolib
#######################################
project(INScoreJNI)
cmake_minimum_required(VERSION 2.6)

set (target jniINScore)
#######################################
# versions management
set (VERSION 1.00)
set (STRVERS "v.1.00")
set (SSTRVERS "1.00")

#######################################
# java setup
FIND_PACKAGE(JNI REQUIRED)
#FIND_PACKAGE(Java REQUIRED)
#message ( "JNI_INCLUDE_DIRS		 ${JNI_Iset_target_properties (${target} PROPERTIES
#message ( "JAVA_AWT_LIBRARY		 ${JAVA_AWT_LIBRARY}")
#message ( "JAVA_JVM_LIBRARY		 ${JAVA_JVM_LIBRARY}")
#message ( "JAVA_INCLUDE_PATH	 ${JAVA_INCLUDE_PATH}")
#message ( "JAVA_INCLUDE_PATH2	 ${JAVA_INCLUDE_PATH2}")
#message ( "JAVA_AWT_INCLUDE_PATH ${JAVA_AWT_INCLUDE_PATH}")

#######################################
# qt setup

if(APPLE OR WIN32)
  set(DESIRED_QT_VERSION 4.7)
  FIND_PACKAGE(QT REQUIRED)
else(APPLE OR WIN32)
  set(DESIRED_QT_VERSION 4.7)
  FIND_PACKAGE(Qt4 REQUIRED)
  set (QTLIBS "-lQtCore -lQtGui" )
endif(APPLE OR WIN32)

if(APPLE)
	set (QTLIBS "-framework QtCore -framework QtGui" )
	set (CORE_FOUNDATION "-framework CoreFoundation")
endif(APPLE)

if(WIN32)
	if(MINGW)
		set(QTLIBS "${QT_LIBRARY_DIR}/libQtCore4.a" "${QT_LIBRARY_DIR}/libQtGui4.a")
	else(MINGW)
		set(QTLIBS "${QT_LIBRARY_DIR}/QtCore4.lib" "${QT_LIBRARY_DIR}/QtGui4.lib")
	endif(MINGW)
endif(WIN32)

set (QTHEADERS "${QT_INCLUDE_DIR}" "${QT_QTCORE_INCLUDE_DIR}" "${QT_QTGUI_INCLUDE_DIR}")

#######################################
if(APPLE)
	set (CMAKE_OSX_ARCHITECTURES "x86_64 i386")
	set (CMAKE_OSX_SYSROOT /Developer/SDKs/MacOSX10.5.sdk)
	set (CMAKE_C++_FLAGS -mmacosx-version-min=10.4)
endif(APPLE)


if(WIN32)
 add_definitions(-DWINVER=0x0400 -DWIN32)
 if(${CMAKE_GENERATOR} STREQUAL "Visual Studio 6")
  add_definitions(-DVC6)
 elseif(${CMAKE_GENERATOR} STREQUAL "Visual Studio 8 2005")
  add_definitions(-DVC2005)
 elseif(${CMAKE_GENERATOR} STREQUAL "Visual Studio 9 2008")
  add_definitions(-DVC2005)
 endif(${CMAKE_GENERATOR} STREQUAL "Visual Studio 6")
endif(WIN32)

#######################################
# set directories, src and headers.
set (JAVA_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../INScore)
set (JNI_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../jni)
set (SRC_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../src)

set (SRC "${JNI_PATH}/*.cpp")				# add source files
set (HEADERS "${JNI_PATH}/*.h")				# add header files
set (INCL ${JNI_INCLUDE_DIRS} ${SRC_PATH}/interface)

#######################################
# set includes
include_directories( ${INCL} ${QTHEADERS})

#######################################
# set library target
file (GLOB JAVA RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "${JAVA_PATH}/*.java")
file (GLOB LIBSRC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${SRC})
file (GLOB LIBH RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${HEADERS})
set (INScore_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../cmake)
find_library (INScore INScore PATHS ${INScore_PATH}/Release NO_DEFAULT_PATH)

set (LIBCONTENT ${LIBSRC} ${LIBH})
set (LINK  ${INScore})

#if(WIN32)
#	enable_language(RC)
#	set(LIBCONTENT ${LIBCONTENT} ../jni/win32/jniGUIDOEngine.rc)
#	set(LINK ${LINK} "../../cmake/release/GUIDOEngine" Gdiplus)
#endif(WIN32)

#if(APPLE)
#	set(LINK ${LINK}  "-framework Cocoa  -framework CoreFoundation")
#elseif(WIN32)
#	set(LINK ${LINK} "../../cmake/release/GUIDOEngine")
#endif(APPLE)

add_library(${target} SHARED ${LIBCONTENT})
set_target_properties (${target} PROPERTIES VERSION ${VERSION})
target_link_libraries (${target} ${LINK})


#######################################
# install settings
if(!WIN32)
set (LIBDEST /usr/lib)
if(${CMAKE_SYSTEM_PROCESSOR} STREQUAL "x86_64")
  set (LIBDEST /usr/lib64)
  message (STATUS "64 bits system detected : setting install dir to ${LIBDEST}")
endif(${CMAKE_SYSTEM_PROCESSOR} STREQUAL "x86_64")

install ( TARGETS ${target}	LIBRARY DESTINATION ${LIBDEST})
endif(!WIN32)
