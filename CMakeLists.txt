CMAKE_MINIMUM_REQUIRED(VERSION 2.8.0)
set(PROJECT_NAME_STR queue-test)
project(${PROJECT_NAME_STR} C CXX)

#-------------------------------------------------------------------------------
# The version number
#-------------------------------------------------------------------------------
set (queue-test_VERSION_MAJOR 0)
set (queue-test_VERSION_MINOR 2)
set (queue-test_VERSION_STRING ${queue-test_VERSION_MAJOR}.${queue-test_VERSION_MINOR})

#-------------------------------------------------------------------------------
# Locate the threading lib and add it to the linked libs
#-------------------------------------------------------------------------------
find_package(Threads)
set(LIBS ${LIBS} ${CMAKE_THREAD_LIBS_INIT})

#-------------------------------------------------------------------------------
# example and benchmark program
#-------------------------------------------------------------------------------
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "build/bin/")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/bin)
set(PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)

include_directories(${INCLUDES} ${PROJECT_INCLUDE_DIR} ${PROJECT_SOURCE_DIR}/src)
file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)
add_executable(${PROJECT_NAME} ${SRC_FILES})
target_link_libraries(${PROJECT_NAME} ${LIBS})

#-------------------------------------------------------------------------------
# Set compiler flags
#-------------------------------------------------------------------------------
set(PROJECT_COMPILER_FLAGS ${PROJECT_COMPILER_FLAGS} "${CMAKE_CXX_FLAGS} -O2 -std=c++11 -fPIC -Wall -pedantic -Wextra -Werror -Wno-long-long")

set_property(
  TARGET ${PROJECT_NAME}
  APPEND PROPERTY COMPILE_FLAGS ${PROJECT_COMPILER_FLAGS})
