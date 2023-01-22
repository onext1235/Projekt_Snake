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
                                            
eDirection pasta::dir;                                          // inicjalizacja potrzebnych zmiennych
eDirection pasta::position[100];            

const int pasta::height = 10;
const int pasta::width = 10;
int pasta::score = { 0 };
int pasta::x_tail[100];
int pasta::y_tail[100];
int pasta::n_tail = { 0 };
int pasta::x = { 5 };
int pasta::y = { 5 };
int pasta::x_apple;
int pasta::y_apple;
char pasta::map_choice;
bool pasta::game_over = false;

Vec_aski pasta::blok(2, aski(2, 'H'));
Vec_aski pasta::miejsce(2, aski(2, ' '));
Mac pasta::papier;
Mac pasta::screen;
snake pasta::anakonda;
apple pasta::owoc;
map pasta::polmska;

apple::apple()                                                  // inicjalizacja struktur
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

int pasta::RNG()                                                                                                   // funkcja zwaraza losow¹ liczbê od 0 do height/width
{
    std::random_device rd;
    std::mt19937 mtRandomEngine(rd());
    std::uniform_int_distribution uni_distr(0, height - 1);
    std::vector< int >	random_decimals;
    std::generate_n(back_inserter(random_decimals), 1, [&]() { return uni_distr(mtRandomEngine); });
    return random_decimals[0];
}

char pasta::menu()
{
    
    char choice;
    while (1)
    {
        system("cls");
        std::cout << "SNAKE" << std::endl;
        std::cout << "Last SCORE: " << score << std::endl;
        std::cout << "1. Start" << std::endl;
        std::cout << "2. Credits" << std::endl;
        std::cout << "3. Exit" << std::endl;
        choice = _getch();

        switch (int(choice)-48)
        {
        case 1:
        {
            system("cls");
            std::cout << "1. Level 1" << std::endl;
            std::cout << "2. Level 2" << std::endl;
            std::cout << "3. Level 3" << std::endl;
            choice = _getch();
            if (choice == '1' || choice == '2' || choice == '3')
            {
                map_choice = choice;
                return map_choice;
            }
            break;
        }
        case 2:
        {
            system("cls");
            std::cout << "Created by: " << std::endl;
            std::cout << "Maciej Drozdz" << std::endl;
            Sleep(3000);
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

void pasta::start()
{
    game_over = false;
    n_tail = 0;
    score = 0;
    x = 5;
    y = 5;
    dir = STOP;   
    bool free = false;

    while (!free)
    {
        x_apple = RNG();
        y_apple = RNG();
        if (!(x_apple == 0 || y_apple == 0 || x_apple == 9 || y_apple == 9))
        {
            free = true;
        }
    }

}

void pasta::input()
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

void pasta::logic(Mac& m, Vec_aski& blok, Vec_aski& miejsce)
{
    int prev_x = x_tail[0];                             //obliczanie pozycji ogonu
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
    switch (dir)                    // wyznaczanie kierunku wê¿a
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
    for (int i = 0; i < n_tail; i++)                                        // sprawdzanie kolizji z ogonem oraz œcian¹
    {
        if (x_tail[i] == x && y_tail[i] == y)
            game_over = true;
    }
    if (int(map_choice) - 48 == 2 || int(map_choice) - 48 == 3)
    {
        if (m[x][y] == blok)
        {
            game_over = true;
        }
    }
    if (x == x_apple && y == y_apple)                                       //zjedzenie jab³ka oraz generacja nowego
    {
        n_tail += 1;
        score += 1;
        bool free = false;
        while (!free)
        {
            x_apple = RNG();
            y_apple = RNG();
            if (m[x_apple][y_apple] == miejsce)
            {
                free = true;
            }
        }
    }
}

void pasta::show(Mac& m, snake& head, apple& owoc)                               // Wyœwietlanie gry na konsoli
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
                        switch (dir)
                        {  
                        case LEFT:
                            m[r][c] = head.head_left;
                            break;
                        case RIGHT:
                            m[r][c] = head.head_right;
                            break;
                        case UP:
                            m[r][c] = head.head_up;
                            break;
                        case DOWN:
                            m[r][c] = head.head_down;
                            break;
                        default:
                            break;
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
                    std::cout << m[r][c][i][j] << " ";
                }
            }
            std::cout << std::endl;
        }
    }
    std::cout << "Score: " << score << std::endl;
}

Mac pasta::setup(map& mapa, Vec_aski& blok, Mac& papier)
{
    
    papier = mapa.world;
    if (map_choice == '1')                                           // tworzenie wybranej mapy
    {
        return papier;
    }
    else if (int(map_choice) - 48 == 2)
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
    else if (int(map_choice) - 48 == 3)
    {
        for (int r = 0; r < height; r++)
        {
            for (int c = 0; c < height; c++)
            {
                if (c == 0 || c == 9)
                {
                    papier[r][c] = blok;
                }
            }
        }
        return papier;
    }
}
