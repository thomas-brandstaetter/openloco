
set(HEADER_DIRECTORY ${CMAKE_SOURCE_DIR}/include/lang)

include_directories(${HEADER_DIRECTORY})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

BISON_TARGET(
        parser
        ${CMAKE_CURRENT_SOURCE_DIR}/parser/parser.yy
        ${CMAKE_CURRENT_BINARY_DIR}/parser.cc
        VERBOSE
        COMPILE_FLAGS "--language=C++ --verbose"
)

FLEX_TARGET(
        scanner
        ${CMAKE_CURRENT_SOURCE_DIR}/scanner/scanner.ll
        ${CMAKE_CURRENT_BINARY_DIR}/scanner.cc
        COMPILE_FLAGS "-+"
)

ADD_FLEX_BISON_DEPENDENCY(scanner parser)


set(    PARSER_HEADERS
        ${HEADER_DIRECTORY}/ast/ast.h
        ${HEADER_DIRECTORY}/ast/codegen.h
        ${HEADER_DIRECTORY}/ast/forward_ast.h
        ${HEADER_DIRECTORY}/ast/meta.h

        ${HEADER_DIRECTORY}/driver/file.h
        ${HEADER_DIRECTORY}/driver/driver.h

        ${HEADER_DIRECTORY}/scanner/scanner.h

        ${HEADER_DIRECTORY}/codegen/code_generator.h)

add_library(
        parser
        driver/driver.cc
        driver/file.cc
        driver/error.cc
        ${CMAKE_CURRENT_BINARY_DIR}/parser.hh
        ${FLEX_scanner_OUTPUTS}
        ${BISON_parser_OUTPUTS}
        ${ADDITIONAL_SOURCES}
        ${PARSER_HEADERS}
        codegen/code_generator.cc)


target_link_libraries(
        parser
        ${$OPENLOCO_LLVM_LIBS}

)