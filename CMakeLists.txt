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

# Define the executable for your project
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
        helper/Helper.cpp
        helper/Helper.h
)

# Link the Graphviz libraries
target_link_libraries(TravellingSalesmanSolver ${GRAPHVIZ_LIBRARIES})

# Download and link Google Test
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Define the test executable (with a separate main for tests)
add_executable(run_tests
        test/main.cpp  # Test main that runs all tests
        test/test_TSInstance.cpp  # Your test file(s)
        graph/Node.cpp  # Add the necessary source files that need to be tested
        graph/Edge.cpp
        graph/Graph.cpp
        graph/TSInstance.cpp
        files/FileManager.cpp
        helper/Helper.cpp
)

# Link the test executable with Google Test and your source files
target_link_libraries(run_tests gtest gtest_main ${GRAPHVIZ_LIBRARIES})

# Add test target
add_test(NAME run_tests COMMAND run_tests)
