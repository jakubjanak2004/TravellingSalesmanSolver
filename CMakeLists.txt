cmake_minimum_required(VERSION 3.29)
project(TravellingSalesmanSolver)

# Set the C++ standard to 20
set(CMAKE_CXX_STANDARD 20)

# Set the path for Graphviz
set(CMAKE_PREFIX_PATH "/opt/homebrew/opt/graphviz")

# Find Graphviz package using pkg-config
find_package(PkgConfig REQUIRED)
pkg_check_modules(GRAPHVIZ REQUIRED libgvc libcdt libcgraph)

# Include directories for Graphviz
include_directories(${GRAPHVIZ_INCLUDE_DIRS})

# Print Graphviz configuration for debugging
message(STATUS "Graphviz include directories: ${GRAPHVIZ_INCLUDE_DIRS}")
message(STATUS "Graphviz library directories: ${GRAPHVIZ_LIBRARY_DIRS}")
message(STATUS "Graphviz libraries: ${GRAPHVIZ_LIBRARIES}")

# Add library directories if necessary
link_directories(${GRAPHVIZ_LIBRARY_DIRS})

# Define the executable and add the source files
add_executable(TravellingSalesmanSolver
        main.cpp
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

# Link the Graphviz libraries
target_link_libraries(TravellingSalesmanSolver ${GRAPHVIZ_LIBRARIES})
