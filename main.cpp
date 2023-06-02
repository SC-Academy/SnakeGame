#include <iostream>
#include <conio.h>     //for file console input/output
#include <cstdlib>     //for using 'system("cls");' to clear the console screen
#include <ctime>       //for converting the given time to a calendar local time and then to a character representation.
#include <chrono>      //for date and time.
#include <thread>      //for creating threads

using namespace std;

// 1
const int width = 20;
const int height = 20;

int snakeX[100], snakeY[100];  // arrays to store snake's position
int foodX, foodY;              // variables to store food's position
int snakeLength = 1;           // initial length of the snake
int score = 0;                 // initial score

enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;
//------------------------------

//2
void Setup()
{
    dir = STOP;  // initialize direction as STOP
    snakeX[0] = width / 2;  // initialize snake's position
    snakeY[0] = height / 2;
    srand(time(NULL));  // seed the random number generator
    foodX = rand() % width;  // generate initial food position
    foodY = rand() % height;
}
//-------------------------------

//3
void Draw()
{
    system("cls");  // clear the console
    for (int i = 0; i < width+2; i++)
        cout << "#";  // draw top border
    cout << endl;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)
                cout << "#";  // draw left border
            if (i == snakeY[0] && j == snakeX[0])
                cout << "O";  // draw snake's head
            else if (i == foodY && j == foodX)
                cout << "F";  // draw food
            else
            {
                bool printed = false;
                for (int k = 1; k < snakeLength; k++)
                {
                    if (snakeX[k] == j && snakeY[k] == i)
                    {
                        cout << "o";  // draw snake's body
                        printed = true;
                    }
                }
                if (!printed)
                    cout << " ";  // draw empty space
            }
            if (j == width-1)
                cout << "#";  // draw right border
        }
        cout << endl;
    }
    for (int i = 0; i < width+2; i++)
        cout << "#";  // draw bottom border
    cout << endl;
    cout << "Score: " << score << endl;  // display current score
}
//-----------------------

//4
void Input()
{
    if (_kbhit())  // check if a key has been pressed
    {
        switch (_getch())  // read the key input
        {
            case 'a': dir = LEFT;  break;
            case 'd': dir = RIGHT; break;
            case 'w': dir = UP;    break;
            case 's': dir = DOWN;  break;
        }
    }
}
//----------------------

//5 - utility
void GenerateFood()
{
    bool foodOnSnake = true;
    while (foodOnSnake)
    {
        // Generate random coordinates for the food
        foodX = rand() % width;
        foodY = rand() % height;

        // Check if food is on the snake
        foodOnSnake = false;
        for (int i = 0; i < snakeLength; i++)
        {
            if (snakeX[i] == foodX && snakeY[i] == foodY)
            {
                foodOnSnake = true;
                break;
            }
        }
    }
}
//-----------------------

//6
void Logic()
{
    // move the snake's body
    for (int i = snakeLength-1; i > 0; i--)
    {
        snakeX[i] = snakeX[i-1];
        snakeY[i] = snakeY[i-1];
    }

    // move the snake's head based on the direction
    switch (dir)
    {
        case LEFT:  snakeX[0]--; break;
        case RIGHT: snakeX[0]++; break;
        case UP:    snakeY[0]--; break;
        case DOWN:  snakeY[0]++; break;
    }

    // Check for collision with food
    //if (head.x == food.x && head.y == food.y)
    //{
        // Increase score and generate new food
        //score += 10;
        //GenerateFood();

        // Add new tail segment
        //snakeLength++;
        //tail[snakeLength].x = tail[snakeLength - 1].x;
        //tail[snakeLength].y = tail[snakeLength - 1].y;
    //}

    //
    if (snakeX[0] == foodX && snakeY[0] == foodY)
    {
       // Snake has collided with food
       score += 10;
       snakeLength++;
       GenerateFood();
    }

}
//------------------------------


bool GameOver()
{
    // Check if snake hits the wall
    if (snakeX[0] == 0 || snakeX[0] == width - 1 ||
        snakeY[0] == 0 || snakeY[0] == height - 1)
    {
        return true;
    }

    // Check if snake hits itself
    for (int i = 1; i < snakeLength; i++)
    {
        if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i])
        {
            return true;
        }
    }

    // Game is not over
    return false;
}

void Sleep(unsigned int milliseconds)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

int main()
{
    // Initialize game
    Setup();

    // Game loop
    while (true)
    {
        // Draw game board
        Draw();

        // Get user input
        Input();

        // Update game state
        Logic();

        // Check if game over
        if (GameOver())
        {
            // Print game over message and final score
            cout << "Game over! Final score: " << score << endl;
            break;
        }

        // Wait for a short time to control game speed
        Sleep(100);
    }

    // Return success
    return 0;
}

