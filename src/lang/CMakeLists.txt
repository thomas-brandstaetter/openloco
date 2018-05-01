
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(ADDITIONAL_SOURCES
        ${CMAKE_CURRENT_BINARY_DIR}/parser.yy
        scanner/scanner.ll
        )

# TODO: the one and only OS which have no cat is the by all beloved Microsoft Windows

set(parser_yy_path ${CMAKE_CURRENT_BINARY_DIR}/parser.yy)

add_custom_command(
    OUTPUT parser.yy

    COMMAND mkdir -p parser
    COMMAND cat parser/preamble.yy > ${parser_yy_path}
    COMMAND cat parser/0.yy >> ${parser_yy_path}
    COMMAND cat parser/11.yy >> ${parser_yy_path}
    COMMAND cat parser/12.yy >> ${parser_yy_path}
    COMMAND cat parser/13.yy >> ${parser_yy_path}
    COMMAND cat parser/14.yy >> ${parser_yy_path}
    COMMAND cat parser/15.yy >> ${parser_yy_path}
    COMMAND cat parser/16.yy >> ${parser_yy_path}
    COMMAND cat parser/17.yy >> ${parser_yy_path}
    COMMAND cat parser/2.yy >> ${parser_yy_path}
    COMMAND cat parser/3.yy >> ${parser_yy_path}
    COMMAND cat parser/postamble.yy >> ${parser_yy_path}

    DEPENDS parser/preamble.yy
    parser/0.yy
    parser/11.yy
    parser/12.yy
    parser/13.yy
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
    COMPILE_FLAGS "--language=C++"
)

FLEX_TARGET(
    lexer
    scanner/scanner.ll
    ${CMAKE_CURRENT_BINARY_DIR}/scanner.cc
    COMPILE_FLAGS "-+"
)

ADD_FLEX_BISON_DEPENDENCY(lexer parser)

add_definitions(-DYYDEBUG=1)


set(parser_HEADERS
    ast/common.h
    ast/ast.h
    driver/driver.h
    scanner/scanner.h
    driver/error.h
    )

add_library(
    parser
    driver/driver.cc
    driver/error.cc
    ${FLEX_lexer_OUTPUTS}
    ${BISON_parser_OUTPUTS}
    ${ADDITIONAL_SOURCES}
    ${parser_HEADERS}
)



add_executable(olc olc.cc)
target_link_libraries(olc parser)