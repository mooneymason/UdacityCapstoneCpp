cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread")
add_definitions(-std=c++17)

project(Capstone)


# Find all executables
file(GLOB project_SRCS src/*.cpp) #src/*.h

# Add project executable


include_directories(${PROJECT_SOURCE_DIR})
add_executable(Capstone src/capstone.cpp src/InputParser.cpp src/MoveableObject.cpp src/Person.cpp src/Threat.cpp src/Node.cpp src/Floor.cpp src/Simulate.cpp src/DefaultInputParameters.cfg) 