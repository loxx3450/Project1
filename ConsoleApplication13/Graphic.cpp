#include <iostream>
#include <Windows.h>
#include "common.h"
using namespace std;

enum ConsoleColor
{
    Black, Blue, Green, Cyan, Red, Magenta, Brown, LightGray, DarkGray,
    Lightblue, LightGreen, Lightcyan, lightRed, LightMagenta, Yellow, White
};

void SetColor(ConsoleColor text, ConsoleColor background)
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}

void coutTime(int sot, int eot) {
    int time = eot - sot;
    if (time - 60 >= 0) {
        int i{ 0 };
        while (time - 60 >= 0) {
            time -= 60;
            i++;
        }
        cout << "\n\nTime: " << i << " minute " << time % 60 << " seconds!\n";
    }
    else {
        cout << "\n\nTime: " << eot - sot << " seconds!\n";
    }
}

void coutNumber(int value) {
    switch (value) {
        case 1:

            SetColor(Blue, Black);
            cout << value << " ";
            SetColor(White, Black);
            break;

        case 2:

            SetColor(Green, Black);
            cout << value << " ";
            SetColor(White, Black);
            break;

        case 3:

            SetColor(Red, Black);
            cout << value << " ";
            SetColor(White, Black);
            break;

        case 4:

            SetColor(Lightblue, Black);
            cout << value << " ";
            SetColor(White, Black);
            break;

        case 5:

            SetColor(Magenta, Black);
            cout << value << " ";
            SetColor(White, Black);
            break;

        case 6:

            SetColor(Cyan, Black);
            cout << value << " ";
            SetColor(White, Black);
            break;

    }
}

void showArr(int** arr, Mods* mods, const int mode, int** ghost_massiv, const int count, const int countFlags, const int end = 0) {

    system("cls");

    cout << mods[mode].strip << "\t\t\t\t";

    SetColor(Green, Black);
    cout << "SPACE - flag on/off \t ENTER - shoot\n";
    SetColor(White, Black);

    for (int i{ 1 }; i <= count; i++) {

        cout << "|";
        for (int j{ 1 }; j <= count; j++) {

            if (arr[i][j] == EMPTY) {

                cout << "  ";
            }
            else if (end == TRUE && arr[i][j] == BOMB) {

                SetColor(lightRed, Black);
                cout << char(BOMBEMOJI) << " ";
                SetColor(White, Black);
            }
            else if (ghost_massiv[i][j] == SECRET) {

                cout << "* ";
            }
            else if (ghost_massiv[i][j] == FLAG) {

                SetColor(Brown, Black);
                cout << char(FLAGEMOJI) << " ";
                SetColor(White, Black);
            }
            else {

                coutNumber(arr[i][j]);
            }
        }
        cout << "|";
        cout << endl;
    }
    cout << mods[mode].strip;

    cout << "\n\nYou still have " << mods[mode].countBombs - countFlags << " flags!!!";


}