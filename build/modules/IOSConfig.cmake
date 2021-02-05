#######################################
# CMAKE INScore for iOS
#######################################
cmake_minimum_required(VERSION 3.4.0)


if (NOT APPLE)
	message (FATAL "Cannot cross compile for iOS, you must call this script from MacOS")
endif()

get_filename_component(ROOT ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)
set (SRCDIR 	${ROOT}/src)
set (IOSSRCDIR  ${SRCDIR}/mobile)

file (GLOB IOS_SRC  RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} 
	"${IOSSRCDIR}/*.cpp"
	"${IOSSRCDIR}/ios/*.mm"
)

file (GLOB IOS_HEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} 
	"${IOSSRCDIR}/*.h"
	"${IOSSRCDIR}/ios/*.h"
)
set (IOS_DEFINITIONS -DINSCORE_IOS -D__MOBILE__)
set (IOS_INCLUDE_DIRS ${IOSSRCDIR})

set (CMAKE_XCODE_EFFECTIVE_PLATFORMS "iPhoneOS")
set (CMAKE_OSX_ARCHITECTURES "arm64 armv8 armv7 armv7s")
set (CMAKE_OSX_SYSROOT "iphoneos")
set (LIBTYPE STATIC)
