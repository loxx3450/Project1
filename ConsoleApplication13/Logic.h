#pragma once

#include "common.h"

bool play(int** arr, int** ghost_massiv, Mods* mods, const int mode, const int count, const int countBombs);

int Choice();

void deleteArrs(int** arr, int** ghost_massiv, const int count);

void newgame(int** &arr, int** &ghost_massiv, Mods* mods, int &mode, int &count, int &countBombs);