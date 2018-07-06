set(HEADER_DIRECTORY ${CMAKE_SOURCE_DIR}/include/lang)

include_directories(${HEADER_DIRECTORY})
include_directories(${CMAKE_BINARY_DIR}/src/lang)
include_directories(${CMAKE_SOURCE_DIR}/src/lang)

add_subdirectory(scanner)
add_subdirectory(parser)

