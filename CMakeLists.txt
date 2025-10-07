cmake_minimum_required(VERSION 3.12)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED TRUE)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

project(BlockBreakC LANGUAGES C VERSION 1.2)

set(IMPL "GLFW3" CACHE STRING "The implementation to build with")
set(HSSIMPL "libc" CACHE STRING "The high score saving implementation to build with")
set(SIMPL "Dummy" CACHE STRING "The screenshot implementation to build with")
option(BUILD_SHARED_LIBS "Build the libraries as shared libraries" OFF)
option(BUILD_ONLY_IMPL "Build only the implementation library" OFF)
option(BUILD_AS_LIBRARY "Build the game as a library" OFF)
option(BUILD_FOR_I586 "Build ${PROJECT_NAME} for i586 (Intel Pentium) or higher" OFF)
option(ENABLE_SCREENSHOT "Enables taking screenshots" OFF)
option(USE_BLOCKSIZELIST "Uses the block size list instead of doing the block size calculations at runtime" OFF)
# Windows Compiler Options
option(BUILD_USING_MSVCRT20 "Build ${PROJECT_NAME} using msvcrt20 (Windows Compiler Only)" OFF)
option(BUILD_WITH_RES "Build with the resource file (Windows Compiler Only)" ON)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -MD")

include(TestBigEndian)
TEST_BIG_ENDIAN(BIG_ENDIAN)
if (BIG_ENDIAN)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DBIG_ENDIAN")
endif()

if(
	NOT IMPL STREQUAL "DJGPP"
	AND
	NOT ${CMAKE_SYSTEM_PROCESSOR} STREQUAL "mips"
)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")
endif()

if(IMPL STREQUAL "DJGPP")
 	set(CMAKE_C_COMPILER "i586-pc-msdosdjgpp-gcc")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DRENDER_WIDTH=320 -DRENDER_HEIGHT=200 -DFONT_WIDTH=8 -DFONT_HEIGHT=8 -DPLAYER_HEIGHT=7 -DPLAYER_SPEED=4 -DFILENAME83")
elseif(IMPL STREQUAL "Xlib")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DFONT_HEIGHT=10")
elseif(IMPL STREQUAL "citro2d")
	if (NINTENDO_3DS)
		set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DRENDER_WIDTH=400 -DRENDER_HEIGHT=240 -DFONT_WIDTH=8 -DFONT_HEIGHT=8 -DPLAYER_SPEED=5")
	else()
		message(FATAL_ERROR "To build the citro2d implementation you must be using the devkitPro 3DS toolchain: -DCMAKE_TOOLCHAIN_FILE=$DEVKITPRO/cmake/3DS.cmake")
	endif()
else()
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DFONT_WIDTH=8 -DFONT_HEIGHT=8")
endif()

if(ENABLE_SCREENSHOT)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DENABLE_SCREENSHOT")
endif()

if(USE_BLOCKSIZELIST)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DUSE_BLOCKSIZELIST")
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
	if(BUILD_WITH_RES)
		set(RESOURCE_FILES "src/res/resource.rc")
	endif()
	if(BUILD_USING_MSVCRT20)
		set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mcrtdll=msvcrt20")
	endif()
elseif(NOT WIN32 AND BUILD_USING_MSVCRT20)
	message(FATAL_ERROR "To build using msvcrt20 you must be using a Windows C compiler")
endif()

include_directories(
	"src"
	"src/impl"
	"src/impl/highScore"
	"src/impl/screenshot"
	"src/shared"
)

add_subdirectory(src/impl)
if(ENABLE_SCREENSHOT)
	add_subdirectory(src/impl/screenshot)
endif()

file(GLOB SHARED_SOURCE_FILES "src/shared/*.c")

add_library(Shared ${SHARED_SOURCE_FILES})

if(ENABLE_SCREENSHOT)
	target_link_libraries(Shared SImpl)
endif()

if(NOT BUILD_ONLY_IMPL)
	add_subdirectory(src/impl/highScore)
	
	file(GLOB SOURCE_FILES "src/*.c")
	
	if(BUILD_AS_LIBRARY)
		set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DBLOCKBREAKC_MAIN_NAME=blockBreakC_main")
		add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})
	else()
		add_executable(${PROJECT_NAME} ${RESOURCE_FILES} ${SOURCE_FILES})
		if(IMPL STREQUAL "DJGPP")
			set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".exe")
		elseif(IMPL STREQUAL "citro2d")
			ctr_generate_smdh(${PROJECT_NAME}.smdh
				NAME "${PROJECT_NAME}"
				DESCRIPTION "A simple game originally made in JavaScript + jQuery"
				VERSION "v${PROJECT_VERSION}pre"
				AUTHOR "StevenSYS"
				ICON "src/res/icon.png"
			)
			ctr_create_3dsx(${PROJECT_NAME} SMDH ${PROJECT_NAME}.smdh)
		endif()
	endif()
	target_link_libraries(
		${PROJECT_NAME}
		Impl
		HSSImpl
		Shared
	)
	if(ENABLE_SCREENSHOT)
		target_link_libraries(${PROJECT_NAME} SImpl)
	endif()
	set_property(TARGET ${PROJECT_NAME} PROPERTY BUILD_RPATH ".")
endif()