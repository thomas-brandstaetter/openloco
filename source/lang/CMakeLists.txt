
include_directories(${HEADER_DIRECTORY})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})


# antlr4

execute_process(
    COMMAND mkdir -p ../build_shared/antlr4
    COMMAND java -Xmx500M -cp "../dependencies/antlr4/antlr-4.7.2-complete.jar:$CLASSPATH" org.antlr.v4.Tool -Dlanguage=Cpp -no-listener -visitor -o ../build_shared/antlr ./source/lang/grammar/olcc.g4
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)

include_directories(${PROJECT_SOURCE_DIR}../build_shared/antlr/source/lang/grammar)

# ------

add_library(parser

    ast/ast.h
    ast/forward_ast.h
    ast/meta.h

    driver/driver.h
    driver/driver.cc
    driver/error.h
    driver/error.cc
    driver/file.h
    driver/file.cc

    codegen/code_generator.h
    codegen/code_generator.cc
    codegen/code_visitor.h
    codegen/environment.h
    codegen/environment.cc

    ${ADDITIONAL_SOURCES}
)


target_link_libraries(
        parser
        ${$OPENLOCO_LLVM_LIBS}

)
