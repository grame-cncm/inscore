cmake_minimum_required (VERSION 2.6)
project (inscorehttpd)
set (target inscorehttpd)

set (ROOT  ${CMAKE_CURRENT_SOURCE_DIR}/..)

FILE(GLOB SERVER_CPP_SOURCES ${ROOT}/*.cpp ${ROOT}/../../src/json/*.cpp)

include_directories(${ROOT}/ ${ROOT}/../../src/library/plugins/httpserver ${ROOT}/../../src/json ${ROOT}/../../src/inscore/web "/usr/local/include")

add_definitions(-DJSON_ONLY)

# microhttpd
EXECUTE_PROCESS ( COMMAND "pkg-config" "--libs" "libmicrohttpd"
        OUTPUT_VARIABLE TMP
        ERROR_VARIABLE TMP
)
string(STRIP ${TMP} microhttpd_LIBRARIES)
set(LINK ${LINK} ${microhttpd_LIBRARIES})

add_library(${target} SHARED ${SERVER_CPP_SOURCES} ${SERVER_C_SOURCES})

set(TARGET_VERSION_MAJOR 1)
set(TARGET_VERSION_MINOR 1)
set(TARGET_VERSION_PATCH 0)
set(TARGET_VERSION_STRING ${TARGET_VERSION_MAJOR}.${TARGET_VERSION_MINOR}.${TARGET_VERSION_PATCH})

add_definitions( -DVERSION="${TARGET_VERSION_STRING}" )

set_target_properties(${target} PROPERTIES VERSION ${TARGET_VERSION_STRING}
    SOVERSION ${TARGET_VERSION_STRING})

target_link_libraries(${target} ${LINK})
