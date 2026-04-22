cmake_minimum_required(VERSION 3.21)
project(PQWA)

set(CMAKE_CXX_STANDARD 23)

add_executable(PQWA main.cpp WaveformSample.cpp WaveformSample.h IO.h IO.cpp writelists.cpp)
