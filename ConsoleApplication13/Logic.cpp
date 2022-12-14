#include <Windows.h>
#include <conio.h>
#include <ctime>
#include <fstream>
#include "Logic.h"
#include "common.h"
#include "Graphic.h"
#include "Creation.h"
#include "Generation.h"
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
    HANDLE  hConsole{};
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = { X, Y };
    SetConsoleCursorPosition(hStdOut, coord);
}



bool Shoot(int** arr, int** ghost_massiv, const int count, int& countFlags, int x, int y) {

    x--;
    y--;

    if (x != 0) {

        x /= 2;
    }

    if (x >= 0 && x <= count && y >= 0 && y <= count) {
        if (arr[y + 1][x + 1] == BOMB) {

            return 0;
        }
        else if (ghost_massiv[y + 1][x + 1] == FLAG) {

            countFlags--;
        }
        ghost_massiv[y + 1][x + 1] = VERIFY;
    }

    return 1;
}

void Flag(int** arr, int** ghost_massiv, const int count, int x, int y, int& countFlags, int countBombs) {

    x--;
    y--;

    if (x != 0) {

        x /= 2;
    }
    if (x >= 0 && x <= count && y >= 0 && y <= count && arr[y + 1][x + 1] != EMPTY) {
        if (ghost_massiv[y + 1][x + 1] == FLAG) {
            ghost_massiv[y + 1][x + 1] = SECRET;
            countFlags--;
        }
        else if (countFlags < countBombs) {
            ghost_massiv[y + 1][x + 1] = FLAG;
            countFlags++;
        }
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

void Lose() {
    cout << "\nYou losed...\nTry again";
}

void Win() {
    cout << "\nYou won!!!";
}

void Records(int* records) {

    cout << "Records: \n";
    for (int i{}; i < 3; i++) {
        cout << i + 1 << ". " << records[i] << " Points!\n";
    }


}

void addRecord(int* &records, int value) {
    if (value > records[0]) {
        records[2] = records[1];
        records[1] = records[0];
        records[0] = value;
    }
    else if (value > records[1]) {
        records[2] = records[1];
        records[1] = value;
    }
    else if (value > records[2]) {
        records[2] = value;
    }
}

void countPoints(int* &records, int eot, int sot, Mods* mods, const int mode) {
    int value{};
    value = 1000 - (eot - sot) * mods[mode].multiply;
    cout << "\nPoints: " << value << "\n";
    if (value > records[2]) {
        addRecord(records, value);
    }
}

bool play(int** arr, int** ghost_massiv, int* records, Mods* mods, const int mode, const int count, const int countBombs) {

    int move{}, x{ 1 }, y{ 1 }, countFlags{ 0 }, sot{}, eot{};

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

            if (!Shoot(arr, ghost_massiv, count, countFlags, x, y)) {

                showArr(arr, mods, mode, ghost_massiv, count, countFlags, 1);

                eot = time(NULL);

                Lose();

                return 1;
            }
            showArr(arr, mods, mode, ghost_massiv, count, countFlags);

            break;

        case flag:

            Flag(arr, ghost_massiv, count, x, y, countFlags, countBombs);

            showArr(arr, mods, mode, ghost_massiv, count, countFlags);

            break;
        }
        if (ifWin(ghost_massiv, count, countBombs)) {

            showArr(arr, mods, mode, ghost_massiv, count, countFlags, 1);

            eot = time(NULL);

            coutTime(sot, eot);

            countPoints(records, eot, sot, mods, mode);

            Records(records);

            Win();

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
            if (y == 0) {
                return 0;
            }
            else if (y > 3) {
                return 2;
            }
            return y - 1;
            break;


        }
        GotoXY(x, y);
    }
}

void newgame(int** &arr, int** &ghost_massiv, Mods* mods, int &mode, int &count, int &countBombs) {
    system("cls");

    mode = Choice();

    count = mods[mode].count;

    countBombs = mods[mode].countBombs;

    arr = CreateArr(count);

    GenerateArr(arr, count, countBombs);

    ghost_massiv = CreateGhostArr(arr, count);
}

void ReturnRecords(int* &records) {

    ifstream f("C:\\Users\\egork\\source\\repos\\ConsoleApplication13\\records.txt");;

    for (int i{}; i < 3; i++) {
        f >> records[i];
    }

    f.close();
}

void SaveRecords(int*& records) {

    ofstream f("C:\\Users\\egork\\source\\repos\\ConsoleApplication13\\records.txt");;

    for (int i{}; i < 3; i++) {
        f << records[i] << endl;
    }

    f.close();
}