cmake_minimum_required(VERSION 3.4.0)
project (inscore)

macro (get_major_minor_patch version)
	string( REGEX REPLACE "([0-9]*)\\.([0-9])([0-9])" "\\1"  VERSION_MAJOR ${version} )
	string( REGEX REPLACE "([0-9]*)\\.([0-9])([0-9])" "\\2"  VERSION_MINOR ${version} )
	string( REGEX REPLACE "([0-9]*)\\.([0-9])([0-9])" "\\3"  VERSION_PATCH ${version} )
endmacro()

get_filename_component(ROOT ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)
set (BINDIR ${ROOT}/build/bin)
set (INSDOC ${ROOT}/package/doc)

#######################################
# versions management
file (READ ${ROOT}/version.txt VERSION)
get_major_minor_patch( ${VERSION} )
message (STATUS "Configuring version ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")


####################################
# application files
file (GLOB APP ${BINDIR}/*)


####################################
# install section
####################################
if (WIN32)
	set (CMAKE_INSTALL_PREFIX .)
	set (DEST .)
	set (DOCDEST  ${DEST})
	set (FONTDEST ${DEST})
elseif(APPLE)
	set (CMAKE_INSTALL_PREFIX .)
	set (DEST INScore-${VERSION})
	set (DOCDEST  ${DEST})
	set (FONTDEST ${DEST})
else()
	set (DEST ${DESTDIR}${CMAKE_INSTALL_PREFIX})
	set (DOCDEST  ${DEST}/share/inscore)
	set (FONTDEST ${DEST}/share/fonts/guido)
endif()
message (STATUS "Install to ${DEST}")

####################################
# install applications
####################################
if(APPLE)
install (
    DIRECTORY ${BINDIR}/INScoreViewer.app DESTINATION ${DEST}
	FILE_PERMISSIONS USE_SOURCE_PERMISSIONS
    DIRECTORY_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
    	GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
    PATTERN ".DS_Store" EXCLUDE
)

#install (
#    FILES     ${BINDIR}/IBundle DESTINATION ${DEST}
#    PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
#)

elseif (WIN32)
install (
    DIRECTORY ${BINDIR} DESTINATION ${DEST}
    FILE_PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ
    DIRECTORY_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
    	GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
    PATTERN ".DS_Store" EXCLUDE
)
else ()
file (GLOB INSCORELIB RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "${BINDIR}/libINScore*")
install (
    FILE ${BINDIR}/inscoreviewer DESTINATION ${DEST}/bin
    FILE_PERMISSIONS USE_SOURCE_PERMISSIONS
)
install (
    FILE ${INSCORELIB} DESTINATION ${DEST}/lib
    FILE_PERMISSIONS USE_SOURCE_PERMISSIONS
)
endif()

####################################
# install documentation
install (
    DIRECTORY ${INSDOC} DESTINATION ${DOCDEST}
    FILE_PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ
    DIRECTORY_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
    PATTERN ".DS_Store" EXCLUDE
)

####################################
# install interfaces
install (
    DIRECTORY ${ROOT}/interfaces DESTINATION ${DOCDEST}
    FILE_PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ
    DIRECTORY_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
    PATTERN ".DS_Store" EXCLUDE
)

####################################
# install sample files
set (SAMPLES ${DOCDEST}/examples)
set (SSRC    ${ROOT}/scripts)
install (
    DIRECTORY 	${SSRC}/M-signalConnection
				${SSRC}/M-sync-scores
				${SSRC}/Max-tools
				${SSRC}/MP-Turenas
				${SSRC}/MP-cursors
				${SSRC}/MP-first-demo
				${SSRC}/MP-graphsig-sinus
				${SSRC}/MP-graphsig-var
				${SSRC}/MP-interaction
				${SSRC}/MP-sync-cars
				${SSRC}/MP-sync-train
				${SSRC}/PureData-tools
				${SSRC}/Perception
				${SSRC}/Standalone
    DESTINATION ${SAMPLES}
    FILE_PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ
    DIRECTORY_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
    PATTERN ".DS_Store" EXCLUDE
)
install (
    FILES     ${SSRC}/readme.txt DESTINATION ${SAMPLES}
    PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ
)


####################################
# install misc files
install (
    FILES     ${ROOT}/src/changelog.txt ${ROOT}/package/ReadMe.html DESTINATION ${DOCDEST}
    PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ
)

####################################
# installguido font
install (
    FILES     ${ROOT}/src/guido2.ttf DESTINATION ${FONTDEST}
    PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ
)

####################################
# install VS redistributables
if (WIN32)
set (VS "C:/Program Files (x86)/Microsoft Visual Studio 14.0/VC/redist/x64/Microsoft.VC140.CRT")
install (
    FILES  "${VS}/msvcp140.dll" "${VS}/vcruntime140.dll" DESTINATION ${DEST}/FaustLive
    PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ
)
endif()


####################################
# cpack section
####################################
set (CPACKDEST INScore-${VERSION})
set (CPACK_PACKAGE_NAME   "INScore")
set (CPACK_PACKAGE_VENDOR "GRAME")
set (CPACK_PACKAGE_DESCRIPTION_SUMMARY "INScore - an environment for the design of interactive augmented music scores.")
set (CPACK_PACKAGE_VERSION   ${VERSION})
set (CPACK_PACKAGE_VERSION_MAJOR   ${VERSION_MAJOR})
set (CPACK_PACKAGE_VERSION_MINOR   ${VERSION_MINOR})
set (CPACK_PACKAGE_VERSION_PATCH   ${VERSION_PATCH})

set (CPACK_MONOLITHIC_INSTALL true)
set (CPACK_RESOURCE_FILE_LICENSE  ${ROOT}/package/rsrc/license.txt)
set (CPACK_PACKAGE_INSTALL_DIRECTORY  ${CPACKDEST})

####################################
# NSIS specific section
set (CPACK_NSIS_INSTALL_ROOT "C:\\\\Program Files")
set (CPACK_NSIS_MODIFY_PATH on)
set (CPACK_NSIS_MUI_ICON "${ROOT}/rsrc/ITLViewer.ico")

include (CPack)
