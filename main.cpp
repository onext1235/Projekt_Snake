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

const int height = 10;
const int width = 10;

int score;
int x_tail[100], y_tail[100];
int n_tail = { 0 };
int x = { 5 };
int y = { 5 };
int x_apple;
int y_apple;
char map_choice = 'f';
bool game_over = false;
bool wyjscie = false;

eDirection dir;
eDirection position[100];

int main()
{
    Vec_aski blok(2, aski(2, 'H'));
    Vec_aski miejsce(2, aski(2, ' '));
    Mac papier;
    //Mac screen;
    snake anakonda;
    apple owoc;
    map polmska;

    while (1)
    {
        pasta::menu(map_choice, wyjscie);
        pasta::start(game_over, n_tail, score, x, y, dir, x_apple, y_apple, height);
        while (!game_over)
        {
            auto screen = pasta::setup(polmska, blok, papier, map_choice, height);
         
            pasta::show(screen, anakonda, owoc, height, x, y, x_apple, y_apple, n_tail, position, x_tail, y_tail, dir, score);
            pasta::input(dir);
            pasta::logic(screen, blok, miejsce, height, x, y, x_apple, y_apple, x_tail, y_tail, position, n_tail, dir, game_over, score, map_choice);
            Sleep(200);
        }
    }
}
