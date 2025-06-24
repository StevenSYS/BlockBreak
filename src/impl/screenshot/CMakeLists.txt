# SVG
if(SIMPL STREQUAL "SDL3SVG")
	find_package(SDL3 REQUIRED)
	set(SIMPL_FILES "svg/sdl3.c")
elseif(SIMPL STREQUAL "libcSVG")
	set(SIMPL_FILES "svg/libc.c")
# PPM
elseif(SIMPL STREQUAL "SDL3PPM")
	find_package(SDL3 REQUIRED)
	set(SIMPL_FILES "ppm/sdl3.c")
elseif(SIMPL STREQUAL "libcPPM")
	set(SIMPL_FILES "ppm/libc.c")
elseif(SIMPL STREQUAL "Dummy")
	set(SIMPL_FILES "dummy.c")
else()
	message(FATAL_ERROR "Invalid implementation, the possible values are \"SDL3SVG\", \"libcSVG\", \"SDL3PPM\", \"libcPPM\" or \"Dummy\"")
endif()

add_library(SImpl ${SIMPL_FILES})

if(SIMPL STREQUAL "SDL3SVG" OR SIMPL STREQUAL "SDL3PPM")
	target_link_libraries(SImpl SDL3::SDL3)
endif()