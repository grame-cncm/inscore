
cmake_minimum_required(VERSION 3.8.0 FATAL_ERROR)

get_filename_component(ROOT ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)
set (GUIDOAR 	${ROOT}/modules/guidoar/src)
set (OSC 		${ROOT}/lib/oscpack)

if (WIN32)
 	set (OSCIP ${OSC}/ip/win32)
else()
 	set (OSCIP ${OSC}/ip/posix)
endif()


file (GLOB OSC_SRC  RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} 
	"${OSC}/osc/*.cpp"
	"${OSC}/ip/*.cpp"
	"${OSCIP}/*.cpp"
)

file (GLOB OSC_HEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} 
	"${OSC}/osc/*.h"
	"${OSC}/ip/*.h"
	"${OSCIP}/*.h"
)

#######################################
# set includes
set (OSC_INCLUDE_DIRS 
	"${OSC}"
) 

message (STATUS "Includes OSCPack")
