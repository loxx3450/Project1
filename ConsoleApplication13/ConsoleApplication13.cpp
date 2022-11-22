#include <iostream>
#include "Generation.h"
#include "Creation.h"
#include "Logic.h"

using namespace std;

int main()
{
    srand(time(NULL));

    Mods* mods = new Mods[3]{
        {10, 15, "----------------------"},
        {15, 35, "--------------------------------"},
        {20, 60, "------------------------------------------"}
    };

    int mode = Choice();

    const int count = mods[mode].count;

    const int countBombs = mods[mode].countBombs;
    
    int** arr = CreateArr(count);

    GenerateArr(arr, count, countBombs);
    int** ghost_massiv = CreateGhostArr(arr, count, countBombs);

    if (play(arr, ghost_massiv, mods, mode, count, countBombs)) {
        cout << "\nYou Won";
    }
    else {
        cout << "\nYou Losed";
    }


    return 0;
}