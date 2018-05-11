
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

BISON_TARGET(
        parser
        ${CMAKE_CURRENT_SOURCE_DIR}/parser/parser.yy
        ${CMAKE_CURRENT_BINARY_DIR}/parser.cc
        VERBOSE
        COMPILE_FLAGS "--language=C++"
)

FLEX_TARGET(
        scanner
        ${CMAKE_CURRENT_SOURCE_DIR}/scanner/scanner.ll
        ${CMAKE_CURRENT_BINARY_DIR}/scanner.cc
        COMPILE_FLAGS "-+"
)

ADD_FLEX_BISON_DEPENDENCY(scanner parser)


add_library(
        parser
        driver/driver.cc
        driver/error.cc
        scanner/scanner.h
        ast/ast.h
        ${CMAKE_CURRENT_BINARY_DIR}/parser.hh
        ${FLEX_scanner_OUTPUTS}
        ${BISON_parser_OUTPUTS}
        ${ADDITIONAL_SOURCES}
        ${parser_HEADERS}
        ast/forward_ast.h)
