#pragma once
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

using aski = std::vector<char>;
using Vec_aski = std::vector<aski>;

using Dac = std::vector<Vec_aski>;
using Mac = std::vector<Dac>;

enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };

struct snake
{
    snake();
    aski skin;
    Vec_aski head_up;
    Vec_aski head_down;
    Vec_aski head_left;
    Vec_aski head_right;
    Vec_aski tail_up;
    Vec_aski tail_side;
};

struct apple
{
    apple();
    aski xd;
    Vec_aski japko;
};

struct map
{
    map();
    Mac world;
};

class pasta
{  
    public:

    static const int height;
    static const int width;
    static int score;
    static int x_tail[100], y_tail[100];
    static int n_tail;
    static int x;
    static int y;
    static int x_apple;
    static int y_apple;
    static char map_choice;
    static bool game_over;
    static bool wyjscie;

    static Vec_aski blok;
    static Vec_aski miejsce;
    static Mac papier;
    static Mac screen;
    static snake anakonda;
    static apple owoc;
    static map polmska;

    static eDirection dir;
    static eDirection position[100];
  
    static int RNG();
    static char menu();
    static void start();
    static void input();
    static void logic(Mac& m, Vec_aski& blok, Vec_aski& miejsce);
    static void show(Mac& m, snake& head, apple& owoc);
    static Mac setup(map& mapa, Vec_aski& blok, Mac& papier);
};

