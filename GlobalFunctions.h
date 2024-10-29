#pragma once
#include "GlobalVariables.h"

void visualMatrixInitialization();

void ResetMatrix();


void drawScreen();

void GetSquareIndexes(sf::Vector2i mousePos, int &return_line, int &return_col);

void manageMatrixClick(sf::Vector2i mousePos);

bool ClickedInsideMatrix(sf::Vector2i mousePos);

void ActivateButton(const string &buttonName);

void generateMaze();

bool isMazeSolveable();

void createMaze();

bool isValidMove(int x, int y);

void DFS();

void BFS();
