#include "GlobalFunctions.h"

const int MAX_ROWS = matrix_height;
const int MAX_COL = matrix_width;

void visualMatrixInitialization() {

	for (int i = 0; i < matrix_height; i++)
	{
		for (int j = 0; j < matrix_width; j++)
		{
			visualMatrix[i][j] = sf::RectangleShape(sf::Vector2f(matrixSquareSize, matrixSquareSize));

			visualMatrix[i][j].setOutlineThickness(borderThickness);
			visualMatrix[i][j].setOutlineColor(sf::Color::Black);

			visualMatrix[i][j].setFillColor(sf::Color(150, 150, 150));

			visualMatrix[i][j].setPosition(matrix_widthOffset + float(j) * cellSize,
				matrix_heightOffset + float(i) * cellSize + menu_size);
		}
	}
}

void ResetMatrix()
{
	start_point.line = -1;
	start_point.col = -1;
	finish_point.line = -1;
	finish_point.col = -1;

	for (int i = 0; i < matrix_height; i++)
	{
		for (int j = 0; j < matrix_width; j++)
		{
			matrix[i][j] = 0;
			visualMatrix[i][j].setFillColor(sf::Color(150, 150, 150));

		}
	}

	for (int i = 0; i < matrix_height; i++)
	{
		for (int j = 0; j < matrix_width; j++)
		{
			window.draw(visualMatrix[i][j]);
			
		}
	}

	window.display();
}

void drawScreen()
{
	window.clear(sf::Color::White); //background color + clearing the screen



	startButton.draw(window);
	finishButton.draw(window);
	wallsButton.draw(window);

	deleteWallsButton.draw(window);

	createMazeButton.draw(window);
	ResetMatrixButton.draw(window);

	DFSButton.draw(window);
	BFSButton.draw(window);

	CloseWindowButton.draw(window);


	for (int i = 0; i < matrix_height; i++)
	{
		for (int j = 0; j < matrix_width; j++)
		{
			window.draw(visualMatrix[i][j]);
		}

	}

	window.display();
}

void GetSquareIndexes(sf::Vector2i mousePos, int &line, int&col) {

		col = (mousePos.x - matrix_widthOffset) / (cellSize); 
		line = ((mousePos.y - menu_size - matrix_heightOffset) / (cellSize));
	
}

void manageMatrixClick(sf::Vector2i mousePos) {
	
	int line, col;

	GetSquareIndexes(mousePos, line, col);  //calculate the indexes of the clicked square

	if (buttons[start]->GetActiveStatus() == true)
	{
		if (start_point.line >= 0 && start_point.col >= 0)
			visualMatrix[start_point.line][start_point.col].setFillColor(sf::Color(150, 150, 150));

		start_point.line = line;
		start_point.col = col;

		if (matrix[line][col] != 2)  //if its not a finish
		{
			visualMatrix[start_point.line][start_point.col].setFillColor(sf::Color::Red);
			matrix[start_point.line][start_point.col] = 1;
		}


		buttons[start]->SetStatus(false);
		startButton.ChangeColor(sf::Color::Black);
	
	}

	if (buttons[finish]->GetActiveStatus() == true)
	{
		if (finish_point.line >= 0 && finish_point.col >= 0)
			visualMatrix[finish_point.line][finish_point.col].setFillColor(sf::Color(150, 150, 150));

		finish_point.line = line;
		finish_point.col = col;

		if (matrix[line][col] != 1)  //if its not a start
		{
			visualMatrix[finish_point.line][finish_point.col].setFillColor(sf::Color::Yellow);
			matrix[finish_point.line][finish_point.col] = 2;
		}

		buttons[finish]->SetStatus(false);
		finishButton.ChangeColor(sf::Color::Black);

	}

	if (buttons[walls]->GetActiveStatus() == true)
	{
		
		wall_point.line = line;
		wall_point.col = col;

		if (matrix[line][col] != 1 && matrix[line][col] != 2)
		{
			visualMatrix[wall_point.line][wall_point.col].setFillColor(sf::Color::Blue);
			matrix[wall_point.line][wall_point.col] = -1;
		}


	}

}

bool ClickedInsideMatrix(sf::Vector2i mousePos) {
	return mousePos.x < window_width - matrix_widthOffset && mousePos.x > matrix_widthOffset &&     //if clicked inside matrix
		mousePos.y < window_height - matrix_heightOffset && mousePos.y > menu_size + matrix_heightOffset;
}

void ActivateButton(const string &buttonName)
{
	if (!lastActiveButton.empty() && lastActiveButton != buttonName)	//deactivate the button that was previosly active(if any)
	{
		buttons[lastActiveButton]->SetStatus(false);				
		buttons[lastActiveButton]->ChangeColor(sf::Color::Black);
	}

	if (buttons[buttonName]->GetActiveStatus() == true)					//(if it is already active, deactivate it
	{
		buttons[buttonName]->SetStatus(false);
		buttons[buttonName]->ChangeColor(sf::Color::Black);
		lastActiveButton.clear();
	}
	else if (buttons[buttonName]->GetActiveStatus() == false)			//if its not active, activate it
	{
		buttons[buttonName]->SetStatus(true);
		buttons[buttonName]->ChangeColor(sf::Color(0, 100, 0));

		buttons[buttonName]->draw(window);
		window.display();

		lastActiveButton = buttonName;
		
		
	}
	

}

void generateMaze() {
	srand(static_cast<unsigned int>(time(0)));

	// Set walls and path
	for (int i = 0; i < matrix_height; ++i) {
		for (int j = 0; j < matrix_width; ++j) {
			// Set boundaries as walls
			if (i == 0 || i == matrix_height - 1 || j == 0 || j == matrix_width - 1) {
				matrix[i][j] = -1; // Wall
			}
			else {
				
				if (rand() % 4 == 0) { // 25% chance to create a wall
					matrix[i][j] = -1;
				}
			}
		}
	}

	
	matrix[start_point.line][start_point.col] = 1; // Start point
	matrix[finish_point.line][finish_point.col] = 2; // Finish point

	
	for (int i = 0; i < matrix_height; ++i) {
		for (int j = 0; j < matrix_width; ++j) {
			visualMatrix[i][j].setFillColor((matrix[i][j] == -1) ? sf::Color::Black :
				(matrix[i][j] == 1) ? sf::Color::Green :
				(matrix[i][j] == 2) ? sf::Color::Yellow :
				sf::Color::White);
		}
	}

	drawScreen(); 
}

bool isMazeSolveable()
{
	
	std::queue<std::pair<int, int>> q;
	q.push({ start_point.line, start_point.col });

	
	std::vector<std::vector<bool>> visited(matrix_height, std::vector<bool>(matrix_width, false));
	visited[start_point.line][start_point.col] = true; 


	const int directions[4][2] = { { -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 } };

	// BFS loop
	while (!q.empty()) {
		auto current = q.front();
		q.pop();

		int x = current.first;
		int y = current.second;

		
		if (x == finish_point.line && y == finish_point.col) {
			return true; 
		}

		
		for (int i = 0; i < 4; ++i) {
			int newX = x + directions[i][0];
			int newY = y + directions[i][1];

			
			if (newX >= 0 && newX < matrix_height && newY >= 0 && newY < matrix_width &&
				!visited[newX][newY] && matrix[newX][newY] != -1) {
				
				visited[newX][newY] = true;
				
				q.push({ newX, newY });
			}
		}
	}

	return false; 
}

void createMaze()
{
	generateMaze();
		while (isMazeSolveable() == false)
		{
			ResetMatrix();
			generateMaze();
		}
}

bool isValidMove(int x, int y) {
	return x >= 0 && x < matrix_height && y >= 0 && y < matrix_width && (matrix[x][y] == 0 || matrix[x][y] == 2);  //2=finish 0=nothing
}

void DFS() {
	std::stack<pair<int, int>> s;
	s.push({ start_point.line, start_point.col });

	matrix[start_point.line][start_point.col] = 1; 
	

	pair<int, int> parent[100][100];

	
	for (int i = 0; i < 100; ++i) {
		for (int j = 0; j < 100; ++j) {
			parent[i][j] = { -1, -1 };
		}
	}

	bool pathFound = false;

	while (!s.empty() && !pathFound) {
		pair<int, int> top = s.top();
		int x = top.first;
		int y = top.second;
		s.pop();

		for (int i = 0; i < 4; ++i) {
			int newX = x + di[i];
			int newY = y + dj[i];

			
			if (isValidMove(newX, newY)) {
				s.push({ newX, newY });

				
				matrix[newX][newY] = 1;
				visualMatrix[newX][newY].setFillColor(sf::Color::Green);


				parent[newX][newY] = { x, y };


				if (newX == finish_point.line && newY == finish_point.col) {
					visualMatrix[newX][newY].setFillColor(sf::Color::Yellow); // Highlight the finish point
					pathFound = true;
					break;
				}

				drawScreen();
				sf::sleep(sf::milliseconds(30));
			}
		}
	}

	// If a path was found, highlight it
	if (pathFound) {
		pair<int, int> current = { finish_point.line, finish_point.col };

		
		while (current.first != start_point.line || current.second != start_point.col) {
			if (!(current.first == finish_point.line && current.second == finish_point.col)) {
				visualMatrix[current.first][current.second].setFillColor(sf::Color::Magenta); // Highlight the path
			}
			current = parent[current.first][current.second];

			drawScreen();
			sf::sleep(sf::milliseconds(10));
		}
	}
}

void BFS() {
	queue<pair<int, int>> q;
	q.push({ start_point.line, start_point.col });

	

 	matrix[start_point.line][start_point.col] = 1;  

	pair<int, int> parent[100][100];

	// Initialize all elements to (-1, -1)
	for (int i = 0; i < 100; ++i) {
		for (int j = 0; j < 100; ++j) {
			parent[i][j] = make_pair(-1, -1);
		}
	}

	bool pathFound = false;

	while (!q.empty() && !pathFound) {
		pair<int, int> front = q.front();
		int x = front.first;
		int y = front.second;
		q.pop();

		
		for (int i = 0; i < 4; ++i) {
			int newX = x + di[i];
			int newY = y + dj[i];

			
			if (isValidMove(newX, newY)) {
				q.push({ newX, newY });

				matrix[newX][newY] = 1;
				visualMatrix[newX][newY].setFillColor(sf::Color::Green);

				parent[newX][newY] = { x, y };

				
				if (newX == finish_point.line && newY == finish_point.col) {
					visualMatrix[newX][newY].setFillColor(sf::Color::Yellow);
					pathFound = true;
					break;
				}

				drawScreen();
				sf::sleep(sf::milliseconds(30));
			}
		}

		if (pathFound == true)
			break;
	}

	// If a path was found, highlight it
	if (pathFound) {
		
		pair<int, int> current = { finish_point.line, finish_point.col };

		while (current.first != start_point.line || current.second != start_point.col) {
			
			if (!(current.first == finish_point.line && current.second == finish_point.col)) {
				visualMatrix[current.first][current.second].setFillColor(sf::Color::Magenta);
			}
			current = parent[current.first][current.second];
		
			drawScreen();
			sf::sleep(sf::milliseconds(10));
		}
		
	}
}
