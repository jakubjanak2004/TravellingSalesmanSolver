# --------------------------------------------------------------the old cmake--------------------------------------------------------------
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
link_directories(/opt/homebrew/opt/graphviz/lib)

# Find Boost with program_options and system components
find_package(Boost 1.75 REQUIRED COMPONENTS system program_options)

if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    message(STATUS "Boost include directories: ${Boost_INCLUDE_DIRS}")
    message(STATUS "Boost libraries: ${Boost_LIBRARIES}")
else()
    message(FATAL_ERROR "Boost not found!")
endif()

# Define the executable for your project
add_executable(tss
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
        helper/Helper.cpp
        helper/Helper.h
)

# Link the Graphviz and Boost libraries
target_link_libraries(tss ${GRAPHVIZ_LIBRARIES} Boost::system Boost::program_options)

enable_testing()

# Define the test executable (with a separate main for tests)
add_executable(run_tests
        test/catch.hpp
        test/catch.cpp
        test/test_main.cpp
        test/test_TSInstance.cpp
        test/test_Edge.cpp
        test/test_Node.cpp
        test/test_Graph.cpp

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
        helper/Helper.cpp
        helper/Helper.h
        test/catch.hpp
)

# Link the test executable with Google Test, Graphviz, and Boost
target_link_libraries(run_tests ${GRAPHVIZ_LIBRARIES} Boost::system Boost::program_options)

# Add test target
include(CTest)
add_test(NAME all COMMAND run_tests)