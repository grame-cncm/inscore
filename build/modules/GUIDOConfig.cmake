
cmake_minimum_required(VERSION 3.8.0 FATAL_ERROR)

get_filename_component(ROOT ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)
set (GUIDOLIB 	${ROOT}/modules/guidolib)

#######################################
# set includes
set (GUIDO_INCLUDE_DIRS  ${GUIDOLIB}/src/engine/include)

#######################################
# set library
if (IOS)
	set (GUIDO_LIBRARIES ${GUIDOLIB}/build/lib/libGUIDOEngine.a)
elseif(UNIX)
	set (GUIDO_LIBRARIES -L${CMAKE_CURRENT_SOURCE_DIR}/lib -lGUIDOEngine)
elseif(WIN32)
	if ("${CMAKE_GENERATOR}" MATCHES "(Win64|IA64)")
		set (GUIDO_LIBRARIES ${GUIDOLIB}/build/lib/GUIDOEngine64.lib)
		set (GUIDO_DLL ${GUIDOLIB}/build/lib/GUIDOEngine64.dll)
	else()
		set (GUIDO_LIBRARIES ${GUIDOLIB}/build/lib/GUIDOEngine.lib)
		set (GUIDO_DLL ${GUIDOLIB}/build/lib/GUIDOEngine.dll)
	endif()		
endif()

file (STRINGS "${GUIDOLIB}/version.txt" GUIDO_VERSION)
message (STATUS "Using GUIDOEngine version ${GUIDO_VERSION}")

