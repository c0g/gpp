cmake_minimum_required(VERSION 2.8.4)
project(GP)
SET(CMAKE_CXX_FLAGS "-std=c++11")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
find_package(Eigen3 REQUIRED)
message(${EIGEN3_INCLUDE_DIR})
include_directories(${EIGEN3_INCLUDE_DIR} src src/kernel)
add_subdirectory(googletest)
add_subdirectory(tests)

set(SOURCE_FILES main.cpp)

add_executable(GP ${SOURCE_FILES})