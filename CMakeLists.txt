cmake_minimum_required(VERSION 3.12)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

project(BlockBreakC LANGUAGES C VERSION 1.3)

set(IMPL "SDL3" CACHE STRING "The implementation to build with")
set(HSSIMPL "libc" CACHE STRING "The high score saving implementation to build with")
option(BUILD_SHARED_LIBS "Build the libraries as shared libraries" OFF)
option(BUILD_FOR_I586 "Build ${PROJECT_NAME} for i586 (Intel Pentium) or higher" OFF)
# Windows Compiler Options
option(BUILD_USING_MSVCRT20 "Build ${PROJECT_NAME} using msvcrt20 (Windows Compiler Only)" OFF)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DFONT_WIDTH=8 -DFONT_HEIGHT=8")

# Impl
if(IMPL STREQUAL "SDL3")
	find_package(SDL3 REQUIRED)
	set(IMPL_FILE "sdl3.c")
elseif(IMPL STREQUAL "GLUT")
	find_package(OpenGL REQUIRED)
	find_package(GLUT REQUIRED)
	include_directories(
		${OPENGL_INCLUDE_DIRS}
		${GLUT_INCLUDE_DIR}
	)
	set(IMPL_FILE "glut.c")
elseif(IMPL STREQUAL "SDL3GL")
	find_package(SDL3 REQUIRED)
	find_package(OpenGL REQUIRED)
	include_directories(${OPENGL_INCLUDE_DIRS})
	set(IMPL_FILE "sdl3GL.c")
elseif(IMPL STREQUAL "citro2d")
	if (NINTENDO_3DS)
		set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DRENDER_WIDTH=400 -DRENDER_HEIGHT=240 -DPLAYER_SPEED=5")
	else()
		message(FATAL_ERROR "To build the citro2d implementation you must be using the devkitPro 3DS/2DS toolchain: -DCMAKE_TOOLCHAIN_FILE=$DEVKITPRO/cmake/3DS.cmake")
	endif()
	set(IMPL_FILE "citro2d.c")
else()
	message(FATAL_ERROR "Invalid implementation, the possible values are \"SDL3\", \"GLUT\", \"SDL3GL\" or \"citro2d\"")
endif()

# HSSImpl
if(HSSIMPL STREQUAL "libc")
	set(HSSIMPL_FILE "libc.c")
elseif(HSSIMPL STREQUAL "Dummy")
	set(HSSIMPL_FILE "dummy.c")
else()
	message(FATAL_ERROR "Invalid high score implementation, the possible values are \"libc\" or \"Dummy\"")
endif()

set(CMAKE_C_FLAGS_DEBUG "-g -Wall")
set(CMAKE_C_FLAGS_RELEASE "-O2")
if(
	NOT IMPL STREQUAL "citro2d" AND
	NOT CMAKE_C_COMPILER_ID MATCHES "Clang"
)
	set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -s")
endif()

if(BUILD_FOR_I586)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -march=i586 -fcf-protection=none")
endif()

if(WIN32)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wl,-subsystem,windows")
	set(RESOURCE_FILES "src/res/resource.rc")
	if(BUILD_USING_MSVCRT20)
		set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mcrtdll=msvcrt20")
	endif()
elseif(NOT WIN32 AND BUILD_USING_MSVCRT20)
	message(FATAL_ERROR "To build using msvcrt20 you must be using a Windows C compiler")
endif()

include_directories("src")

file(GLOB SOURCE_FILES "src/*.c")

add_executable(
	${PROJECT_NAME}
	"src/impl/${IMPL_FILE}"
	"src/hssImpl/${HSSIMPL_FILE}"
	${RESOURCE_FILES}
	${SOURCE_FILES}
)
if(IMPL STREQUAL "SDL3")
	target_link_libraries(${PROJECT_NAME} SDL3::SDL3)
elseif(IMPL STREQUAL "GLUT")
	target_link_libraries(
		${PROJECT_NAME}
		${OPENGL_LIBRARY}
	)
	
	if (BUILD_USING_MSVCRT20)
		target_link_libraries(${PROJECT_NAME} libglut.a)
	else()
		target_link_libraries(${PROJECT_NAME} ${GLUT_glut_LIBRARY})
	endif()
	
	if (APPLE)
		target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
	endif()
elseif(IMPL STREQUAL "SDL3GL")
	target_link_libraries(
		${PROJECT_NAME}
		SDL3::SDL3
		${OPENGL_LIBRARY}
	)
	
	if (APPLE)
		target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
	endif()
elseif(IMPL STREQUAL "citro2d")
	ctr_generate_smdh(${PROJECT_NAME}.smdh
		NAME "${PROJECT_NAME}"
		DESCRIPTION "A simple game originally made in JavaScript + jQuery"
		VERSION "v${PROJECT_VERSION}pre"
		AUTHOR "StevenSYS"
		ICON "src/res/icon.png"
	)
	ctr_create_3dsx(${PROJECT_NAME} SMDH ${PROJECT_NAME}.smdh)
	target_link_libraries(
		${PROJECT_NAME}
		citro2d
		citro3d
		ctru
	)
endif()
set_property(TARGET ${PROJECT_NAME} PROPERTY BUILD_RPATH ".")