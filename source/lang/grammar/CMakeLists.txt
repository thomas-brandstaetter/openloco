find_package(Java COMPONENTS Runtime)
include_directories(${CMAKE_CURRENT_BINARY_DIR})
message("include_directories(${CMAKE_CURRENT_BINARY_DIR})")
include_directories(${PROJECT_SOURCE_DIR}/../dependencies/antlr4/antlr4-cpp-runtime-4-2/antlr4-runtime)

add_custom_command(
    OUTPUT antrl_output
    COMMAND java -Xmx500M -cp "${PROJECT_SOURCE_DIR}/../dependencies/antlr4/antlr-4.7.2-complete.jar:$CLASSPATH" org.antlr.v4.Tool -Dlanguage=Cpp -visitor -no-listener -o ${CMAKE_CURRENT_BINARY_DIR}/antlr-gen ${CMAKE_CURRENT_SOURCE_DIR}/olcc.g4
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

set_source_files_properties(
    ${CMAKE_CURRENT_BINARY_DIR}/antlr-gen/olccBaseVisitor.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/antlr-gen/olccLexer.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/antlr-gen/olccParser.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/antlr-gen/olccVisitor.cpp
)

add_library(parser_internals
    ${CMAKE_CURRENT_BINARY_DIR}/antlr-gen/olccBaseVisitor.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/antlr-gen/olccLexer.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/antlr-gen/olccParser.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/antlr-gen/olccVisitor.cpp
)

target_link_libraries(parser_internals
    ${PROJECT_SOURCE_DIR}/../dependencies/antlr4/antlr4-cpp-runtime-4-2/lib/libantlr4-runtime.a
)

