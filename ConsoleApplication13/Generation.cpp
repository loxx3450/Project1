
#include "common.h"
#include "Creation.h"

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
    int value{ 0 };

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

void GenerateGhostArr(int** arr, int** ghost_massiv, const int count) {
    for (int i{ 1 }; i <= count; i++) {

        for (int j{ 1 }; j <= count; j++) {

            ghost_massiv[i][j] = CheckAround(arr, count, i, j);
        }
    }
}

int** CreateGhostArr(int** arr, const int count) {
    int** ghost_massiv = CreateArr(count);

    GenerateGhostArr(arr, ghost_massiv, count);

    return ghost_massiv;
}