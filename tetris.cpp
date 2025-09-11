/*
 * Project: Console Tetris (C++)
 * Description: A simple Tetris game implemented in C++ for Windows console.
 * Author: AmirAbas AdibAnsari
 * License: MIT
 */


#include <iostream>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <unistd.h>
#include <stdio.h>
#include <bits/stdc++.h>
using namespace std;

const int width = 15; // Width of the playing board
const int height = 10; // height of the playing board

int legoHeight[4]; // height of each random logo
int legoWidth[4]; // width of each random logo
int shadowHeight[4]; // height of each random logos shadow
int shadowWidth[4]; // width of each random logos sahdow

char lego; 
const char emptyf = ' ';
const char legoShadow = ' ';
char board[width][height];

int point = 0;
int timeSleep;
int errorShadow = 1;// a temp variable for shaowing sahdow
time_t starting, ending;// for count time start and end of a game

void setCursorPosition(short int x, short int y)
{
    // This function is used to clear the terminal in a better way
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = {x, y};
    SetConsoleCursorPosition(output, pos);
}

void emptyboard()
{
    // This function is used to empty board in start of game
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            board[i][j] = emptyf;
        }
    }
}


bool canGoDownShadow()
{
    // This function checks if the shadow can go down
    for (int i = 0; i < 4; i++)
    {
        int temp = -1;
        if (shadowWidth[i] == width - 1)
        {
            return false;
        }
        if (board[shadowWidth[i] + 1][shadowHeight[i]] != emptyf)
        {
            temp = 0;
            int nextWidthShadow = shadowWidth[i] + 1;
            int nextHeightShadow = shadowHeight[i];
            if (nextWidthShadow == shadowWidth[0] && nextHeightShadow == shadowHeight[0])
                ++temp;
            else if (nextWidthShadow == shadowWidth[1] && nextHeightShadow == shadowHeight[1])
                ++temp;
            else if (nextWidthShadow == shadowWidth[2] && nextHeightShadow == shadowHeight[2])
                ++temp;
            else if (nextWidthShadow == shadowWidth[3] && nextHeightShadow == shadowHeight[3])
                ++temp;
        }
        if (temp == 0)
        {
            return false;
        }
    }
    return true;
}

void shadow()
{
    // This function specifies the final location of the shadow
    for (int i = 0; i < 4; i++)
    {
        shadowWidth[i] = legoWidth[i];
        shadowHeight[i] = legoHeight[i];
    }
    while (canGoDownShadow() == true)
    {
        for (int i = 0; i < 4; i++)
        {
            ++shadowWidth[i];
        }
    }
    for (int i = 0; i < 4; i++)
    {
        board[shadowWidth[i]][shadowHeight[i]] = legoShadow;
    }
}


inline void showboard(int time)
{
    // This function prints everything you see
    setCursorPosition(0, 0);
    HANDLE console_color;
    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
    for (int i = 0; i < width; i++)
    {
        cout << "|";
        for (int j = 0; j < height; j++)
        {
            if (board[i][j] == '0')
            {
                SetConsoleTextAttribute(console_color, 1);
                cout << board[i][j];
            }
            else if (board[i][j] == '1')
            {
                SetConsoleTextAttribute(console_color, 2);
                cout << board[i][j];
            }
            else if (board[i][j] == '2')
            {
                SetConsoleTextAttribute(console_color, 3);
                cout << board[i][j];
            }
            else if (board[i][j] == '3')
            {
                SetConsoleTextAttribute(console_color, 4);
                cout << board[i][j];
            }
            else if (board[i][j] == '4')
            {
                SetConsoleTextAttribute(console_color, 5);
                cout << board[i][j];
            }
            else if (board[i][j] == '5')
            {
                SetConsoleTextAttribute(console_color, 6);
                cout << board[i][j];
            }
            else if (board[i][j] == '6')
            {
                SetConsoleTextAttribute(console_color, 14);
                cout << board[i][j];
            }
            else if (board[i][j] == '7')
            {
                SetConsoleTextAttribute(console_color, 13);
                cout << board[i][j];
            }
            else if (board[i][j] == '8')
            {
                SetConsoleTextAttribute(console_color, 10);
                cout << board[i][j];
            }
            else if (board[i][j] == '9')
            {
                SetConsoleTextAttribute(console_color, 11);
                cout << board[i][j];
            }
            else if ((i == shadowWidth[0] && j == shadowHeight[0]) || (i == shadowWidth[1] && j == shadowHeight[1]) ||
                     (i == shadowWidth[2] && j == shadowHeight[2]) || (i == shadowWidth[3] && j == shadowHeight[3]) )
            {
                if( errorShadow == 1)
                {
                    SetConsoleTextAttribute(console_color, 240);
                    cout << board[i][j];
                }
                else
                {
                    SetConsoleTextAttribute(console_color, 15);
                    cout << board[i][j];
                }
            }
            else if (board[i][j] == emptyf)
            {
                SetConsoleTextAttribute(console_color, 15);
                cout << board[i][j];
            }
        }
        SetConsoleTextAttribute(console_color, 15);
        cout << "|";
        cout << endl;
    }
    cout << endl
         << "Press (x) to move END " << endl
         << "Press (s) to move FAST" << endl
         << "Press (d) to move RIGHT" << endl
         << "Press (a) to move LEFT" << endl
         << "Press (e) to E-ROTATE" << endl
         << "Press (q) to Q-ROTATE" << endl;

    cout << endl
         << endl
         << "Your point is : " << point;
    Sleep(time);
}

void chooseLego()
{
    // This function specifies what character each shape will be made with
    srand(time(0));
    int randomNumberCharacter = rand() % (10) + 48;
    char character = randomNumberCharacter;
    lego = character;
}

void makeNewShape()
{
    // This function creates a new shape in board with the already created character
    chooseLego();
    for (int i = 3; i >= 0; i--)
    {
        if (board[legoWidth[i]][legoHeight[i]] == emptyf)
        {
            board[legoWidth[i]][legoHeight[i]] = lego;
        }
    }
    point += 1;
}


bool canGoDown()
{
    // This function checks if our shape can be go down
    for (int i = 0; i < 4; i++)
    {
        int temp = -1;
        if (legoWidth[i] == width - 1)
        {
            return false;
        }
        if (board[legoWidth[i] + 1][legoHeight[i]] != emptyf)
        {
            temp = 0;
            int nextWidthLego = legoWidth[i] + 1;
            int nextHeightLego = legoHeight[i];
            if (nextWidthLego == legoWidth[0] && nextHeightLego == legoHeight[0])
                ++temp;
            else if (nextWidthLego == legoWidth[1] && nextHeightLego == legoHeight[1])
                ++temp;
            else if (nextWidthLego == legoWidth[2] && nextHeightLego == legoHeight[2])
                ++temp;
            else if (nextWidthLego == legoWidth[3] && nextHeightLego == legoHeight[3])
                ++temp;
        }
        if (temp == 0)
        {
            return false;
        }
    }
    return true;
}

bool canGoLeft()
{
    // This function checks if our shape can be go left
    for (int i = 0; i < 4; i++)
    {
        int temp = -1;
        if (legoHeight[i] == 0)
        {
            return false;
        }
        if (board[legoWidth[i]][legoHeight[i] - 1] != emptyf)
        {
            temp = 0;
            int leftWidthLego = legoWidth[i];
            int leftHeightLego = legoHeight[i] - 1;
            if (leftWidthLego == legoWidth[0] && leftHeightLego == legoHeight[0])
                ++temp;
            else if (leftWidthLego == legoWidth[1] && leftHeightLego == legoHeight[1])
                ++temp;
            else if (leftWidthLego == legoWidth[2] && leftHeightLego == legoHeight[2])
                ++temp;
            else if (leftWidthLego == legoWidth[3] && leftHeightLego == legoHeight[3])
                ++temp;
        }
        if (temp == 0)
        {
            return false;
        }
    }
    return true;
}

bool canGoRight()
{
    // This function checks if our shape can be go right
    for (int i = 0; i < 4; i++)
    {
        int temp = -1;
        if (legoHeight[i] == height - 1)
        {
            return false;
        }
        if (board[legoWidth[i]][legoHeight[i] + 1] != emptyf)
        {
            temp = 0;
            int rightWidthLego = legoWidth[i];
            int rightHeightlego = legoHeight[i] + 1;
            if (rightWidthLego == legoWidth[0] && rightHeightlego == legoHeight[0])
                ++temp;
            else if (rightWidthLego == legoWidth[1] && rightHeightlego == legoHeight[1])
                ++temp;
            else if (rightWidthLego == legoWidth[2] && rightHeightlego == legoHeight[2])
                ++temp;
            else if (rightWidthLego == legoWidth[3] && rightHeightlego == legoHeight[3])
                ++temp;
        }
        if (temp == 0)
        {
            return false;
        }
    }
    return true;
}


void goDown()
{
    // This function moves our shape down
    for (int i = 0; i < 4; i++)
    {
        board[legoWidth[i]][legoHeight[i]] = emptyf;
    }
    for (int i = 0; i < 4; i++)
    {
        board[legoWidth[i] + 1][legoHeight[i]] = lego;
    }
    for (int i = 0; i <= 3; i++)
    {
        legoWidth[i]++;
    }
}

void goRight(char character)
{
    // This function moves our shape right
    if (character == 'd')
    {
        for (int i = 0; i <= 3; i++)
        {
            board[legoWidth[i]][legoHeight[i]] = emptyf;
        }
        for (int i = 0; i <= 3; i++)
        {
            board[legoWidth[i]][legoHeight[i] + 1] = lego;
        }
        for (int i = 0; i <= 3; i++)
        {
            legoHeight[i]++;
        }
    }
}

void goLeft(char character)
{
    // This function moves our shape left
    if (character == 'a')
    {
        for (int i = 0; i <= 3; i++)
        {
            board[legoWidth[i]][legoHeight[i]] = emptyf;
        }
        for (int i = 0; i <= 3; i++)
        {
            board[legoWidth[i]][legoHeight[i] - 1] = lego;
        }
        for (int i = 0; i <= 3; i++)
        {
            legoHeight[i]--;
        }
    }
}

void goEnd()
{
    // This function takes our shape to the lowest possible state in an instant
    while (canGoDown() == true)
    {
        goDown();
    }
    Beep(200, 300);
    if (legoWidth[2] < 3)
    {
        point += 20;
    }
    else if (legoWidth[2] < width / 2)
    {
        point += 15;
    }
    else
    {
        point += 10;
    }
}

void goFast()
{
    // This function speeds up our shape
    for (int i = 1; i <= 3; i++)
    {
        if (canGoDown() == true)
        {
            goDown();
            showboard(timeSleep - 150);
        }
        else
        {
            break;
        }
    }
    point += 15;
}

void eRotate()
{
    // This function rotates our shape clockwise
    int w[4], h[4];
    w[0] = legoWidth[0];
    w[1] = legoWidth[1];
    w[2] = legoWidth[2];
    w[3] = legoWidth[3];
    h[0] = legoHeight[0];
    h[2] = legoHeight[2];
    h[1] = legoHeight[1];
    h[3] = legoHeight[3];

    for (int i = 0; i < 4; i++)
    {
        board[w[i]][h[i]] = emptyf;
    }

    int temp = 1;

    for (int i = 0; i < 4; i++)
    {
        if (i != 2)
        {
            legoHeight[i] = -(w[i] - legoWidth[2]) + legoHeight[2];
            legoWidth[i] = (h[i] - legoHeight[2] + legoWidth[2]);
            if (legoHeight[i] >= height || legoHeight[i] < 0 || legoWidth[i] >= width || legoWidth[i] < 0 ||
                board[legoWidth[i]][legoHeight[i]] != emptyf)
            {
                temp = 0;
                for (int j = 0; j < 4; j++)
                {
                    legoWidth[j] = w[j];
                    legoHeight[j] = h[j];
                    board[legoWidth[j]][legoHeight[j]] = lego;
                }
                break;
            }
        }
    }

    if (temp == 1)
    {
        for (int i = 0; i < 4; i++)
        {
            board[legoWidth[i]][legoHeight[i]] = lego;
        }
        Beep(1000, 300);
    }
}

void qRotate()
{
    // This function rotates our shape counterclockwise
    int w[4], h[4];
    w[0] = legoWidth[0];
    w[1] = legoWidth[1];
    w[2] = legoWidth[2];
    w[3] = legoWidth[3];
    h[0] = legoHeight[0];
    h[2] = legoHeight[2];
    h[1] = legoHeight[1];
    h[3] = legoHeight[3];

    for (int i = 0; i < 4; i++)
    {
        board[w[i]][h[i]] = emptyf;
    }

    int temp = 1;

    for (int i = 0; i < 4; i++)
    {
        if (i != 2)
        {
            legoHeight[i] = (w[i] - legoWidth[2]) + legoHeight[2];
            legoWidth[i] = -(h[i] - legoHeight[2]) + legoWidth[2];
            if (legoHeight[i] >= height || legoHeight[i] < 0 || legoWidth[i] >= width || legoWidth[i] < 0 ||
                board[legoWidth[i]][legoHeight[i]] != emptyf)
            {
                temp = 0;
                for (int j = 0; j < 4; j++)
                {
                    legoWidth[j] = w[j];
                    legoHeight[j] = h[j];
                    board[legoWidth[j]][legoHeight[j]] = lego;
                }
                break;
            }
        }
    }

    if (temp == 1)
    {
        for (int i = 0; i < 4; i++)
        {
            board[legoWidth[i]][legoHeight[i]] = lego;
        }
        Beep(1000, 300);
    }
}


void changeRow(int numberWidth )
{
    // This function removes the filled rows
    for (int i = 0; i < height; i++)
    {
        board[numberWidth][i] = emptyf;
    }
    for (int i = numberWidth; i > 0; i--)
    {
        for (int j = height - 1; j >= 0; j--)
        {
            swap(board[i][j], board[i - 1][j]);
        }
    }
    point += 50;
}

void sendRow()
{
    // This function checks whether a row is filled 
    for (int i = width - 1; i >= 0; i--)
    {
        int temp = 0;
        for (int j = 0; j < height; j++)
        {
            if (board[i][j] == emptyf)
            {
                temp = 1;
                break;
            }
        }
        if (temp == 0)
        {
            changeRow(i);
        }
    }
}


int firstPosition()
{
    // This function randomly returns an initial height for our shape
    srand(time(0));
    int randomHeight = rand() % (height - 3) + 2;
    return randomHeight;
}

void typeShape(int numberShape)
{
    // This function determines the coordinates of our shape according to the input number
    int originHeight = firstPosition();
    if (numberShape == 1)
    {
        legoHeight[0] = originHeight;
        legoWidth[0] = 0;

        legoHeight[1] = originHeight - 1;
        legoWidth[1] = 0;

        legoHeight[2] = originHeight - 1;
        legoWidth[2] = 1;

        legoHeight[3] = originHeight;
        legoWidth[3] = 1;
    }
    else if (numberShape == 2)
    {
        legoHeight[0] = originHeight + 1;
        legoWidth[0] = 0;

        legoHeight[1] = originHeight;
        legoWidth[1] = 0;

        legoHeight[2] = originHeight - 1;
        legoWidth[2] = 0;

        legoHeight[3] = originHeight - 2;
        legoWidth[3] = 0;
    }
    else if (numberShape == 3)
    {
        legoHeight[0] = originHeight;
        legoWidth[0] = 0;

        legoHeight[1] = originHeight - 1;
        legoWidth[1] = 1;

        legoHeight[2] = originHeight;
        legoWidth[2] = 1;

        legoHeight[3] = originHeight + 1;
        legoWidth[3] = 1;
    }
    else if (numberShape == 4)
    {
        legoHeight[0] = originHeight;
        legoWidth[0] = 0;

        legoHeight[1] = originHeight;
        legoWidth[1] = 1;

        legoHeight[2] = originHeight;
        legoWidth[2] = 2;

        legoHeight[3] = originHeight + 1;
        legoWidth[3] = 2;
    }
    else if (numberShape == 5)
    {
        legoHeight[0] = originHeight;
        legoWidth[0] = 0;

        legoHeight[1] = originHeight;
        legoWidth[1] = 1;

        legoHeight[2] = originHeight + 1;
        legoWidth[2] = 1;

        legoHeight[3] = originHeight + 1;
        legoWidth[3] = 2;
    }
    else if (numberShape == 6)
    {
        legoHeight[0] = originHeight;
        legoWidth[0] = 0;

        legoHeight[1] = originHeight;
        legoWidth[1] = 1;

        legoHeight[2] = originHeight;
        legoWidth[2] = 2;

        legoHeight[3] = originHeight - 1;
        legoWidth[3] = 2;
    }
    else if (numberShape == 7)
    {
        legoHeight[0] = originHeight;
        legoWidth[0] = 0;

        legoHeight[1] = originHeight;
        legoWidth[1] = 1;

        legoHeight[2] = originHeight - 1;
        legoWidth[2] = 1;

        legoHeight[3] = originHeight - 1;
        legoWidth[3] = 2;
    }
}

int getRandom()
{
    // This function returns a random number as the shape number
    int number;
    srand(time(0));
    number = rand() % 7 + 1;
    return number;
}

inline void MotionsShape()
{
    // This function defines all the movements of our shape as long as it can go
    char arrow;
    int numberShape = getRandom();
    typeShape(numberShape);
    makeNewShape();
    showboard(timeSleep);
    while (canGoDown() == true)
    {
        int temp = 0;
        if (kbhit())
        {
            arrow = getch();
            if (canGoRight() == true)
            {
                goRight(arrow);
                showboard(0);
            }
            if (canGoLeft() == true)
            {
                goLeft(arrow);
                showboard(0);
            }
            if (arrow == 's')
            {
                goFast();
                temp = 1;
            }
            if (arrow == 'e' && numberShape != 1)
            {
                eRotate();
                showboard(timeSleep);
            }
            if (arrow == 'q' && numberShape != 1)
            {
                qRotate();
                showboard(timeSleep);
            }
            if (arrow == 'x')
            {
                goEnd();
                showboard(timeSleep);
                break;
            }
        }
        if (temp == 0)
        {
            shadow();
            goDown();
            showboard(timeSleep);
        }
    }
    sendRow();
}


bool canPlay()
{
    // This function checks whether the game is finished or not
    for (int i = 2; i <= height - 2; i++)
    {
        if (board[0][i] != emptyf)
        {
            return false;
        }
    }
    return true;
}

void beautifulDelete()
{
    // This function deletes the screen beautifully when the game is finished
    Beep(1500, 900);
    for (int i = width - 1; i >= 0; i--)
    {
        for (int j = 0; j < height; j++)
        {
            board[i][j] = emptyf;
        }
        showboard(150);
    }
}

void yourLevel()
{
    // This function determines the level of the game according to the user's opinion
    int levelNumber;
    cout << "Enter your NumberLevel :" << endl;
    cout << "1.Easy" << endl
         << "2.Medium" << endl
         << "3.Hard" << endl;
    cin >> levelNumber;
    if (levelNumber == 1)
    {
        timeSleep = 500;
        point += 10;
    }
    else if (levelNumber == 2)
    {
        timeSleep = 350;
        point += 20;
    }
    else if (levelNumber == 3)
    {
        timeSleep = 200;
        point += 40;
    }
    else
    {
        cout << "Error , please Enter a valid Number " << endl;
        yourLevel();
    }
    system("cls");
    cout << endl
         << "Press (x) to move END " << endl
         << "Press (s) to move FAST" << endl
         << "Press (d) to move RIGHT" << endl
         << "Press (a) to move LEFT" << endl
         << "Press (e) to E-Rotete" << endl
         << "Press (q) to Q-Rotate" << endl
         << endl;
}

void loading()
{
    // This function beautifully displays "loading" at the beginning of the game
    system("cls");
    char load[13];
    for (int i = 0; i < 13; i++)
    {
        load[i] = ' ';
    }
    cout << endl
         << "LOADING TETRIS ..." << endl
         << endl;
    HANDLE console_color;
    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console_color, 240);
    for (int i = 0; i < 13; i++)
    {
        if (i == 0)
        {
            Sleep(1000);
        }
        else if (i == 2)
            Sleep(500);
        else if (i == 5)
            Sleep(400);
        else if (i == 10)
            Sleep(800);
        cout << load[i];
    }
    Sleep(800);
    SetConsoleTextAttribute(console_color, 15);
    system("cls");
}

void countPointTime( int timeGame)
{
    // This function adds to your point according to the start and end time of the game
    if( timeGame < 30)
    {
        point += 10;
    }
    else if( timeGame < 60)
    {
        point += 20;
    }
    else if( timeGame < 90)
    {
        point += 30;
    }
    else if( timeGame < 120)
    {
        point += 40;
    }
    else if( timeGame >= 120)
    {
        point += 50;
    }
}


void tetrisGame()
{
    loading();
    emptyboard();
    system("cls");
    yourLevel();
    cout << "Press (1) to Start TETRIS " << endl;
    char start;
    cin >> start;
    system("cls");
    while (start == '1')
    {
        point = 0;
        time(&starting);
        while (canPlay() == true)
        {
            MotionsShape();
            sendRow();
        }
        time(&ending);
        errorShadow = 0;
        beautifulDelete();
        system("cls");
        int timeGame = difftime(ending , starting);
        countPointTime( timeGame );
        cout << endl
             << endl;
        cout << "Your final point is : " << point << endl
             << endl;
        cout << "if you want to PLAY again , Press (1) " << endl
             << endl;
        cout << "else if you want to EXIT , Press (0) " << endl;
        cin >> start;
        system("cls");
    }
    system("cls");
    cout << endl
         << endl
         << "TETRIS is over ";
}

int main()
{
    // start tetris and enjoy!!!!
    tetrisGame();
    return 0;
}