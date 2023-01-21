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
    static int RNG(int height);
    static int menu(char map_choice, bool exit);
    static void start(bool& game_over, int n_tail, int score, int x, int y, eDirection dir, int x_apple, int y_apple, int height);
    static void input(eDirection dir);
    static void logic(Mac& m, Vec_aski& blok, Vec_aski& miejsce, int height, int x, int y, int x_apple, int y_apple, int x_tail[], int y_tail[], eDirection position[], int n_tail, eDirection dir, bool game_over, int score, char map_choice);
    static void show(Mac& m, snake& head, apple& owoc, int height, int x, int y, int x_apple, int y_apple, int n_tail, eDirection position[], int x_tail[], int y_tail[], eDirection dir, int score);
    static Mac setup(map& mapa, Vec_aski& blok, Mac& papier, char map_choice, int height);
};

