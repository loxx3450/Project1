﻿#include <iostream>
#include <Windows.h>
#include <conio.h>
using namespace std;


enum {
    EMPTY = 0,
    ONE = 1,
    TWO = 2,
    THREE = 3,
    FOUR = 4, 
    FIVE = 5,
    SIX = 6,
    SEVEN = 7,
    EIGHT = 8,
    BOMB = 9
};

enum {
    rright = 77,
    up = 72,
    down = 80,
    lleft = 75
};

void GotoXY(int X, int Y)
{
    HANDLE  hConsole;
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = { X, Y };
    SetConsoleCursorPosition(hStdOut, coord);
}



int** CreateArr(int count) {
    int** arr = new int* [count + 2];
    for (int i{}; i < count + 2; i++) {
        arr[i] = new int[count + 2]{0};
    }

    return arr;
}

int random(int min = 0, int max = 9) {

    return rand() % (max - min + 1) + min;
}

void GenerateBombs(int** arr, int count) {
    int x{}, y{};
    for (int i{1}; i <= count; i++) {
        x = random(1, count);
        y = random(1, count);
        cout << x << y << endl;
        if (arr[x][y] != BOMB) {
            arr[x][y] = BOMB;
        }
        else {
            i--;
            continue;
        }
        
    }
}

int CheckBombs(int** arr, int count, int x, int y) {
    int value{0};
    for (int i{ x - 1 }; i <= x + 1; i++) {
        for (int j{ y - 1 }; j <= y + 1; j++) {
            if (arr[i][j] == BOMB) {
                value++;
            }
        }
    }
    return value;
}

void BombsAround(int** arr, int count) {
    for (int i{ 1 }; i <= count; i++) {
        for (int j{ 1 }; j <= count; j++) {
            if (arr[i][j] != BOMB) {
                arr[i][j] = CheckBombs(arr, count, i, j);
            }
        }
    }
}

void GenerateArr(int** arr, int count) {
    GenerateBombs(arr, count);
    BombsAround(arr, count);
}

void showArr(int** arr, int count) {
    for (int i{1}; i <= count; i++) {
        for (int j{1}; j <= count; j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}

void play(int** arr, int count) {
    int move{}, x{ 0 }, y{ 0 };
    system("cls");
    showArr(arr, count);
    while (true) {
        move = _getch();
        switch (move) {
        case rright:
            x += 2;
            break;
        case lleft:
            x -= 2;
            break;
        case up:
            y--;
            break;
        case down:
            y++;
            break;
        }
        GotoXY(x, y);
    }

}

int main()
{
    srand(time(NULL));
    rand();

    int count{ 8 };
    
    int** arr = CreateArr(count);

    GenerateArr(arr, count);
    showArr(arr, count);

    play(arr, count);

    return 0;
}