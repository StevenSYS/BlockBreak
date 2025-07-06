if(HSSIMPL STREQUAL "libc")
	set(HSSIMPL_FILES "libc.c")
elseif(HSSIMPL STREQUAL "Dummy")
	set(HSSIMPL_FILES "dummy.c")
else()
	message(FATAL_ERROR "Invalid high score saving implementation, the possible values are \"libc\" or \"Dummy\"")
endif()

add_library(HSSImpl STATIC ${HSSIMPL_FILES})