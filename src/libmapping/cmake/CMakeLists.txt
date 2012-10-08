cmake_minimum_required(VERSION 2.6)
project(libmapping)

#######################################
# cmake build types configuration
set (CMAKE_CONFIGURATION_TYPES Debug Release)

set (TARGET	mapping)

#######################################
# versions management
set (libMappingFWKVERS 0.98)
set (libMappingFWKSTRVERS "v.0.98")
set (SOVERS 1)

#######################################
if(WIN32)
if(MSVC)
	add_definitions(-DMSVC -D_USE_MATH_DEFINES)
endif(MSVC)
else(WIN32)
	add_definitions(-Wall)
endif(WIN32)

message ("CMAKE_SYSTEM_VERSION ${CMAKE_SYSTEM_VERSION}")

if(APPLE)
	if (${CMAKE_SYSTEM_VERSION} VERSION_LESS 9.0.0)
		set (CMAKE_OSX_SYSROOT /Developer/SDKs/MacOSX10.4u.sdk)
	elseif (${CMAKE_SYSTEM_VERSION} VERSION_LESS 10.8.0)
		set (CMAKE_OSX_SYSROOT /Developer/SDKs/MacOSX10.5.sdk)
	elseif (${CMAKE_SYSTEM_VERSION} VERSION_LESS 11.4.0)
		set (CMAKE_OSX_SYSROOT /Developer/SDKs/MacOSX10.6.sdk)
	else ()
		set (CMAKE_OSX_SYSROOT "macosx10.7")
	endif ()
 #######################################
 if (DIST STREQUAL "yes")
	message (STATUS "All architectures will be compiled - Use -DDIST=no to change.")
	set (CMAKE_OSX_ARCHITECTURES "x86_64 i386")
 else ()
	message (STATUS "Only the current architecture will be compiled - Use -DDIST=yes to change.")
 endif ()
	set (CMAKE_C++_FLAGS -mmacosx-version-min=10.5)
endif(APPLE)

#######################################
# set directories, src and headers.
set (ROOT ${CMAKE_CURRENT_SOURCE_DIR}/../src)
set (FOLDERS  misc parser relations segments)

#######################################
#
foreach(folder ${FOLDERS})
	set(SRC ${SRC} "${ROOT}/${folder}/*.cpp")			# add source files
endforeach(folder)
file (GLOB CORESRC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${SRC})

foreach(folder ${FOLDERS})
	set(HEADERS ${HEADERS} "${ROOT}/${folder}/*.h")		# add header files
endforeach(folder)
file (GLOB COREH RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${HEADERS})

foreach(folder ${FOLDERS})
	set(INCL ${INCL} "${ROOT}/${folder}")				# add include folders
endforeach(folder)
set(INCL ${INCL} "${ROOT}/atomic")


#######################################
# qt setup

if(APPLE)
	set (CORE_FOUNDATION "-framework CoreFoundation")
endif(APPLE)

file (GLOB PUBLICHEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${INCL})

#######################################
# set libraries
#set(INSLIBS  ${INSLIBS} ${CORE_FOUNDATION} )

#######################################
# set targets
include_directories(${INCL})

add_library( ${TARGET} STATIC ${CORESRC} ${COREH})
set_source_files_properties (${COREH} PROPERTIES HEADER_FILE_ONLY TRUE)
set_target_properties (${TARGET} PROPERTIES 
			VERSION ${libMappingFWKVERS}
			SOVERSION ${SOVERS}
			MACOSX_FRAMEWORK_SHORT_VERSION_STRING ${libMappingFWKSTRVERS}
			MACOSX_FRAMEWORK_BUNDLE_VERSION ${libMappingFWKVERS}
			PUBLIC_HEADER "${PUBLICHEADERS}"
)
#target_link_libraries( ${TARGET} ${INSLIBS} )
