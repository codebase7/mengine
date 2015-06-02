add_subdirectory(Core)
add_subdirectory(Common)

if (BUILD_UNIT_TESTS)
	add_subdirectory(Tests)
endif (BUILD_UNIT_TESTS)