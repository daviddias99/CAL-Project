//
// Created by david on 27-05-2019.
//

#ifndef SOURCE_MENU_H
#define SOURCE_MENU_H

void chooseCity();

#include <iostream>
#include <string>
#include <graph_viz/graphviewer.h>
#include "Graph.h"
#include "PersonGen.h"
#include "VisLoader.h"
#include "Car.h"

using namespace std;

void showMainMenu();
void runMainMenu();
void chooseCity();
void initViewer(bool autoPosition = false);
void generatePeople();
void chooseDriver();
void showWholeMap();
void checkAlgorithm();
bool showDFSAfterDriver();

#endif SOURCE_MENU_H
