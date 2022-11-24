#include <iostream>
#include <fstream>
#include <string>

#include "Generation.h"
#include "Creation.h"
#include "Logic.h"
#include "common.h"

using namespace std;

int main()
{
    srand(time(NULL));

    Mods* mods = new Mods[3]{
        {10, 15, "----------------------", 7},
        {15, 35, "--------------------------------", 4},
        {20, 60, "------------------------------------------", 1}
    };

    string decision{};

    int mode = Choice();

    int count = mods[mode].count;

    int countBombs = mods[mode].countBombs;
    
    int** arr = CreateArr(count);

    GenerateArr(arr, count, countBombs);

    int** ghost_massiv = CreateGhostArr(arr, count);

    int* records = CreateRecords();

    ReturnRecords(records);

    while (true) {

        if (play(arr, ghost_massiv, records, mods, mode, count, countBombs)) {

            cout << "\n\nContinue?[yes/no]\n";
            cin >> decision;
            if (decision == "no") {

                SaveRecords(records);

                break;
            }
            else {

                newgame(arr, ghost_massiv, mods, mode, count, countBombs);
            }
        }

        
    }
    


    return 0;
}