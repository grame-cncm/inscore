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
add_definitions(-DNO_OSCSTREAM -DPARSERTEST)

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
set (INSFOLDERS  controller events lib model mapping view interface scripting atomic libmapping/src/misc libmapping/src/segments libmapping/src/relations)

# add source files
set(SRC "${ROOT}/*.cpp" "${ROOT}/parser/*.cpp" "${INSCORE}/scripting/TScripting.cpp" "${INSCORE}/lib/Tools.cpp")
set(SRC "${SRC}" "${INSCORE}/libmapping/src/misc/rational.cpp" "${INSCORE}/controller/IMessage.cpp")

file (GLOB CORESRC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${SRC})

set(INCL "${ROOT}/parser")							# add include folders
foreach(folder ${INSFOLDERS})
	set(INCL ${INCL} "${INSCORE}/${folder}")		# add include folders
endforeach(folder)

#######################################
# set targets
include_directories(${INCL} ${OSC_PATH})
add_executable( ${APPLTARGET} ${CORESRC} )


#######################################
# install setup
install ( TARGETS ${APPLTARGET}
    	RUNTIME DESTINATION /usr/local/bin
)
