/*
Taskkill /F /IM "copy.exe" /T
g++ E:\CPP\Practice\copy.cpp -o E:\CPP\Practice\copy.exe
E:\CPP\Practice\copy.exe
*/

#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

/*defining Node and typedef-ing it*/
struct Node
{
	int dataX = -1;
	int dataY = -1;
	Node* link = NULL;
};	typedef struct Node Node;
/*defined Node and typedef-ed it*/

void visual(int* snakeX, int* snakeY, int* fruitX, int* fruitY, int* score); //print visual elements
void input(int* dir, int* gameSpeed); //takes input and direction
void kmove(int* snakeX, int* snakeY, int* dir); //moves the snake on the direction
void makeFruit(int* fruitX, int* fruitY); //makes fruit randomely
void eatFruitUpdatetScore(int* snakeX, int* snakeY, int* fruitX, int* fruitY, int *score);//id snake ate fruit, update score and snake size
void didGameEnd(int* snakeX, int* snakeY, bool* didEnd); //if the snake hit the border
void createFirstSnakeBit(int snakeX, int snakeY); //a snakeBit is a single unit of snake body
void addSnakeBitAtTail(int snakeX, int snakeY); //update snakes head unit. Tail undicates tail of the node
void deleteSnakeBitAtHead(); //last body unit removed. head means node's head
bool isInSnake(int x, int y); //if snake body vontains the unit x,y , return true
bool doesSnakeCollide(int x, int y); //if snake collides with itself, return true

/*-------------global variables-------------------*/
int snakeSize = 0, nodeSize = 1;
Node *head = new Node, *tail; //node variables
/*-------------global variablrs-------------------*/


int main()
{
	bool didEnd = 0;
	int gameSpeed, score = 0, snakeX = 14, snakeY = 10, dir = 0, fruitX = 3, fruitY = 3;
	cout<< "Enter game speed(1-10): ";
	cin>> gameSpeed;

    gameSpeed = 11 - gameSpeed;
    gameSpeed *= 10;

	while(didEnd == false)
	{
		visual(&snakeX, &snakeY, &fruitX, &fruitY, &score);
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

void visual(int* snakeX, int* snakeY, int* fruitX, int* FruitY, int* score) //snakX is a pointer
{
	system("cls");

	for (int i = 0; i < 20; ++i) //row
	{
		for (int j = 0; j < 30; ++j) //columm
		{
			if ((j == 0 || j ==29) || (i == 0 || i == 19))
			{
				cout<<"#";//prints the border
			}
			else if(j == *fruitX && i == *FruitY)
            {
                cout<<'+'; //prinys the fruit represented by '+'
            }
			else if (j == *snakeX && i == *snakeY)//*snakeX is the data pointed by pointer snakeX
			{
				cout<<'0'; //snake head
			}
			else if (isInSnake(j, i) == true)
			{
				cout<<"O"; //snake body
			}
			else cout<<" "; //empty space in house
		}
		cout<<'\n'; //next row
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
			case ' ' : system("pause"); break;/*"press 'space'(ASCII 32) to pause"*/
			default: break;
		}
	}
	Sleep(*gameSpeed); //gamespeed is a pointer in the function. so have to get the ifo from the pointer
}

void kmove(int* snakeX, int* snakeY, int* dir)
{
	switch(*dir)
	{
		case 1 : *snakeY = *snakeY-1; if(*snakeY == 1 || *snakeY ==2 || *snakeY == 17 || *snakeY ==18){Sleep(100);} /* it becomes hard at end of Y axis on the box*/ break;
		case 2 : *snakeX = *snakeX-1 ; break;
		case 3 : *snakeY = *snakeY+1; if(*snakeY == 1 || *snakeY ==2 || *snakeY == 17 || *snakeY ==18){Sleep(100);} /* it becomes hard at end of Y axis on the box*/ break;
		case 4 : *snakeX = *snakeX+1 ; break;
		default: break;
	}
	if (snakeSize < nodeSize)
	{
		createFirstSnakeBit(*snakeX, *snakeY);
		snakeSize++;
	}
	else if (snakeSize == nodeSize)
	{
		addSnakeBitAtTail(*snakeX, *snakeY);
		deleteSnakeBitAtHead();
	}
	else if (snakeSize > nodeSize)
	{
		addSnakeBitAtTail(*snakeX, *snakeY);
		nodeSize++;
	}
}

void didGameEnd(int* snakeX, int* snakeY, bool* didEnd)
{
	if ((*snakeX == 0 || *snakeX ==29) || (*snakeY == 0 || *snakeY == 19))
	{
		*didEnd = 1;
	}
	else if (doesSnakeCollide(*snakeX, *snakeY) == true)
	{
		*didEnd = 1;
	}
}

void eatFruitUpdatetScore(int* snakeX, int* snakeY, int* fruitX, int* fruitY, int *score)
{
	if ((*snakeY == *fruitY) && (*snakeX == *fruitX)) //snake ate the fruit
	{
		*score = *score + 10;
		snakeSize++; //snake size increase by one
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

void createFirstSnakeBit(int snakeX, int snakeY)
{
	head = new Node; /*setting node1. head will remain unchanged fo rest of time*/
	tail = head;
	head->dataX = snakeX; //defaultSnakeX;
	head->dataY = snakeY; //defaultSnakeY;
}

void addSnakeBitAtTail(int snakeX, int snakeY)
{
	Node* tempNode;
	tempNode = new Node;
	tempNode->dataX = snakeX;
	tempNode->dataY = snakeY;
	tail->link = tempNode; /*tail or the last node now points to the newNode i.e tempNode. tail is no longer last node, rather 2nd last*/
	tail = tempNode; /*now tail is updated. the last node is tail again*/
}

void deleteSnakeBitAtHead()
{
	Node* disposableHead = head;
	head = head->link;
	delete disposableHead; disposableHead = NULL; //does it free memory?
}

bool isInSnake(int x, int y)
{
	Node* disposableHead = head;
	while(disposableHead != NULL)
	{
		if (disposableHead->dataX == x && disposableHead->dataY == y)
		{
			return true;
		}
		disposableHead = disposableHead->link;
	}
	return false;
}

bool doesSnakeCollide(int x, int y)
{
	int i = 3;
	Node* disposableHead = head;
	while(i < snakeSize && disposableHead != NULL)
	{
		if (disposableHead->dataX == x && disposableHead->dataY == y)
		{
			return true;
		}
		disposableHead = disposableHead->link;
		i++;
	}
	return false;
}