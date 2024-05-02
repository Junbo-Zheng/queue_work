cmake_minimum_required(VERSION 3.27)

project(
  queue_work
  VERSION 1.0
  LANGUAGES C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(QUEUE_WORK_THREAD_LEVEL
    "100"
    CACHE STRING "")
set(QUEUE_WORK_THREAD_SIZE
    "8192"
    CACHE STRING "")
set(QUEUE_WORK_THREAD_NAME
    "\"queue-work-thread\""
    CACHE STRING "")

add_compile_options(-Wall -Wextra -Werror -Wno-format -g)

set(queue_work_source main.c queue_work.c)

add_executable(${PROJECT_NAME} ${queue_work_source})

target_compile_definitions(
  ${PROJECT_NAME}
  PUBLIC -DCONFIG_QUEUE_WORK_THREAD_LEVEL=${QUEUE_WORK_THREAD_LEVEL})
target_compile_definitions(
  ${PROJECT_NAME}
  PUBLIC -DCONFIG_QUEUE_WORK_THREAD_SIZE=${QUEUE_WORK_THREAD_SIZE})
target_compile_definitions(
  ${PROJECT_NAME}
  PUBLIC -DCONFIG_QUEUE_WORK_THREAD_NAME=${QUEUE_WORK_THREAD_NAME})

target_include_directories(${PROJECT_NAME} PRIVATE ./)

target_link_libraries(${PROJECT_NAME} pthread)
