#include <iostream>
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

void showArr(int** arr, int** ghost_massiv, int count) {
    for (int i{1}; i <= count; i++) {
        for (int j{1}; j <= count; j++) {
            if (arr[i][j] == 0) {
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
        cout << endl;
    }
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
    if (x != 0) {
        x /= 2;
    }
    ghost_massiv[y + 1][x + 1] = 2;
}



bool play(int** arr, int count) {
    int** ghost_massiv = CreateArr(count);
    int move{}, x{ 0 }, y{ 0 };

    system("cls");
    showArr(arr, ghost_massiv, count);
    cout << "\n\n";
    show(arr, count);
    
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
                return 1;
            }
            system("cls");
            showArr(arr, ghost_massiv, count);
            cout << "\n\n";
            show(arr, count);
            break;
        case flag:
            Flag(ghost_massiv, x, y);
            system("cls");
            showArr(arr, ghost_massiv, count);
            cout << "\n\n";
            show(arr, count);
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

    if (play(arr, count)) {
        system("cls");
        cout << "You losed";
    }

    return 0;
}