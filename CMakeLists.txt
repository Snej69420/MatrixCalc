cmake_minimum_required(VERSION 3.23)
project(MatrixCalc)

set(CMAKE_CXX_STANDARD 14)

add_executable(MatrixCalc main.cpp matrix.cpp matrix.h)

add_executable(Site MatrixCalc matrix.cpp matrix.h WebInterface/WebServer.cpp WebInterface/WebServer.h WebInterface/crow.h WebInterface/main.cpp)
