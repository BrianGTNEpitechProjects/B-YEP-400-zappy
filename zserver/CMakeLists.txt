cmake_minimum_required(VERSION 3.11)

project(PSU_zappy_2018)

SET(CMAKE_C_FLAGS "-W -Wall -Wextra -Werror -Wunused")

set(HEADER_FILES_PATH ${PROJECT_SOURCE_DIR}/include)
set(SOURCE_FILES_PATH ${PROJECT_SOURCE_DIR}/sources)
set(TESTS_SOURCES_FILES_PATH ${PROJECT_SOURCE_DIR}/tests/sources)

set(LIB_PATH ${PROJECT_SOURCE_DIR}/lib)
set(LIB_CIRCULAR_BUFFER_PATH ${LIB_PATH}/circular_buffer)
set(LIB_CONTAINERS_PATH ${LIB_PATH}/containers)

add_subdirectory(${LIB_CONTAINERS_PATH})
add_subdirectory(${LIB_CIRCULAR_BUFFER_PATH})

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

add_executable(zappy_server ${SOURCE_FILES} ${HEADER_FILES})
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -iquote ${HEADER_FILES_PATH} -iquote ${LIB_CIRCULAR_BUFFER_PATH}/include -iquote ${LIB_CONTAINERS_PATH}/include")
target_link_libraries(zappy_server circular_buffer containers)

file(
        GLOB_RECURSE
        TESTS_FILES
        ${TESTS_SOURCES_FILES_PATH}/*.c
)

set(TESTS_SOURCES ${SOURCE_FILES} include/network_client_user_map.h)
list(REMOVE_ITEM TESTS_SOURCES ${SOURCE_FILES_PATH}/main.c)

add_executable(zappy_server_test ${TESTS_SOURCES} ${HEADER_FILES} ${TESTS_FILES})
target_link_libraries(zappy_server_test criterion circular_buffer containers)