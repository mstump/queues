CMAKE_MINIMUM_REQUIRED(VERSION 2.8.0)
set(PROJECT_NAME_STR spsc)
project(${PROJECT_NAME_STR} C CXX)

#-------------------------------------------------------------------------------
# The version number
#-------------------------------------------------------------------------------
set (libuv-test_VERSION_MAJOR 0)
set (libuv-test_VERSION_MINOR 1)
set (libuv-test_VERSION_STRING ${spsc_VERSION_MAJOR}.${spsc_VERSION_MINOR})

#-------------------------------------------------------------------------------
# example and benchmark program
#-------------------------------------------------------------------------------
set(PROJECT_LIB_NAME ${PROJECT_NAME_STR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "build/bin/")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/bin)
set(PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)

include_directories(${INCLUDES} ${PROJECT_INCLUDE_DIR} ${PROJECT_SOURCE_DIR}/src)
file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)
add_executable(${PROJECT_NAME} ${SRC_FILES})

#-------------------------------------------------------------------------------
# Set compiler flags
#-------------------------------------------------------------------------------
set(PROJECT_COMPILER_FLAGS "${CMAKE_CXX_FLAGS} -O2 -std=c++0x -fPIC -Wall -pedantic -Wextra -Werror -Wno-long-long")

set_property(
  TARGET ${PROJECT_NAME}
  APPEND PROPERTY COMPILE_FLAGS ${PROJECT_COMPILER_FLAGS})
