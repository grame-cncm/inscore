cmake_minimum_required (VERSION 2.6)
project (inscorehttpd)
set (target inscorehttpd)

set (ROOT  ${CMAKE_CURRENT_SOURCE_DIR}/..)

FILE(GLOB SERVER_CPP_SOURCES ${ROOT}/*.cpp)

include_directories(${ROOT}/ ${ROOT}/../../src/plugins/httpserver "/usr/local/include")

# microhttpd
EXECUTE_PROCESS ( COMMAND "pkg-config" "--libs" "libmicrohttpd"
        OUTPUT_VARIABLE TMP
        ERROR_VARIABLE TMP
)
string(STRIP ${TMP} microhttpd_LIBRARIES)
set(LINK ${LINK} ${microhttpd_LIBRARIES})

add_library(${target} SHARED ${SERVER_CPP_SOURCES} ${SERVER_C_SOURCES})
target_link_libraries(${target} ${LINK})
