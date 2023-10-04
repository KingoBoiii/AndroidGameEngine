cmake_minimum_required(VERSION 3.6.0)

add_library(native_app_glue STATIC ${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c)
target_include_directories(native_app_glue PUBLIC ${ANDROID_NDK}/sources/android/native_app_glue)

find_library(log-lib log)

set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -u ANativeActivity_onCreate")

set(EXTERNAL_LIBRARY_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../Engine/Source/obj/local/${ANDROID_ABI}/libengine.so)

add_library(engine SHARED IMPORTED)
set_target_properties(engine PROPERTIES IMPORTED_LOCATION ${EXTERNAL_LIBRARY_PATH})
target_include_directories(engine INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/../../Engine/Source)

add_library(androidruntime SHARED androidruntime.cpp)

target_link_libraries(androidruntime
	engine
	native_app_glue
	android
	${log-lib}
	EGL
	GLESv3)
