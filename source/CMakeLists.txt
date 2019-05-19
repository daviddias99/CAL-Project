cmake_minimum_required(VERSION 3.14)
project(source)

set(CMAKE_CXX_STANDARD 14)

link_libraries(ws2_32 wsock32)

add_executable(source main.cpp
        Edge.cpp EdgeInfo.cpp Exceptions.cpp Graph.cpp NodeInfo.cpp Person.cpp Vertex.cpp graph_viz/connection.cpp graph_viz/graphviewer.cpp
        Edge.h EdgeInfo.h Exceptions.h Graph.h NodeInfo.h Person.h Vertex.h graph_viz/connection.h graph_viz/graphviewer.h util.cpp util.h)

