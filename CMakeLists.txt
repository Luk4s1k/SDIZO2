cmake_minimum_required(VERSION 3.22)
project(SDIZO2)

set(CMAKE_CXX_STANDARD 14)

add_executable(SDIZO2 main.cpp Graph/ListGraph.cpp Graph/ListGraph.h Graph/MatrixGraph.cpp Graph/MatrixGraph.h BinaryHeap/BinaryHeap.cpp BinaryHeap/BinaryHeap.h Menu/ListGraphMenu.cpp Menu/ListGraphMenu.h Menu/MatrixGraphMenu.cpp Menu/MatrixGraphMenu.h Measurments/ListGMeasurments.cpp Measurments/ListGMeasurments.h Measurments/MatrixGMeasurments.cpp Measurments/MatrixGMeasurments.h Measurments/MeasureTime.cpp Measurments/MeasureTime.h)
