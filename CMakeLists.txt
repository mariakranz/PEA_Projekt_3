cmake_minimum_required(VERSION 3.26)
project(PEA_Projekt_3)

set(CMAKE_CXX_STANDARD 17)

add_executable(PEA_Projekt_3 main.cpp
        data/DataReader.cpp
        graph/TSPGraph.cpp
        representations/GraphRep.cpp
        xmlParser/tinyxml2.cpp)
