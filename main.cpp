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
    while (1)   // p�tla g��wna
    {
        pasta::menu();                                                                           //wywo�anie menu gry 
        pasta::start();                                                                          //resetowanie zmiennych
        while (!pasta::game_over)
        {
            pasta::screen = pasta::setup(pasta::polmska, pasta::blok, pasta::papier);            //tworzenie mapy
            pasta::show(pasta::screen, pasta::anakonda, pasta::owoc);                            //wy�wietlanie gry w konsoli
            pasta::input();                                                                      //sczytywanie przyciku
            pasta::logic(pasta::screen, pasta::blok, pasta::miejsce);                            //kolizje/punktacja/tworzenie nowych jab�ek
            Sleep(200);
        }
    }
}
