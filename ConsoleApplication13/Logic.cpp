#include <Windows.h>
#include <conio.h>
#include <ctime>
#include "Logic.h"
#include "common.h"
#include "Graphic.h"
using namespace std;

enum Buttons
{
    rright = 77,
    up = 72,
    down = 80,
    lleft = 75,
    shoot = 13,
    flag = 32
};

void GotoXY(int X, int Y)
{
    HANDLE  hConsole;
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = { X, Y };
    SetConsoleCursorPosition(hStdOut, coord);
}



bool Shoot(int** arr, int** ghost_massiv, int x, int y) {

    x--;
    y--;

    if (x != 0) {

        x /= 2;
    }
    if (arr[y + 1][x + 1] == BOMB) {

        return 0;
    }
    ghost_massiv[y + 1][x + 1] = VERIFY;

    return 1;
}

void Flag(int** ghost_massiv, int x, int y, int& countFlags, int countBombs) {

    x--;
    y--;

    if (x != 0) {

        x /= 2;
    }
    if (ghost_massiv[y + 1][x + 1] == FLAG) {
        ghost_massiv[y + 1][x + 1] = SECRET;
        countFlags--;
    }
    else if (countFlags < countBombs) {
        ghost_massiv[y + 1][x + 1] = FLAG;
        countFlags++;
    }
}

int ifWin(int** ghost_massiv, const int count, const int countBombs) {

    int value{ 0 };

    for (int i{ 1 }; i <= count; i++) {

        for (int j{ 1 }; j <= count; j++) {

            if (ghost_massiv[i][j] != VERIFY) {

                value++;
            }
        }
    }
    if (value == countBombs) {

        return 1;
    }

    return 0;
}

void deleteArrs(int** arr, int** ghost_massiv, const int count) {
    for (int i{}; i < count + 2; i++) {

        delete[] arr[i];
        delete[] ghost_massiv[i];
    }

    delete[] arr;
    delete[] ghost_massiv;
}

bool play(int** arr, int** ghost_massiv, Mods* mods, const int mode, const int count, const int countBombs) {

    int move{}, x{ 1 }, y{ 1 }, countFlags{ 0 }, sot, eot;

    showArr(arr, mods, mode, ghost_massiv, count, countFlags);

    sot = time(NULL);

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

        case shoot:

            if (!Shoot(arr, ghost_massiv, x, y)) {

                showArr(arr, mods, mode, ghost_massiv, count, countFlags, 1);

                deleteArrs(arr, ghost_massiv, count);

                coutTime(sot);

                return 0;
            }
            showArr(arr, mods, mode, ghost_massiv, count, countFlags);

            break;

        case flag:

            Flag(ghost_massiv, x, y, countFlags, countBombs);

            showArr(arr, mods, mode, ghost_massiv, count, countFlags);

            break;
        }
        if (ifWin(ghost_massiv, count, countBombs)) {

            showArr(arr, mods, mode, ghost_massiv, count, countFlags, 1);

            deleteArrs(arr, ghost_massiv, count);

            coutTime(sot);

            return 1;
        }

        GotoXY(x, y);
    }

}

int Choice() {
    cout << "Choose game difficulty: \n1.Easy \n2.Normal \n3.Hard \n";
    int move{}, x{ 0 }, y{ 0 };

    while (true) {
        move = _getch();
        switch (move) {
        case up:
            y--;
            break;
        case down:
            y++;
            break;
        case shoot:
            return y - 1;
            break;


        }
        GotoXY(x, y);
    }
}