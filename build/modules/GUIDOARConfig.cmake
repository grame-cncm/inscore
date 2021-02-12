
cmake_minimum_required(VERSION 3.6.0 FATAL_ERROR)

get_filename_component(ROOT ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)
set (GUIDOAR 	${ROOT}/modules/guidoar/src)

file (GLOB GUIDOAR_SRC  RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} 
	"${GUIDOAR}/guido/*.cpp" 
	"${GUIDOAR}/guido/abstract/*.cpp" 
	"${GUIDOAR}/interface/*.cpp" 
	"${GUIDOAR}/lib/*.cpp" 
	"${GUIDOAR}/operations/*.cpp" 
	"${GUIDOAR}/parser/*.cpp" 
	"${GUIDOAR}/visitors/*.cpp" 
)
file (GLOB GUIDOAR_HEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} 
	"${GUIDOAR}/guido/*.h" 
	"${GUIDOAR}/guido/abstract/*.h" 
	"${GUIDOAR}/interface/*.h" 
	"${GUIDOAR}/lib/*.h" 
	"${GUIDOAR}/operations/*.h" 
	"${GUIDOAR}/parser/*.h" 
	"${GUIDOAR}/visitors/*.h" 
)

#######################################
# set includes
set (GUIDOAR_INCLUDE_DIRS 
	"${GUIDOAR}/guido"
	"${GUIDOAR}/guido/abstract"
	"${GUIDOAR}/interface"
	"${GUIDOAR}/lib"
	"${GUIDOAR}/operations"
	"${GUIDOAR}/parser"
	"${GUIDOAR}/visitors"
) 
