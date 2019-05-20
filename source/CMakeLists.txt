cmake_minimum_required(VERSION 3.13)
project(source)

set(CMAKE_CXX_STANDARD 14)

#link_libraries(ws2_32 wsock32)
include_directories(src)
include_directories(graph_viz)
include_directories(mapas)

add_executable(source src/main.cpp
        src/Edge.cpp src/EdgeInfo.cpp src/Exceptions.cpp src/Graph.cpp src/NodeInfo.cpp src/Person.cpp src/Vertex.cpp graph_viz/connection.cpp graph_viz/graphviewer.cpp
        src/Edge.h src/EdgeInfo.h src/Exceptions.h src/Graph.h src/NodeInfo.h src/Person.h src/Vertex.h graph_viz/connection.h graph_viz/graphviewer.h src/util.cpp src/util.h)

