#include "Tetris.h"

#include <iostream>
#include <conio.h>
#include <ctime>

using namespace std;

int main(void)
{
	Tetris Tetris;

	long currentTime = 0;
	long showMapTime = 0;
	long graphDownTime = 0;

	const int SHOWPERIOD = 50;
	const int DOWNPERIOD = 300;		//Game speed

	for (;;)
	{
		currentTime = clock();
		char c;
		//Read input
		char input = ';';
		if (_kbhit())
		{
			input = _getch();
			switch (input)
			{
				//GO right
				case 'd':
					if (!Tetris.checkCollision('r'))
					{
						Tetris.clearCurrentGraph();
						Tetris.graphMove('r');
					}
					break;
				//Go left
				case 'a':
					if (!Tetris.checkCollision('l'))
					{
						Tetris.clearCurrentGraph();
						Tetris.graphMove('l');
					}
					break;
				//Go down
				case 's':
					if (!Tetris.checkCollision('d'))
					{
						Tetris.clearCurrentGraph();
						Tetris.graphMove('d');
					}
					break;
				//Rotate
				case ' ':
					Tetris.graphRotate();
					break;
				default:
					break;
			}
			Tetris.uploadGraph();
		}

		//Show map
		if(currentTime >= showMapTime or currentTime < showMapTime - 10000)
		{
			system("cls");
			Tetris.showMap();
			showMapTime = currentTime + SHOWPERIOD;
		}

		//Graph down
		if ((currentTime >= graphDownTime or currentTime < graphDownTime - 10000) and !Tetris.checkCollision('d'))
		{
			Tetris.clearCurrentGraph();
			Tetris.graphMove('d');
			Tetris.uploadGraph();
			graphDownTime = currentTime + DOWNPERIOD;
		}
		if (Tetris.GameOver)
		{
			break;
		}
	}
	
	return 0;
}
