if(IMPL STREQUAL "SDL3")
	find_package(SDL3 REQUIRED)
	set(IMPL_FILES "sdl3.c")
elseif(IMPL STREQUAL "GLUT")
	find_package(OpenGL REQUIRED)
	find_package(GLUT REQUIRED)
	include_directories(
		${OPENGL_INCLUDE_DIRS}
		${GLUT_INCLUDE_DIR}
	)
	set(IMPL_FILES "glut.c")
elseif(IMPL STREQUAL "GLFW3")
	find_package(OpenGL REQUIRED)
	find_package(glfw3 REQUIRED)
	include_directories(${OPENGL_INCLUDE_DIRS})
	set(IMPL_FILES "glfw3.c")
elseif(IMPL STREQUAL "SDL3GL")
	find_package(SDL3 REQUIRED)
	find_package(OpenGL REQUIRED)
	include_directories(
		${SDL3_INCLUDE_DIRS}
		${OPENGL_INCLUDE_DIRS}
	)
	set(IMPL_FILES "sdl3GL.c")
elseif(IMPL STREQUAL "raylib")
	find_package(raylib 3.0 REQUIRED)
	include_directories(${raylib_INCLUDE_DIRS})
	set(IMPL_FILES "raylib.c")
elseif(IMPL STREQUAL "DJGPP")
	message(WARNING "This implementation is quite inefficient")
	set(BUILD_SHARED_LIBS OFF)
	set(BUILD_AS_LIBRARY OFF)
	set(BUILD_FOR_I586 OFF)
	set(IMPL_FILES "djgpp.c")
elseif(IMPL STREQUAL "Xlib")
	find_package(X11 REQUIRED)
	include_directories(${X11_INCLUDE_DIR})
	set(IMPL_FILES "xlib.c")
elseif(IMPL STREQUAL "citro2d")
	set(IMPL_FILES "citro2d.c")
elseif(IMPL STREQUAL "Dummy")
	set(IMPL_FILES "dummy.c")
else()
	message(FATAL_ERROR "Invalid implementation, the possible values are \"SDL3\", \"GLUT\", \"GLFW3\", \"SDL3GL\", \"raylib\", \"DJGPP\", \"Xlib\", \"citro2d\" or \"Dummy\"")
endif()

add_library(Impl ${IMPL_FILES})

target_link_libraries(Impl Random)

if(ENABLE_SCREENSHOT)
	target_link_libraries(Impl SImpl)
endif()

if(IMPL STREQUAL "SDL3")
	target_link_libraries(Impl SDL3::SDL3)
elseif(IMPL STREQUAL "GLUT")
	target_link_libraries(
		Impl
		${OPENGL_LIBRARY}
	)
	if (BUILD_USING_MSVCRT20)
		target_link_libraries(Impl libglut.a)
	else()
		target_link_libraries(Impl ${GLUT_glut_LIBRARY})
	endif()
	if (APPLE)
		target_link_libraries(Impl "-framework OpenGL")
	endif()
elseif(IMPL STREQUAL "GLFW3")
	target_link_libraries(
		Impl
		${OPENGL_LIBRARY}
		glfw
	)
	if (APPLE)
		target_link_libraries(Impl "-framework OpenGL")
	endif()
elseif(IMPL STREQUAL "SDL3GL")
	target_link_libraries(
		Impl
		SDL3::SDL3
		${OPENGL_LIBRARY}
	)
	if (APPLE)
		target_link_libraries(Impl "-framework OpenGL")
	endif()
elseif(IMPL STREQUAL "raylib")
	target_link_libraries(Impl raylib)
	if (APPLE)
		target_link_libraries(Impl "-framework IOKit")
		target_link_libraries(Impl "-framework Cocoa")
		target_link_libraries(Impl "-framework OpenGL")
	endif()
elseif(IMPL STREQUAL "Xlib")
	target_link_libraries(Impl ${X11_LIBRARIES})
elseif(IMPL STREQUAL "citro2d")
	target_link_libraries(Impl citro2d citro3d ctru)
endif()