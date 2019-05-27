//
// Created by david on 21-05-2019.
//

#ifndef SOURCE_VISLOADER_H
#define SOURCE_VISLOADER_H

#include "Graph.h"
#include "graph_viz/graphviewer.h"

#define MAP_FOLDER_PATH "../resources/mapas/"
#define EDGE_FILE_PATH "/T01_edges_"
#define NODE_XY_FILE_PATH "/T01_nodes_X_Y_"
#define NODE_LL_FILE_PATH "/T01_nodes_lat_lon_"

bool loadGraphForVis(GraphViewer* gv, string cidade);
void loadGraphForVis(GraphViewer* gv, Graph& graph);

#endif //SOURCE_VISLOADER_H
