#include "graph.h"

#include <iostream>
#include <random>
#include <ctime>

using namespace std;

const int WEIGHT = 20;
const int HEIGHT = 20;

class Tetris
{
private:
	char map[HEIGHT][WEIGHT];
	int currentGraph;
	int currentX;
	int currentY;
	int score;
public:
	bool GameOver;
	Tetris();
	void initialParameter();
	void showMap();
	bool checkCollision(char);
	void graphMove(char);
	void graphRotate();
	void checkAndRemove();
	void uploadGraph();
	void clearCurrentGraph();
	void checkGameOver(int);
};

Tetris::Tetris()
{
	//Initial Map
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WEIGHT; j++)
		{
			map[i][j] = '.';
		}
	}

	for (int j = 0; j <= WEIGHT; j += (WEIGHT - 1))
	{
		for (int i = 0; i < HEIGHT; i++)
		{
			map[i][j] = '|';
		}
	}

	score = 0;
	GameOver = 0;
	initialParameter();
}

void Tetris::initialParameter()
{
	srand(time(NULL));
	currentGraph = rand() % 7;
	currentX = 7;
	currentY = -4;
}

void Tetris::showMap()
{
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WEIGHT; j++)
		{
			cout << map[i][j];
		}
		cout << endl;
	}

	//Show score
	cout << "score:" << score;
}

bool Tetris::checkCollision(char direction)
{
	int nextY = currentY;
	int nextX = currentX;
	switch (direction)
	{
		//Go down
		case 'd':
			nextY++;
			for (int j = 0; j < 8; j += 2)
			{
				for (int i = 3; i >= 0; i--)
				{
					if (graph[currentGraph][i][j] == '[')
					{
						if (graph[currentGraph][i][j] == map[nextY + i][nextX + j] or (nextY + i) == HEIGHT)
						{ 
							checkAndRemove();
							checkGameOver(i);
							initialParameter();
							return true;
						}
						break;
					}
				}
			}
			break;

		//Go right
		case 'r':
			nextX += 2;
			for (int i = 0; i < 4; i++)
			{
				for (int j = 7; j >= 0; j -= 2)
				{
					if (graph[currentGraph][i][j] == ']')
					{
						if (graph[currentGraph][i][j] == map[nextY + i][nextX + j] or (nextX + j) == WEIGHT)
							return true;
						break;
					}
				}
			}
			break;

		//Go left
		case 'l':
			nextX -= 2;
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 8; j += 2)
				{
					if (graph[currentGraph][i][j] == '[')
					{
						if (graph[currentGraph][i][j] == map[nextY + i][nextX + j] or (nextX + j) == -1)
							return true;
						break;
					}
				}
			}
			break;
	}
	return false;
}

void Tetris::graphMove(char direction)
{
	switch (direction)
	{
		case 'd':
			currentY++;
			break;
		case 'r':
			currentX += 2;
			break;
		case 'l':
			currentX -= 2;
			break;
	}
}

void Tetris::graphRotate()
{
	char graphBeforeR[4][4];
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (graph[currentGraph][i][j * 2] == '[')
				graphBeforeR[i][j] = '*';
			else
				graphBeforeR[i][j] = ' ';
		}
	}

	//Get the rotate matrix
	char graphAfterR[4][4];
	for (int j = 3; j >= 0; j--)
	{
		for (int i = 0; i < 4; i++)
		{
			graphAfterR[i][j] = graphBeforeR[4 - j - 1][i];
		}
	}

	//Check if Rotate
	bool flag = 1;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (graphAfterR[i][j] == '*')
			{
				if((map[currentY + i][currentX + j * 2] == '[' and graphBeforeR[i][j] != graphAfterR[i][j]) or (currentY + i) >= HEIGHT or (currentX + j * 2 + 1) >= WEIGHT or (currentX + j * 2) <= -1)
				{ 
					flag = 0;
					break;
				}
			}
		}
		if (flag == 0)
		{
			break;
		}
	}

	//If flag equal to 1, rotate graph.
	if (flag == 1)
	{
		clearCurrentGraph();
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				graph[currentGraph][i][j] = ' ';
			}
		}

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (graphAfterR[i][j] == '*')
				{
					graph[currentGraph][i][j * 2] = '[';
					graph[currentGraph][i][j * 2 + 1] = ']';
				}
			}
		}
		uploadGraph();
	}
}

void Tetris::checkAndRemove()
{
	int times = 0;
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 1; j < WEIGHT - 1; j++)
		{
			if (map[i][j] == '.')
				break;
			if (j == WEIGHT - 2)
			{
				times += (times/2 + 1);
				//The cube above this line goes one cube down.
				if(i - 1 > 0)
				{
					for (int y = i - 1; y >= 0; y--)
					{
						for (int x = 1; x < WEIGHT - 1; x++)
						{
							map[y + 1][x] = map[y][x];
						}
					}
					for (int x = 1; x < WEIGHT - 1; x++)
						map[0][x] = '.';
				}
			}
		}
	}
	score += times * 10;
}

void Tetris::uploadGraph()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if(graph[currentGraph][i][j] != ' ' && (i + currentY) >= 0)
				map[i + currentY][j + currentX] = graph[currentGraph][i][j];
		}
	}
}

void Tetris::clearCurrentGraph()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (graph[currentGraph][i][j] != ' ' && (i + currentY) >= 0)
				map[i + currentY][j + currentX] = '.';
		}
	}
}

void Tetris::checkGameOver(int y)
{
	for (int j = 1; j < WEIGHT - 1; j++)
	{
		if (currentY + y < 0)
		{
			GameOver = 1;
		}
	}
}