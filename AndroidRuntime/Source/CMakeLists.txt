cmake_minimum_required(VERSION 3.6.0)

add_library(native_app_glue STATIC ${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c) 
target_include_directories(native_app_glue PUBLIC ${ANDROID_NDK}/sources/android/native_app_glue)

find_library(log-lib log)

set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -u ANativeActivity_onCreate")

add_library(engine STATIC ${CMAKE_CURRENT_SOURCE_DIR}/../../Engine/Source/Lib.cpp)
target_include_directories(engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../Engine/Source)

add_compile_definitions(PLATFORM_ANDROID)

add_library(androidruntime SHARED androidruntime.cpp)

#add_library(engine STATIC IMPORTED)
#set_target_properties(engine PROPERTIES IMPORTED_LOCATION  ${CMAKE_CURRENT_SOURCE_DIR}/../../bin/Debug-windows-x86_64/Engine/Engine.lib)
#set_target_properties(engine PROPERTIES INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/../../Engine/Source)

target_link_libraries(androidruntime
	engine
	android
	native_app_glue
	${log-lib})
