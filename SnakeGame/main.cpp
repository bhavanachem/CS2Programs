#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

bool gameOver;
const int gameBoardWidth = 20;
const int gameBoardHeight = 20;
int fruitCount = 5;
int snakeHeadx, snakeHeady, userScore;
int fruitX[5], fruitY[5];
int tailX[100], tailY[100];
int tailLength;
enum eDirecton { STOP = 0, LEFT = 1, RIGHT = 2, UP = 3, DOWN = 4 };
eDirecton direction;

//------------------------program starts------------------------//

void howManyFruit() {
    cout << "How many fruit would you like (1-5): \n";
    cin >> fruitCount;
    cout << "Directions: ";
}//end of howManyFruit()

void generateNewFruit(int xCoord, int yCoord) {
    for (int fruitIndex = 0; fruitIndex < fruitCount; fruitIndex++) {
        if (fruitX[fruitIndex] == xCoord && fruitY[fruitIndex] == yCoord) {
            fruitX[fruitIndex] = rand() % gameBoardWidth;
            fruitY[fruitIndex] = rand() % gameBoardHeight;
            cout << "Found snake ate fruit" << endl;
        }
    }
}

void Setup() {
    gameOver = false;
    direction = STOP;
    snakeHeadx = gameBoardWidth / 2;
    snakeHeady = gameBoardHeight / 2;
    howManyFruit();
    for (int fruitIndex = 0; fruitIndex < fruitCount; fruitIndex++) {
        fruitX[fruitIndex] = rand() % gameBoardWidth;
        fruitY[fruitIndex] = rand() % gameBoardHeight;
    }
    userScore = 0;
    tailLength = 0; // Initialize the tail length
}

bool checkIfFruitLoc(int xCoord, int yCoord) {
    for (int fruitIndex = 0; fruitIndex < fruitCount; fruitIndex++) {
        if (fruitX[fruitIndex] == xCoord && fruitY[fruitIndex] == yCoord) {
            return true;
        }
    }
    return false;
}

void DrawBoard() {
    system("cls");
    for (int i = 0; i < gameBoardWidth + 2; i++)
        cout << "#";
    cout << endl;

    for (int boardRow = 0; boardRow < gameBoardHeight; boardRow++) {
        for (int boardCol = 0; boardCol < gameBoardWidth; boardCol++) {
            if (boardCol == 0)
                cout << "#";
            if (boardRow == snakeHeady && boardCol == snakeHeadx)
                cout << "O";
            else if (checkIfFruitLoc(boardCol, boardRow))
                cout << "F";
            else {
                bool printTail = false;
                for (int tailIndex = 0; tailIndex < tailLength; tailIndex++) {
                    if (tailX[tailIndex] == boardCol && tailY[tailIndex] == boardRow) {
                        cout << "o";
                        printTail = true;
                    }
                }
                if (!printTail)
                    cout << " ";
            }

            if (boardCol == gameBoardWidth - 1)
                cout << "#";
        }
        cout << endl;
    }

    for (int i = 0; i < gameBoardWidth + 2; i++)
        cout << "#";
    cout << endl;
    cout << "Score:" << userScore << endl;
}

void GetInput() {
    if (_kbhit()) {
        switch (_getch()) {
        case 'a':
            direction = LEFT;
            break;
        case 'd':
            direction = RIGHT;
            break;
        case 'w':
            direction = UP;
            break;
        case 's':
            direction = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }
}

void UpdateTail() {
    int currentTailX = tailX[0];
    int currentTailY = tailY[0];
    int nextTailX, nextTailY;
    tailX[0] = snakeHeadx;
    tailY[0] = snakeHeady;
    for (int tailIndex = 1; tailIndex < tailLength; tailIndex++) {
        nextTailX = tailX[tailIndex];
        nextTailY = tailY[tailIndex];
        tailX[tailIndex] = currentTailX;
        tailY[tailIndex] = currentTailY;
        currentTailX = nextTailX;
        currentTailY = nextTailY;
    }
}

void UpdateScoreAndFruit() {
    for (int fruitIndex = 0; fruitIndex < fruitCount; fruitIndex++) {
        if (snakeHeadx == fruitX[fruitIndex] && snakeHeady == fruitY[fruitIndex]) {
            userScore += 10;
            generateNewFruit(snakeHeadx, snakeHeady);
            tailLength++;
        }
    }
}

void CheckGameOver() {
    for (int tailIndex = 0; tailIndex < tailLength; tailIndex++) {
        if (tailX[tailIndex] == snakeHeadx && tailY[tailIndex] == snakeHeady) {
            gameOver = true;
        }
    }
}

void UpdateSnakeHead() {
    switch (direction) {
    case LEFT:
        snakeHeadx--;
        break;
    case RIGHT:
        snakeHeadx++;
        break;
    case UP:
        snakeHeady--;
        break;
    case DOWN:
        snakeHeady++;
        break;
    default:
        break;
    }

    if (snakeHeadx >= gameBoardWidth) snakeHeadx = 0;
    else if (snakeHeadx < 0) snakeHeadx = gameBoardWidth - 1;
    if (snakeHeady >= gameBoardHeight) snakeHeady = 0;
    else if (snakeHeady < 0) snakeHeady = gameBoardHeight - 1;
}

void UpdateGameBoard() {
    UpdateTail();
    UpdateSnakeHead();
    UpdateScoreAndFruit();
    CheckGameOver();
}

int main() {
    Setup();
    while (!gameOver) {
        DrawBoard();
        GetInput();
        UpdateGameBoard();
        Sleep(50);
    }
    return 0;
}
