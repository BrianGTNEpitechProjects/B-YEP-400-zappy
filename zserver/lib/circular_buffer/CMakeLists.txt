cmake_minimum_required(VERSION 3.11)

project(circular_buffer)

SET(CMAKE_C_FLAGS "-W -Wall -Wextra -Werror -Wunused")

set(HEADER_FILES_PATH include)
set(SOURCE_FILES_PATH sources)
set(TESTS_SOURCES_FILES_PATH tests/sources)

file(
        GLOB_RECURSE
        SOURCE_FILES
        ${SOURCE_FILES_PATH}/*.c
)

file(
        GLOB_RECURSE
        HEADER_FILES
        ${HEADER_FILES_PATH}/*.h
)

add_library(circular_buffer ${SOURCE_FILES} ${HEADER_FILES})
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -iquote ${PROJECT_SOURCE_DIR}/${HEADER_FILES_PATH}")

file(
        GLOB_RECURSE
        TESTS_FILES
        ${TESTS_SOURCES_FILES_PATH}/*.c
)

add_executable(circular_buffer_test ${SOURCE_FILES} ${HEADER_FILES} ${TESTS_FILES})
target_link_libraries(circular_buffer_test criterion)