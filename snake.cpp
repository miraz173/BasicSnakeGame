/*g++ E:\CPP\Practice\snake.cpp -o E:\CPP\Practice\snake.exe
  E:\CPP\Practice\snake.exe

  Taskkill /F /IM "snake.exe" /T*/

#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

void makeFruit(int* fruitX, int* fruitY);
void wall(int* snakeX, int* snakeY, int* fruitX, int* fruitY, int* score);
void input(int* dir, int* gameSpeed);
void kmove(int* snakeX, int* snakeY, int* dir);
void didGameEnd(int* snakeX, int* snakeY, int* didEnd);
void eatFruitUpdatetScore(int* snakeX, int* snakeY, int* fruitX, int* fruitY, int *score);

int main()
{
	int gameSpeed, score = 0, snakeX = 14, snakeY = 10, dir = 0, didEnd = 0, fruitX = 3, fruitY = 3;
	cout<< "Enter game speed(1-10): ";
	cin>> gameSpeed;

    gameSpeed = 11 - gameSpeed;
    gameSpeed *= 10;
	while(!didEnd)
	{
		wall(&snakeX, &snakeY, &fruitX, &fruitY, &score);
		input(&dir, &gameSpeed);
		kmove(&snakeX, &snakeY, &dir);
		eatFruitUpdatetScore(&snakeX, &snakeY, &fruitX, &fruitY, &score);
		didGameEnd(&snakeX, &snakeY, &didEnd);
	}

	system("cls");
	cout<<"Game Over.\nYour score is: "<< score <<'\n';
	system("pause");

	return 0;
}

void wall(int* snakeX, int* snakeY, int* fruitX, int* FruitY, int* score)
{
	system("cls");

	for (int i = 0; i < 20; ++i)
	{
		for (int j = 0; j < 30; ++j)
		{
			if ((j == 0 || j ==29) || (i == 0 || i == 19))
			{
				cout<<"#";
			}
			else if (j == *snakeX && i == *snakeY)
			{
				cout<<'O';
			}
			else if(j == *fruitX && i == *FruitY)
            {
                cout<<'+';
            }
			else cout<<" ";
		}
		cout<<'\n';
	}

	cout<<"Your score is: "<< *score <<'\n';
}

void input(int* dir, int* gameSpeed)
{
	if(kbhit())
	{
		switch(getch())
		{
			case 'w' : *dir = 1; break;/*"up"*/
			case 'a' : *dir = 2; break;/*"left"*/
			case 's' : *dir = 3; break;/*"down"*/
			case 'd' : *dir = 4; break;/*"right"*/
			default: break;
		}
	}
	Sleep(*gameSpeed);
}

void kmove(int* snakeX, int* snakeY, int* dir)
{
	switch(*dir)
	{
		case 1 : *snakeY = *snakeY-1; if(*snakeY == 1 || *snakeY ==2 || *snakeY == 17 || *snakeY ==18){Sleep(5);} /* it becomes hard at end of Y axis on the box*/ break;
		case 2 : *snakeX = *snakeX-1 ; break;
		case 3 : *snakeY = *snakeY+1; if(*snakeY == 1 || *snakeY ==2 || *snakeY == 17 || *snakeY ==18){Sleep(5);} /* it becomes hard at end of Y axis on the box*/ break;
		case 4 : *snakeX = *snakeX+1 ; break;
		default: break;
	}

}

void didGameEnd(int* snakeX, int* snakeY, int* didEnd)
{
	if ((*snakeX == 0 || *snakeX ==29) || (*snakeY == 0 || *snakeY == 19))
	{
		*didEnd = 1;
	}
}

void eatFruitUpdatetScore(int* snakeX, int* snakeY, int* fruitX, int* fruitY, int *score)
{
	if ((*snakeY == *fruitY) && (*snakeX == *fruitX))
	{
		*score = *score + 10;
		makeFruit(fruitX, fruitY); /*fruitX and fruitY are already pointers here. so, &fruitX will pass the "address of pointer", not "pointer"*/
	}
}

void makeFruit(int* fruitX, int* fruitY)
{
    *fruitX = rand()%29;
    *fruitY = rand()%19;

    while(*fruitX == 0)
    {
        *fruitX = rand()%29;
    }
    while(*fruitY == 0)
    {
        *fruitY = rand()%19;
    }
}
