#include <iostream>
#pragma once

enum ConsoleColor;

void SetColor(ConsoleColor text, ConsoleColor background);

void coutTime(int sot, int eot);

void showArr(int** arr, Mods* mods, const int mode, int** ghost_massiv, const int count, const int countFlags, const int end = 0);