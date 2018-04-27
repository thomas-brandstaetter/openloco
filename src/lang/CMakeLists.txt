
include_directories(${CMAKE_CURRENT_BINARY_DIR})

if (Win32)
    include_directories(${CMAKE_SOURCE_DIR}\\header\\lang)
endif ()

set(ADDITIONAL_SOURCES
        ${CMAKE_CURRENT_BINARY_DIR}/parser.yy
        scanner.ll
        )

#find_program(
#    mcpp_PATH
#    mcpp
#)

set(mcpp_PATH /opt/local/bin/mcpp)

# TODO: the one and only OS which have no cat is the by all beloved Microsoft Windows

add_custom_command(
    OUTPUT parser.yy

    COMMAND cat parser/preamble.yy > ${CMAKE_CURRENT_BINARY_DIR}/parser.yy
    COMMAND cat parser/0.yy >> ${CMAKE_CURRENT_BINARY_DIR}/parser.yy
    COMMAND cat parser/11-13.yy >> ${CMAKE_CURRENT_BINARY_DIR}/parser.yy
    COMMAND cat parser/14.yy >> ${CMAKE_CURRENT_BINARY_DIR}/parser.yy
    COMMAND cat parser/15.yy >> ${CMAKE_CURRENT_BINARY_DIR}/parser.yy
    COMMAND cat parser/16.yy >> ${CMAKE_CURRENT_BINARY_DIR}/parser.yy
    COMMAND cat parser/17.yy >> ${CMAKE_CURRENT_BINARY_DIR}/parser.yy
    COMMAND cat parser/2.yy >> ${CMAKE_CURRENT_BINARY_DIR}/parser.yy
    COMMAND cat parser/3.yy >> ${CMAKE_CURRENT_BINARY_DIR}/parser.yy
    COMMAND cat parser/postamble.yy >> ${CMAKE_CURRENT_BINARY_DIR}/parser.yy

    DEPENDS parser/preamble.yy
    parser/0.yy
    parser/11-13.yy
    parser/14.yy
    parser/15.yy
    parser/16.yy
    parser/17.yy
    parser/2.yy
    parser/3.yy
    parser/postamble.yy

    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}

    COMMENT "** build ${CMAKE_CURRENT_BINARY_DIR}/parser.yy"
    VERBATIM
)

BISON_TARGET(
    parser
    ${CMAKE_CURRENT_BINARY_DIR}/parser.yy
    ${CMAKE_CURRENT_BINARY_DIR}/parser.cc
    VERBOSE
    COMPILE_FLAGS "--defines --debug --verbose --graph --language=C++ --debug"
)

FLEX_TARGET(
    lexer
    scanner.ll
    ${CMAKE_CURRENT_BINARY_DIR}/scanner.cc
    COMPILE_FLAGS "-+ --debug"
)

ADD_FLEX_BISON_DEPENDENCY(lexer parser)

add_definitions(-DYYDEBUG=1)

add_library(
    parser
    driver.cc
    ${FLEX_lexer_OUTPUTS}
    ${BISON_parser_OUTPUTS}

    ${ADDITIONAL_SOURCES}
    ${parser_HEADERS}
)
