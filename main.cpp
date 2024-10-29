#include "GlobalVariables.h"
#include "GlobalFunctions.h"
#include "Button.h"

#include <iostream>
#include <Windows.h>

#include <SFML\Graphics.hpp>
#include<vector>
#include <string>
#include <map>

using namespace std;

int main() {			

	

	for (int i = 0; i < matrix_height; i++)
	{
		for (int j = 0; j < matrix_width; j++)
		{
			matrix[i][j] = 0; //default: no meaning like start point,end point etc.
		}
	}
	

	visualMatrixInitialization();

	sf::Vector2i mousePos;

	buttons[start] = &startButton;
	buttons[finish] = &finishButton;
	buttons[walls] = &wallsButton;
	buttons[deleteWalls] = &deleteWallsButton;
	buttons[dfs] = &DFSButton;
	buttons[bfs] = &BFSButton;
	buttons[reset] = &ResetMatrixButton;
	buttons[maze] = &createMazeButton;
	

	

	start_point.line = -1;
	start_point.col = -1;
	finish_point.line = -1;
	finish_point.col = -1;
	

	while (window.isOpen()) {

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

		sf::Event evnt;

		while (window.pollEvent(evnt))
		{
			switch (evnt.type)
			{
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::MouseButtonPressed:
				if (evnt.mouseButton.button == sf::Mouse::Left)
				{
					 mousePos = sf::Mouse::getPosition(window); //get the coords of the mouse click

					if (startButton.isClicked(mousePos))
					{
						ActivateButton(start);
					}

					if (finishButton.isClicked(mousePos))
					{
						ActivateButton(finish);
					}

					if (wallsButton.isClicked(mousePos))
					{
						ActivateButton(walls);
					}

					if (deleteWallsButton.isClicked(mousePos))
					{
						ActivateButton(deleteWalls);
					}
					
					if (DFSButton.isClicked(mousePos))
					{
						if (start_point.line == -1 || finish_point.line == -1)
						{
							printf("You must first place a start or a finish point!\n");
						}
						else {
							ActivateButton(dfs);

							DFS();

							buttons[dfs]->SetStatus(false);
							buttons[dfs]->ChangeColor(sf::Color::Black);
						}
					}

					if (BFSButton.isClicked(mousePos))
					{
						if (start_point.line == -1 || finish_point.line == -1)
						{
							printf("You must first place a start or a finish point!\n");
						}
						else {
							ActivateButton(bfs);

							BFS();

							buttons[bfs]->SetStatus(false);
							buttons[bfs]->ChangeColor(sf::Color::Black);
						}
					}

					if (createMazeButton.isClicked(mousePos))
					{
						if (start_point.line == -1 || finish_point.line == -1)
						{
							printf("You must first place a start or a finish point!\n");
						}
						else {
							ActivateButton(maze);
							createMaze();
						}
					}

					if (ResetMatrixButton.isClicked(mousePos))
					{
						ActivateButton(reset);
						ResetMatrix();

						buttons[reset]->SetStatus(false);
						buttons[reset]->ChangeColor(sf::Color::Black);
					}

					if (CloseWindowButton.isClicked(mousePos))
						window.close();

				}
				break;

			}
		}



		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			mousePos = sf::Mouse::getPosition(window);

			int line, col;

			

			if (ClickedInsideMatrix(mousePos)) {

				//manageMatrixClick(mousePos);

				GetSquareIndexes(mousePos, line, col);  //calculate the indexes of the clicked square

				if (buttons[start]->GetActiveStatus() == true)
				{
					if (start_point.line >= 0 && start_point.col >= 0)
					{
						visualMatrix[start_point.line][start_point.col].setFillColor(sf::Color(150, 150, 150));
						matrix[start_point.line][start_point.col] = 0;
					}
					start_point.line = line;
					start_point.col = col;

					if (matrix[line][col] != 2)
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
					{
						visualMatrix[finish_point.line][finish_point.col].setFillColor(sf::Color(150, 150, 150));
						matrix[finish_point.line][finish_point.col] = 0;
					}
					finish_point.line = line;
					finish_point.col = col;

					if (matrix[line][col] != 1)
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

				if (buttons[deleteWalls]->GetActiveStatus() == true)
				{
					wall_point.line = line;
					wall_point.col = col;

					if (matrix[line][col] != 1 && matrix[line][col] != 2)
					{
						visualMatrix[wall_point.line][wall_point.col].setFillColor(sf::Color(150,150,150));
						matrix[wall_point.line][wall_point.col] = 0;
					}

				}

				

			}

		}
		
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
			window.close();

		


		window.display();
			
	}

	return 0;
} 