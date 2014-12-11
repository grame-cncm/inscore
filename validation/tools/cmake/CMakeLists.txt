cmake_minimum_required(VERSION 2.6)
project(inscore-tools)

#######################################
# cmake build types configuration
set (CMAKE_CONFIGURATION_TYPES Debug Release)

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
	set (CMAKE_OSX_DEPLOYMENT_TARGET 10.6)
	set (MACOSX_DEPLOYMENT_TARGET 10.6)
	set (CMAKE_C++_FLAGS -mmacosx-version-min=10.6)
endif(APPLE)

#######################################
# set directories, src and headers.
set (ROOT ${CMAKE_CURRENT_SOURCE_DIR}/..)
set (OSC_PATH  "${ROOT}/../../lib/oscpack")
set (INSC_PATH "${ROOT}/../../src")

# add source files
set(SRC "${ROOT}/*.cpp" "${ROOT}/parser/*.cpp" "${INSCORE}/scripting/TScripting.cpp" "${INSCORE}/lib/Tools.cpp")
set(SRC "${SRC}" "${INSCORE}/libmapping/src/misc/rational.cpp" "${INSCORE}/controller/IMessage.cpp")

file (GLOB CORESRC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${SRC})

if(WIN32)
	set(OSCPACK  ${OSC_PATH}/cmake/release/oscpack.lib)
 	find_library (INSCORE INScore PATHS ${ROOT}/../../build/win32/Release NO_DEFAULT_PATH)
	set(INSLIBS  winmm.lib ws2_32.lib)
elseif(APPLE)
	set(OSCPACK  ${OSC_PATH}/build/MacOS/Release/liboscpack.a)
 	find_library (INSCORE INScore PATHS ${ROOT}/../../build/MacOS/Release NO_DEFAULT_PATH)
elseif(UNIX)
	set(OSCPACK  -L${OSC_PATH}/cmake -loscpack)
 	find_library (INSCORE INScore PATHS ${ROOT}/../../cmake NO_DEFAULT_PATH)
endif()



#######################################
# set targets
add_executable( forcepdfdate ${ROOT}/forcepdfdate.cpp )

file (GLOB VSRC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${ROOT}/INScoreVersion.cpp)
include_directories(${INSC_PATH}/interface ${OSC_PATH})
add_executable( INScoreVersion ${ROOT}/INScoreVersion.cpp )
target_link_libraries( INScoreVersion ${INSCORE} ${INSLIBS})

include_directories(${OSC_PATH})
add_executable( SendOSC ${ROOT}/SendOSC.cpp )
target_link_libraries( SendOSC ${OSCPACK} ${INSLIBS})

