#pragma once
#include <vector>
#include <map>
#include <queue>
#include <stack>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Button.h"

using namespace std;

extern sf::RenderWindow window;

extern float window_width;   //window info
extern float window_height;

extern float menu_size;		//menu info

extern float matrixSquareSize;  //matrix info
extern float borderThickness;

extern float cellSize;  //the size of a cell->borders+square

extern int matrix_width;   //number of col
extern int matrix_height; //number of lines

extern float matrix_widthOffset; //distances from edges
extern float matrix_heightOffset;

extern vector<vector<int>> matrix;

extern vector<vector<sf::RectangleShape>> visualMatrix;

extern struct startPoint {
	int line, col;
};

extern struct finishPoint {
	int line, col;
};

extern struct wallPoint {
	int line, col;
}wall_point;

extern struct ClickedSquare {
	int line, col;
};

extern int di[];

extern int dj[];

extern queue<int> X, Y;

extern startPoint start_point;

extern finishPoint finish_point;

extern ClickedSquare clickedSquare;

extern map<string, Button*> buttons;

extern string start;
extern string finish;
extern string walls;
extern string deleteWalls;
extern string dfs;
extern string bfs;
extern string reset;
extern string maze;

extern string lastActiveButton;

extern int clicked_line;
extern int clicked_col;

extern bool picked_start;
extern bool picked_finish;
extern bool picked_walls;

extern Button startButton;
extern Button finishButton;

extern Button wallsButton;
extern Button deleteWallsButton;

extern Button createMazeButton;
extern Button ResetMatrixButton;

extern Button DFSButton;
extern Button BFSButton;


extern Button CloseWindowButton;