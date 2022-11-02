cmake_minimum_required(VERSION 3.10)
project(demo)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV 4 REQUIRED)
include_directories("/usr/include/eigen3")
add_executable(problem1 main1.cpp)
#add_executable(probelm2 main2.cpp)
#add_executable(probelm3 main3.cpp)
target_link_libraries(problem1 ${OpenCV_LIBS})
#target_link_libraries(probelm2 ${OpenCV_LIBS})
#target_link_libraries(probelm3 ${OpenCV_LIBS})

