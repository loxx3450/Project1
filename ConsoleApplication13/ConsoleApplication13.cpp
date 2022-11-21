#include <iostream>
#include <Windows.h>
#include <conio.h>
using namespace std;

struct Mods {
    int count{ 0 };
    int countBombs{ 0 };
    string strip{ "no_title" };
};


enum {
    EMPTY = 0,
    SECRET = 0,
    VERIFY = 1,
    FLAG = 2,
    BOMB = 9
};

enum {
    rright = 77,
    up = 72,
    down = 80,
    lleft = 75,
    shoot = 13,
    flag = 32
};

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

void GotoXY(int X, int Y)
{
    HANDLE  hConsole;
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = { X, Y };
    SetConsoleCursorPosition(hStdOut, coord);
}



int** CreateArr(const int count) {
    int** arr = new int* [count + 2];

    for (int i{}; i < count + 2; i++) {

        arr[i] = new int[count + 2]{0};
    }

    return arr;
}

int random(int min = 0, int max = 9) {

    return rand() % (max - min + 1) + min;
}

void GenerateBombs(int** arr, const int count, const int countBombs) {
    int x{}, y{};

    for (int i{}; i < countBombs; i++) {

        x = random(1, count);
        y = random(1, count);

        if (arr[x][y] != BOMB) {

            arr[x][y] = BOMB;
        }
        else {

            i--;
            continue;
        }
        
    }
}

int CheckBombs(int** arr, const int count, const int x, const int y) {
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

void BombsAround(int** arr, const int count) {
    for (int i{ 1 }; i <= count; i++) {

        for (int j{ 1 }; j <= count; j++) {

            if (arr[i][j] != BOMB) {

                arr[i][j] = CheckBombs(arr, count, i, j);
            }
        }
    }
}

void GenerateArr(int** arr, const int count, const int countBombs) {
    GenerateBombs(arr, count, countBombs);
    BombsAround(arr, count);
}

void showArr(int** arr, Mods* mods, const int mode, int** ghost_massiv, const int count, const int countFlags, const int end = 0) {

    system("cls");

    cout << mods[mode].strip;

    for (int i{1}; i <= count; i++) {

        cout << "|";
        for (int j{1}; j <= count; j++) {

            if (arr[i][j] == EMPTY) {

                ghost_massiv[i][j] = 1;
                cout << "  ";
            }
            else if (end == TRUE && arr[i][j] == BOMB) {
                SetColor(Red, Black);
                cout << "& ";
                SetColor(White, Black);
            }
            else if (ghost_massiv[i][j] == SECRET) {

                cout << "* ";
            }
            else if (ghost_massiv[i][j] == FLAG) {
                SetColor(Red, Black);
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

int CheckAround(int** arr, const int count, const int x, const int y) {

    for (int i{ x - 1 }; i <= x + 1; i++) {

        for (int j{ y - 1 }; j <= y + 1; j++) {

            if (arr[i][j] == EMPTY && i >= 1 && i <= count && j >= 1 && j <= count) {

                return 1;
            }
        }
    }
    return 0;
}

void GenerateghostArr(int** arr, int** ghost_massiv, const int count) {
    for (int i{ 1 }; i <= count; i++) {

        for (int j{ 1 }; j <= count; j++) {

            ghost_massiv[i][j] = CheckAround(arr, count, i, j);
        }
    }
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

void Flag(int** ghost_massiv, int x, int y, int &countFlags, int countBombs) {

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

        cout << "You win";

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

bool play(int** arr, Mods* mods, const int mode, const int count, const int countBombs) {

    int move{}, x{ 1 }, y{ 1 }, countFlags{0};

    int** ghost_massiv = CreateArr(count);

    GenerateghostArr(arr, ghost_massiv, count);

    showArr(arr, mods, mode, ghost_massiv, count, countFlags);
    
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

int main()
{
    srand(time(NULL));
    rand();

    Mods* mods = new Mods[3]{
        {10, 15, "----------------------\n"},
        {15, 35, "--------------------------------\n"},
        {20, 60, "------------------------------------------\n"}
    };

    int mode = Choice();

    const int count = mods[mode].count;

    const int countBombs = mods[mode].countBombs;
    
    int** arr = CreateArr(count);

    GenerateArr(arr, count, countBombs);

    if (play(arr, mods, mode, count, countBombs)) {
        cout << "\nYou Won";
    }
    else {
        cout << "\nYou Losed";
    }

    return 0;
}