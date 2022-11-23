#pragma once

#include <iostream>

struct Mods {
    int count{ 0 };
    int countBombs{ 0 };
    std::string strip{ "no_title" };
};

enum Values {
    EMPTY = 0,
    SECRET = 0,
    VERIFY = 1,
    FLAG = 2,
    BOMBEMOJI = 6,
    FLAGEMOJI = 20,
    BOMB = 9
};