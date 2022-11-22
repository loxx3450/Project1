#pragma once
#include <iostream>

struct Mods {
    int count{ 0 };
    int countBombs{ 0 };
    std::string strip{ "no_title" };
};

bool play(int** arr, int** ghost_massiv, Mods* mods, const int mode, const int count, const int countBombs);

int Choice();