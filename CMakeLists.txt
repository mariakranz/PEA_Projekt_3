cmake_minimum_required(VERSION 3.26)
project(PEA_Projekt_3)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(PEA_Projekt_3 main.cpp
        data/DataReader.cpp
        graph/TSPGraph.cpp
        representations/GraphRep.cpp
        xmlParser/tinyxml2.cpp
        algorithms/GeneticAlgorithm.cpp
        algorithms/GeneticAlgorithm.h
        data/Tests.h
        data/Tests.cpp)
