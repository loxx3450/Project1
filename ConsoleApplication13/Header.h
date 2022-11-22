#include <iostream>
#pragma once

struct Mods {
    int count{ 0 };
    int countBombs{ 0 };
    std::string strip{ "no_title" };
};

int** CreateArr(const int count);

void GenerateArr(int** arr, const int count, const int countBombs);

bool play(int** arr, Mods* mods, const int mode, const int count, const int countBombs);

int Choice();


