#include <iostream>
#include <conio.h>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

using namespace std;

    const int heightBoard = 25;
    const int widthBoard = 25;
    const int playTime = 300;

    int direction; //stopped = 0; left = 1; right = 2; up = 3; down = 4;
    bool gameOver = false;
    int board[heightBoard][widthBoard]; //0 = blank, 1 = wall, 2 = fruit, 3 = snake
    int score = 0;
    int fruitX = rand() % heightBoard;
    int fruitY = rand() % widthBoard;
    int snakeX = heightBoard /2;
    int snakeY = widthBoard /2;
    int snakeSize = 1;
    int snakeSizeAux;

void SetupBoard()
{
    for (int i=0; i < heightBoard; i++)
    {
        for (int j=0; j < widthBoard; j++)
        {
            if ((i == 0) || (i == heightBoard-1) || (j == 0) || (j == heightBoard-1))
            {
                board[i][j] = 1;
            }
            else
            {
                board[i][j] = 0;
            }
        }
    }

    board[snakeX][snakeY] = 3;
    board[fruitX][fruitY] = 2;
}

void ShowBoard()
{
    system("cls");

    for (int i=0; i < heightBoard; i++)
    {
        for (int j=0; j < widthBoard; j++)
        {
            if (board[i][j] == 0)
                cout<<" ";
            else if (board[i][j] == 1)
                cout<<"#";
            else if (board[i][j] == 2)
                cout<<"@";
            else
                cout<<"*";
        }
        cout<<endl;
    }
    cout<<"Score: "<<score;
}

void ReadKeyboard()
{
    if (_kbhit())
    {
        switch (_getch())
        {
            case 'a':
                direction = 1;
            break;
            case 'd':
                direction = 2;
            break;
            case 'w':
                direction = 3;
            break;
            case 's':
                direction = 4;
            break;
            case 'x':
                gameOver = true;
            break;
        }
    }
}

void CheckColision()
{
    if (board[snakeX][snakeY] == 1)
    {
        gameOver = true;
    }
    else if (board[snakeX][snakeY] >= 3)
    {
        gameOver = true;
    }
}

void CheckEatFood()
{
    if (board[snakeX][snakeY] == 2)
    {
        fruitX = rand() % heightBoard;
        fruitY = rand() % widthBoard;

        while (board[fruitX][fruitY] == 1 || board[fruitX][fruitY] >= 3)
        {
            fruitX = rand() % heightBoard;
            fruitY = rand() % widthBoard;
        }

        board[fruitX][fruitY] = 2;
        score = score + 10;
        snakeSize = snakeSize + 1;
    }
}

void CleanSnake()
{
    for (int i=0; i < heightBoard; i++)
    {
        for (int j=0; j < widthBoard; j++)
        {
            if (i == snakeX && j == snakeY)
                continue;

            if (board[i][j] == 3)
                board[i][j] = 0;
            else if (board[i][j] == 4)
                board[i][j] = 3;
            else if (board[i][j] == 5)
                board[i][j] = 4;
            else if (board[i][j] == 6)
                board[i][j] = 5;
            else if (board[i][j] == 7)
                board[i][j] = 6;
            else if (board[i][j] == 8)
                board[i][j] = 7;
            else if (board[i][j] == 9)
                board[i][j] = 8;
            else if (board[i][j] == 10)
                board[i][j] = 9;
            else if (board[i][j] == 11)
                board[i][j] = 10;
            else if (board[i][j] == 12)
                board[i][j] = 11;
        }
    }
}

void EvaluatePositionAndGameOver()
{
    Sleep(playTime);

    switch (direction)
    {
        case 1:
            snakeY--;
            CheckEatFood();
            CheckColision();
            board[snakeX][snakeY] = snakeSize+2;
            break;
        case 2:
            snakeY++;
            CheckEatFood();
            CheckColision();
            board[snakeX][snakeY] = snakeSize+2;
            break;
        case 3:
            snakeX--;
            CheckEatFood();
            CheckColision();
            board[snakeX][snakeY] = snakeSize+2;
            break;
        case 4:
            snakeX++;
            CheckEatFood();
            CheckColision();
            board[snakeX][snakeY] = snakeSize+2;
            break;
        default:
            break;
    }

    CleanSnake();
}

void ShowBoardGameOver()
{
    system("cls");
    cout<<"Congratulations, you achiev the score: "<<score;
}

int main()
{
    SetupBoard();

    while (!gameOver)
    {
        ShowBoard();
        ReadKeyboard();
        EvaluatePositionAndGameOver();
    }

    ShowBoardGameOver();

    return 0;
}
