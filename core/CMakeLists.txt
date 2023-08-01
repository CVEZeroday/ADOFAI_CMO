cmake_minimum_required(VERSION 3.8)
project("ADOFAI_CMO_CORE" C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_C_COMPILER gcc)

set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 0)
set(PROJECT_VERSION_PATCH 1)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_VERBOSE_MAKEFILE true)

set(OUTPUT_ELF
  "${CMAKE_PROJECT_NAME}-${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}.out"
  )

set(SRC_FILES
  ${CMAKE_SOURCE_DIR}/src/main.c
  ${CMAKE_SOURCE_DIR}/src/core.c
  ${CMAKE_SOURCE_DIR}/src/resizer.c
  ${CMAKE_SOURCE_DIR}/src/converter.c
  )

include_directories(
  include ${CMAKE_SOURCE_DIR}/include
  )

add_compile_options( -Wall )

set(OUTPUT_DIR ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})

add_executable(
  ${OUTPUT_ELF}
  ${SRC_FILES}
  )
