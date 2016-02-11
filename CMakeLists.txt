cmake_minimum_required(VERSION 3.3)
project(hash_code)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

set(SOURCE_FILES main.cpp simulation.cpp simulation.h product.cpp product.cpp product.h warehouse.cpp warehouse.h order.cpp order.h command.cpp command.h drone.cpp drone.h)
add_executable(hash_code ${SOURCE_FILES})