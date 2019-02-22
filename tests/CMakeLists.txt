
set(CATCH_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../lib/catch/)
message("Catch include dir: " CATCH_INCLUDE_DIR)
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})

# Make test executable
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} TEST_SOURCES)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/../src SRC_FILES)
list(REMOVE_ITEM SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/../src/main.cpp)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)
message(${SRC_FILES})
add_executable(tests ${TEST_SOURCES} ${SRC_FILES})
target_link_libraries(tests Catch)

#add_test(test tests)
