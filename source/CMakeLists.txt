cmake_minimum_required(VERSION 3.13)
project(source)

set(CMAKE_CXX_STANDARD 14)

#link_libraries(ws2_32 wsock32)
include_directories(src)
include_directories(src/graph_viz)
include_directories(resources/mapas)

add_executable(source src/main.cpp
        src/Edge.cpp src/EdgeInfo.cpp src/Exceptions.cpp src/Graph.cpp src/NodeInfo.cpp src/Person.cpp src/Vertex.cpp src/graph_viz/connection.cpp src/graph_viz/graphviewer.cpp
        src/Edge.h src/EdgeInfo.h src/Exceptions.h src/Graph.h src/NodeInfo.h src/Person.h src/Vertex.h src/graph_viz/connection.h src/graph_viz/graphviewer.h src/util.cpp src/util.h
        src/VisLoader.h src/VisLoader.cpp src/PersonGen.h src/PersonGen.cpp src/Car.h src/Car.cpp src/Menu.h src/Menu.cpp)


