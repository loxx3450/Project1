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

void GenerateBombs(int** arr, int count, int countBombs) {
    int x{}, y{};
    for (int i{1}; i <= countBombs; i++) {
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

void GenerateArr(int** arr, int count, int countBombs) {
    GenerateBombs(arr, count, countBombs);
    BombsAround(arr, count);
}

void showArr(int** arr, Mods* mods, int mode, int** ghost_massiv, int count) {
    cout << mods[mode].strip;
    for (int i{1}; i <= count; i++) {
        cout << "|";
        for (int j{1}; j <= count; j++) {
            if (arr[i][j] == 0) {
                ghost_massiv[i][j] = 1;
                cout << "  ";
            }
            else if (ghost_massiv[i][j] == 0) {
                cout << "* ";
            }
            else if (ghost_massiv[i][j] == 2) {
                cout << "! ";
            }
            else {
                cout << arr[i][j] << " ";
            }
        }
        cout << "|";
        cout << endl;
    }
    cout << mods[mode].strip;
}

void show(int** arr, int count) {
    for (int i{ 1 }; i <= count; i++) {
        for (int j{ 1 }; j <= count; j++) {
             cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}

bool Shoot(int** arr, int** ghost_massiv, int x, int y) {
    x--;
    y--;
    if (x != 0) {
        x /= 2;
    }
    if (arr[y + 1][x + 1] == 9) {
        return 0;
    }
    ghost_massiv[y + 1][x + 1] = 1;
    return 1;
}

void Flag(int** ghost_massiv, int x, int y) {
    x--;
    y--;
    if (x != 0) {
        x /= 2;
    }
    ghost_massiv[y + 1][x + 1] = 2;
}
int CheckAround(int** arr, int count, int x, int y) {
    for (int i{ x - 1 }; i <= x + 1; i++) {
        for (int j{ y - 1 }; j <= y + 1; j++) {
            if (arr[i][j] == EMPTY && i >= 1 && i <= count && j >= 1 && j <= count) {
                return 1;
            }
        }
    }
    return 0;
}

void GenerateghostArr(int** arr, int** ghost_massiv, int count) {
    for (int i{ 1 }; i <= count; i++) {
        for (int j{ 1 }; j <= count; j++) {
            ghost_massiv[i][j] = CheckAround(arr, count, i, j);
        }
    }
}

int ifWin(int** ghost_massiv, int count, int countBombs) {
    int value{ 0 };
    for (int i{ 1 }; i <= count; i++) {
        for (int j{ 1 }; j <= count; j++) {
            if (ghost_massiv[i][j] != 1) {
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



bool play(int** arr, Mods* mods, int mode, int count, int countBombs) {
    int** ghost_massiv = CreateArr(count);
    GenerateghostArr(arr, ghost_massiv, count);
    int move{}, x{ 1 }, y{ 1 };

    system("cls");
    showArr(arr, mods, mode, ghost_massiv, count);
    
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
                system("cls");
                showArr(arr, mods, mode, ghost_massiv, count);
                return 0;
            }
            system("cls");
            showArr(arr, mods, mode, ghost_massiv, count);
            break;
        case flag:
            Flag(ghost_massiv, x, y);
            system("cls");
            showArr(arr, mods, mode, ghost_massiv, count);
            break;
        }
        if (ifWin(ghost_massiv, count, countBombs)) {
            system("cls");
            showArr(arr, mods, mode, ghost_massiv, count);
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
        {10, 10, "----------------------\n"},
        {15, 20, "--------------------------------\n"},
        {20, 40, "------------------------------------------\n"}
    };

    int mode = Choice();

    const int count = mods[mode].count;

    const int countBombs = mods[mode].countBombs;
    
    int** arr = CreateArr(count);

    GenerateArr(arr, count, countBombs);

    if (play(arr, mods, mode, count, countBombs)) {
        cout << "You Won";
    }
    else {
        cout << "You Losed";
    }

    return 0;
}