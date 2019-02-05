function(unit_test)
    set(singleValueArgs TARGET)
    set(multiValueArgs SOURCES;LIBRARIES)

    cmake_parse_arguments(
            unit_test					# prefix of variables
            "${flagValueArgs}"	    	# list of boolean flags
            "${singleValueArgs}"        # single value variables
            "${multiValueArgs}"	    	# multi value variables
            ${ARGN}
    )

    add_executable(
            ${unit_test_TARGET}
            ${unit_test_SOURCES}
    )

    target_link_libraries(
            ${unit_test_TARGET}
            ${unit_test_LIBRARIES}
            ${GTEST_BOTH_LIBRARIES}
            ${CMAKE_THREAD_LIBS_INIT}
            ${Boost_LIBRARIES}
    )

    add_test(
            NAME "${unit_test_TARGET}"
            COMMAND "${unit_test_TARGET}"
    )
endfunction()
