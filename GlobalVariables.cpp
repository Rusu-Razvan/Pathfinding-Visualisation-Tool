#pragma once

#include "GlobalVariables.h"

using namespace std;

sf::RenderWindow window(sf::VideoMode(window_width, window_height, 32), "Pathfinder visualation tool",
	sf::Style::Fullscreen);

float window_width = 1920.0f;   //window info
float window_height = 1080.0f;

float menu_size = 200.0f;		//menu info

float matrixSquareSize = 40.0f;  //matrix info
float borderThickness = 1.5f;

float cellSize = matrixSquareSize + 2 * borderThickness;  //the size of a cell->borders+square

int matrix_width = (window_width / cellSize);   //number of col
int matrix_height = ((window_height - menu_size) / cellSize); //number of lines

float matrix_widthOffset = (window_width - matrix_width * cellSize) / 2; //distances from edges
float matrix_heightOffset = ((window_height - menu_size) - matrix_height * cellSize) / 2;

vector<vector<int>> matrix(matrix_height, vector<int>(matrix_width));

vector<vector<sf::RectangleShape>> visualMatrix(matrix_height, vector<sf::RectangleShape>(matrix_width));

int di[] = { -1, 0, 1, 0 };

int dj[] = { 0, 1, 0, -1 };

//int di[] = { -1, 1, 0, 0 };

//int dj[] = { 0, 0, -1, 1 };

queue<int> X, Y;

startPoint start_point;

finishPoint finish_point;

wallPoint wall_point;

ClickedSquare clickedSquare;

map<string, Button*> buttons;

string start = "start";
string finish = "finish";
string walls = "walls";
string deleteWalls = "deleteWalls";
string dfs = "dfs";
string bfs = "bfs";
string reset = "reset";
string maze = "maze";

string lastActiveButton;

int clicked_line;
int clicked_col;

bool picked_start = false;
bool picked_finish = false;
bool picked_walls = false;


Button startButton("Place start point", sf::Vector2f(25.f, 40.f));
Button finishButton("Place finish point", sf::Vector2f(25.f, 100.f));

Button wallsButton("Place walls", sf::Vector2f(220.f, 40.f));
Button deleteWallsButton("Delete walls", sf::Vector2f(220.f, 100.f));

Button createMazeButton("Create maze", sf::Vector2f(415.f, 40.f));
Button ResetMatrixButton("Reset Matrix", sf::Vector2f(415.f,100.f));

Button DFSButton("DFS Algorithm", sf::Vector2f(610.f, 40.f));
Button BFSButton("BFS Algorithm", sf::Vector2f(610.f, 100.f));


Button CloseWindowButton(" X", sf::Vector2f(1870.f, 15.f));
