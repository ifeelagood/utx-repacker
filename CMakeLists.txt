cmake_minimum_required(VERSION 3.5)
project(utx_unpacker)

file(GLOB SRC "src/*.cpp")
add_executable(utx_unpacker ${SRC})

# set optmisation level
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

# set c++ standard
set(CMAKE_CXX_STANDARD 20)
