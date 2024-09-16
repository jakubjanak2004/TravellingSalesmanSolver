cmake_minimum_required(VERSION 3.29)
project(TravellingSalesmanSolver)

set(CMAKE_CXX_STANDARD 20)

add_executable(TravellingSalesmanSolver main.cpp
        graph/Node.cpp
        graph/Node.h
        graph/Edge.cpp
        graph/Edge.h
        graph/Graph.cpp
        graph/Graph.h
        graph/TSInstance.cpp
        graph/TSInstance.h
        files/FileManager.cpp
        files/FileManager.h
        controller/Controller.cpp
        controller/Controller.h
)
