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

void coutTime(int sot) {
    int eot = time(NULL);
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

                ghost_massiv[i][j] = 1;
                cout << "  ";
            }
            else if (end == TRUE && arr[i][j] == BOMB) {
                SetColor(Red, Black);
                cout << char(6) << " ";
                SetColor(White, Black);
            }
            else if (ghost_massiv[i][j] == SECRET) {

                cout << "* ";
            }
            else if (ghost_massiv[i][j] == FLAG) {
                SetColor(Blue, Black);
                cout << char(20) << " ";
                SetColor(White, Black);
            }
            else {

                cout << arr[i][j] << " ";
            }
        }
        cout << "|";
        cout << endl;
    }
    cout << mods[mode].strip;

    cout << "\n\nYou still have " << mods[mode].countBombs - countFlags << " flags!!!";


}