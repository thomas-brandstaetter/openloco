
include_directories(${HEADER_DIRECTORY})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR}/grammar)
include_directories(${PROJECT_SOURCE_DIR}/../dependencies/antlr4/antlr4-cpp-runtime-4-2/antlr4-runtime)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})


# antlr4
add_subdirectory(grammar)
# ------

add_library(parser

    ast/ast.h
    ast/forward_ast.h
    ast/meta.h

    driver/driver.h
    driver/driver.cc
    driver/error.h
    driver/error.cc
    #driver/file.h
    #driver/file.cc

    codegen/code_generator.h
    codegen/code_generator.cc
    #codegen/code_visitor.h
    #codegen/environment.h
    #codegen/environment.cc

    ${ADDITIONAL_SOURCES}
)

target_link_libraries(
    parser
    parser_internals
)

add_executable(
    olcc
    olc.cc
)

target_link_libraries(
    olcc
    parser
)
