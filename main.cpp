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
    while (1)   // pêtla g³ówna
    {
        pasta::menu();                                                                           //wywo³anie menu gry 
        pasta::start();                                                                          //resetowanie zmiennych
        while (!pasta::game_over)
        {
            pasta::screen = pasta::setup(pasta::polmska, pasta::blok, pasta::papier);            //tworzenie mapy
            pasta::show(pasta::screen, pasta::anakonda, pasta::owoc);                            //wyœwietlanie gry w konsoli
            pasta::input();                                                                      //sczytywanie przyciku
            pasta::logic(pasta::screen, pasta::blok, pasta::miejsce);                            //kolizje/punktacja/tworzenie nowych jab³ek
            Sleep(200);
        }
    }
}
