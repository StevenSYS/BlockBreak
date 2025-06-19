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
elseif(IMPL STREQUAL "MS-DOS")
	message(WARNING "This implementation is incomplete")
	set(IMPL_FILES "msDOS.c")
elseif(IMPL STREQUAL "Dummy")
	set(IMPL_FILES "dummy.c")
else()
	message(FATAL_ERROR "Invalid implementation, the possible values are \"SDL3\", \"GLUT\", \"GLFW3\", \"SDL3GL\", \"raylib\", \"MS-DOS\" or \"Dummy\"")
endif()

add_library(Impl ${HSSIMPL_FILES} ${IMPL_FILES})

target_link_libraries(Impl Random)

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
endif()