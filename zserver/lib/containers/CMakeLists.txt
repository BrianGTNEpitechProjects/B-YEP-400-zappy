cmake_minimum_required(VERSION 3.11)

project(containers)

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

add_library(containers ${SOURCE_FILES} ${HEADER_FILES})
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -iquote ${PROJECT_SOURCE_DIR}/${HEADER_FILES_PATH}")