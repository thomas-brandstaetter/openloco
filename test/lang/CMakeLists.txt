
if (Win32)
    include_directories(${CMAKE_BINARY_DIR}\\src\\lang)
endif()

add_executable(parser_play  parser_play.cc)
target_link_libraries(parser_play  parser)

add_executable(scanner_play scanner_play.cc)
target_link_libraries(scanner_play  parser)

add_subdirectory(scanner)
add_subdirectory(parser)

