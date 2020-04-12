cmake_minimum_required(VERSION 3.15)
project(single_responsibility_principle)

set(CMAKE_CXX_STANDARD 14)

FIND_PACKAGE (Boost 1.72 COMPONENTS program_options REQUIRED)
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR})

add_executable(single_responsibility_principle main.cpp)
TARGET_LINK_LIBRARIES(single_responsibility_principle LINK_PUBLIC ${Boost_Libraries})