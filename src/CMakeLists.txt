aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SOURCES)

message("here" ${SOURCES})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)
add_executable(tiny ${SOURCES})
