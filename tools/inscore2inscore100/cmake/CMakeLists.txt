cmake_minimum_required(VERSION 2.6)
project(inscore2inscore100)

#######################################
# cmake build types configuration
set (CMAKE_CONFIGURATION_TYPES Debug Release)

set (APPLTARGET	inscore2inscore100)

#######################################
if(WIN32)
if(MSVC)
	add_definitions(-D_USE_MATH_DEFINES)
endif(MSVC)
else(WIN32)
	add_definitions(-Wall)
endif(WIN32)
add_definitions(-DNO_OSCSTREAM)

if(APPLE)
	if (${CMAKE_SYSTEM_VERSION} VERSION_LESS 9.0.0)
		set (CMAKE_OSX_SYSROOT /Developer/SDKs/MacOSX10.4u.sdk)
	elseif (${CMAKE_SYSTEM_VERSION} VERSION_LESS 10.8.0)
		set (CMAKE_OSX_SYSROOT /Developer/SDKs/MacOSX10.5.sdk)
	elseif (${XCODE_VERSION} VERSION_LESS 4.0.0)
		set (CMAKE_OSX_SYSROOT /Developer/SDKs/MacOSX10.6.sdk)
	else ()
		set (CMAKE_OSX_SYSROOT "macosx10.7")
	endif ()

	set (CMAKE_OSX_ARCHITECTURES "i386 x86_64")
	set (CMAKE_C++_FLAGS -mmacosx-version-min=10.4)
endif(APPLE)

#######################################
# set directories, src and headers.
set (ROOT ${CMAKE_CURRENT_SOURCE_DIR}/..)
set (OSC_PATH  "${ROOT}/../../lib/oscpack")
set (LOCALLIB  "${ROOT}/../../lib/")
set (INSCORE ${ROOT}/../../src)
set (INSFOLDERS  controller lib model mapping view interface scripting libmapping/package/libmapping)

set(SRC "${ROOT}/*.cpp" "${ROOT}/parser/*.cpp" "${INSCORE}/scripting/TScripting.cpp")		# add source files
set(SRC "${SRC}" "${INSCORE}/libmapping/src/misc/rational.cpp" "${INSCORE}/controller/IMessage.cpp")

file (GLOB CORESRC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${SRC})

set(INCL "${ROOT}/parser")							# add include folders
foreach(folder ${INSFOLDERS})
	set(INCL ${INCL} "${INSCORE}/${folder}")		# add include folders
endforeach(folder)

#######################################
# lua support
#add_definitions(-DLUA)
#if (WIN32)
#	set(SCRIPTS ${SCRIPTS} ${LOCALLIB}/lua/win32/lua.lib)
#	set(SCRIPTINCL ${SCRIPTINCL} ${LOCALLIB}/lua/win32/)
#elif(APPLE)
#	set(SCRIPTS ${SCRIPTS} -llua)
#	set(SCRIPTINCL ${SCRIPTINCL} /usr/local/include)
#else ()
#	EXECUTE_PROCESS ( COMMAND "pkg-config" "--cflags" "lua"
#		OUTPUT_VARIABLE TMP
#		ERROR_VARIABLE TMP
#	)
#	string(STRIP ${TMP} LUACFG)
#	add_definitions(${LUACFG})
#	EXECUTE_PROCESS ( COMMAND "pkg-config" "--libs" "lua"
#		OUTPUT_VARIABLE TMP
#		ERROR_VARIABLE TMP
#	)
#	string(STRIP ${TMP} LUACFG)
#	set(SCRIPTS ${SCRIPTS} ${LUACFG})
#endif()
#
#######################################
# javascript support
#add_definitions(-DV8ENGINE)
#if (WIN32)
#	set(SCRIPTS ${SCRIPTS} "${LOCALLIB}/javascript/v8/win32/v8.lib")
#	set(SCRIPTINCL ${SCRIPTINCL} ${LOCALLIB}/javascript/v8/include)
#else()
#	set(SCRIPTINCL ${SCRIPTINCL} ${LOCALLIB}/javascript/v8/include)
#	if(APPLE)
#		set(SCRIPTS ${SCRIPTS} -L${LOCALLIB}/javascript/v8/MacOS -lv8)
#	else()
#		set(SCRIPTS ${SCRIPTS} -L${LOCALLIB}/javascript/v8/linux -lv8)
#	endif()
#endif ()
#
#######################################
# set targets
include_directories(${INCL} ${OSC_PATH})
add_executable( ${APPLTARGET} ${CORESRC} )


#######################################
# install setup
install ( TARGETS ${APPLTARGET}
    	RUNTIME DESTINATION /usr/local/bin
)
