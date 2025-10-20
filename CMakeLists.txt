cmake_minimum_required(VERSION 3.29)
project(LifeSketch)

IF(CMAKE_COMPILER_IS_GNUCXX)
    ADD_COMPILE_OPTIONS(-O3)
ENDIF(CMAKE_COMPILER_IS_GNUCXX)

set(CMAKE_CXX_STANDARD 11)

add_executable(
        LifeSketch main.cpp
        tool/BOBHash32.h
        tool/loadData.h
        sketch/CM/LifeSketch.h
        tool/inc.h
        report/Frequency/report_N.h
)