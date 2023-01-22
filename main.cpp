#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <tuple>
#include <algorithm>
#include <cassert>
#include <random>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <dos.h>
#include <windows.h>
#include "pasta.h"

int main()
{
    while (1)
    {
        pasta::menu();
        pasta::start();
        while (!pasta::game_over)
        {
            pasta::screen = pasta::setup(pasta::polmska, pasta::blok, pasta::papier);
            pasta::show(pasta::screen, pasta::anakonda, pasta::owoc);
            pasta::input();
            pasta::logic(pasta::screen, pasta::blok, pasta::miejsce);
            Sleep(200);
        }
    }
}
