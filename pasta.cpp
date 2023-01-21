#include "pasta.h"

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

apple::apple()
{
    xd = aski(2, 'a');
    japko = Vec_aski(2, xd);
}

snake::snake()
{
    skin = aski(2, '^');
    head_up = Vec_aski(2, skin);
    skin = aski(2, 'V');
    head_down = Vec_aski(2, skin);
    skin = aski(2, '<');
    head_left = Vec_aski(2, skin);
    skin = aski(2, '>');
    head_right = Vec_aski(2, skin);
    skin = aski(2, '|');
    tail_up = Vec_aski(2, skin);
    skin = aski(2, '-');
    tail_side = Vec_aski(2, skin);
}

map::map()
{
    world = Mac(10, Dac(10, Vec_aski(2, aski(2, ' '))));
}

int pasta::RNG(int height)                                                                                                   // funkcja zwaraza losow¹ liczbê od 0 do height/width
{
    std::random_device rd;
    std::mt19937 mtRandomEngine(rd());
    std::uniform_int_distribution uni_distr(0, height - 1);
    std::vector< int >	random_decimals;
    std::generate_n(back_inserter(random_decimals), 1, [&]() { return uni_distr(mtRandomEngine); });
    return random_decimals[0];
}

int pasta::menu(char map_choice, bool exit)
{
    system("cls");
    std::cout << "SNAKE" << std::endl;
    std::cout << "1. Start" << std::endl;
    std::cout << "2. Credits" << std::endl;
    std::cout << "3. Exit" << std::endl;
    char choice;
    while (1)
    {
        choice = _getch();

        switch (int(choice) - 48)
        {
        case 1:
        {
            system("cls");
            std::cout << "1. Level 1" << std::endl;
            std::cout << "2. Level 2" << std::endl;
            std::cout << "3. Level 3" << std::endl;
            choice = _getch();
            if (int(choice) - 48 == 1 || int(choice) - 48 == 2 || int(choice) - 48 == 3)
            {
                map_choice = choice;
                return 0;
            }
            break;
        }
        case 2:
        {
            break;
        }
        case 3:
        {
            std::exit(0);
            break;
        }
        }
    }
}

void pasta::start(bool& game_over, int n_tail, int score, int x, int y, eDirection dir, int x_apple, int y_apple, int height)
{
    game_over = false;
    n_tail = 0;
    score = 0;
    x = 5;
    y = 5;
    dir = UP;
    bool free = false;

    while (!free)
    {
        x_apple = RNG(height);
        y_apple = RNG(height);
        if (!(x_apple == 0 || y_apple == 0 || x_apple == 9 || y_apple == 9))
        {
            free = true;
        }
    }

}

void pasta::input(eDirection dir)
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'w':
            if (dir != DOWN)
            {
                dir = UP;
            }
            break;
        case 'a':
            if (dir != RIGHT)
            {
                dir = LEFT;
            }
            break;
        case 's':
            if (dir != UP)
            {
                dir = DOWN;
            }
            break;
        case 'd':
            if (dir != LEFT)
            {
                dir = RIGHT;
            }
            break;
        }
    }
}

void pasta::logic(Mac& m, Vec_aski& blok, Vec_aski& miejsce, int height, int x, int y, int x_apple, int y_apple, int x_tail[], int y_tail[], eDirection position[], int n_tail, eDirection dir, bool game_over, int score, char map_choice)
{
    int prev_x = x_tail[0];
    int prev_y = y_tail[0];
    int prev_2x, prev_2y;
    eDirection prev_dir = position[0];
    eDirection prev_2dir;
    position[0] = dir;
    x_tail[0] = x;
    y_tail[0] = y;

    for (int i = 1; i < n_tail; i++)
    {
        prev_2x = x_tail[i];
        prev_2y = y_tail[i];
        x_tail[i] = prev_x;
        y_tail[i] = prev_y;
        prev_x = prev_2x;
        prev_y = prev_2y;

        prev_2dir = position[i];
        position[i] = prev_dir;
        prev_dir = prev_2dir;
    }
    switch (dir)
    {
    case LEFT:
        y--;
        break;
    case RIGHT:
        y++;
        break;
    case UP:
        x--;
        break;
    case DOWN:
        x++;
        break;
    default:
        break;
    }
    if (x < 0)
    {
        x = (height - 1);
    }
    else if (x > (height - 1))
    {
        x = 0;
    }
    if (y < 0)
    {
        y = (height - 1);
    }
    else if (y > (height - 1))
    {
        y = 0;
    }
    for (int i = 0; i < n_tail; i++)
    {
        if (x_tail[i] == x && y_tail[i] == y)
            game_over = true;
    }
    if (map_choice == '2' || map_choice == '3')
    {
        if (m[x][y] == blok)
        {
            game_over = true;
        }
    }
    if (x == x_apple && y == y_apple)
    {
        n_tail += 1;
        score += 1;
        bool free = false;
        while (!free)
        {
            x_apple = RNG(height);
            y_apple = RNG(height);
            if (m[x_apple][y_apple] == miejsce)
            {
                free = true;
            }
        }
    }
}

void pasta::show(Mac& m, snake& head, apple& owoc, int height, int x, int y, int x_apple, int y_apple, int n_tail, eDirection position[], int x_tail[], int y_tail[], eDirection dir, int score)                               // Wyœwietlanie gry na konsoli
{
    system("cls");
    for (int r = 0; r < height; r++)
    {
        for (int i = 0; i < 2; i++)
        {
            for (int c = 0; c < height; c++)
            {
                for (int j = 0; j < 2; j++)
                {
                    if (r == x && c == y)
                    {
                        std::cout << "siema\n";
                        if (dir == UP)
                        {
                            m[r][c] = head.head_up;
                        }
                        else if (dir == DOWN)
                        {
                            m[r][c] = head.head_down;
                        }
                        else if (dir == LEFT)
                        {
                            m[r][c] = head.head_left;
                        }
                        else if (dir == RIGHT)
                        {
                            m[r][c] = head.head_right;
                        }  
                    }
                    else if (r == x_apple && c == y_apple)
                    {
                        m[r][c] = owoc.japko;
                    }
                    else
                    {
                        for (int k = 0; k < n_tail; k++)
                        {
                            if (x_tail[k] == r && y_tail[k] == c)
                            {
                                if (position[k] == LEFT || position[k] == RIGHT)
                                {
                                    m[r][c] = head.tail_side;
                                }
                                if (position[k] == UP || position[k] == DOWN)
                                {
                                    m[r][c] = head.tail_up;
                                }
                            }
                        }
                    }
                    std::cout << "siema\n";
                    std::cout << m[r][c][i][j] << " ";
                }
            }
            std::cout << std::endl;
        }
    }
    std::cout << "Score: " << score << std::endl;
}

Mac pasta::setup(map& mapa, Vec_aski& blok, Mac& papier, char map_choice, int height)
{
    std::cout << "siema\n";
    papier = mapa.world;
    if (map_choice == '1')
    {
        return papier;
    }
    else if (map_choice == '2')
    {
        for (int r = 0; r < height; r++)
        {
            for (int c = 0; c < height; c++)
            {
                if (c == 0 || c == 9 || r == 0 || r == 9)
                {
                    papier[r][c] = blok;
                }
            }
        }
        return papier;
    }
    else if (map_choice == '3')
    {
        for (int r = 0; r < height; r++)
        {
            for (int c = 0; c < height; c++)
            {
                if (c == 0 || c == 9 || r == 0 || r == 9)
                {
                    papier[r][c] = blok;
                }
            }
        }
        return papier;
    }
    std::cout << "siema\n";
}
