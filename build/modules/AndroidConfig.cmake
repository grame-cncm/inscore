
cmake_minimum_required(VERSION 3.6.0 FATAL_ERROR)

get_filename_component(ROOT ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)


set (NDK ENV{HOME}/src/android/android-ndk)

set (CMAKE_PROGRAM_PATH  /Users/Shared/Qt/5.15.2/5.15.2/android/bin)
set (QT_ANDROID_ROOT /Users/Shared/Qt/5.15.2/5.15.2/android)

set (CMAKE_TOOLCHAIN_FILE ${NDK}/build/cmake/android.toolchain.cmake)
set (CMAKE_SYSTEM_NAME "Android")
set (ANDROID_NDK ${NDK} )
set (ANDROID_TOOLCHAIN clang) 
set (ANDROID_NATIVE_API_LEVEL 26)
set (ANDROID_PLATFORM android-26)
# -T "ClangDefault" –

message (STATUS "Using Android NDK")

