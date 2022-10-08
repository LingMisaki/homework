cmake_minimum_required(VERSION 3.10)
project(demo)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV 4 REQUIRED)

add_executable(problem2 main.cpp)
add_executable(probelm3 main2.cpp)
target_link_libraries(problem2 ${OpenCV_LIBS})
target_link_libraries(probelm3 ${OpenCV_LIBS})
