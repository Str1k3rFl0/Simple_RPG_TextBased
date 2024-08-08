#ifndef MENU_H
#define MENU_H

#include <windows.h>
#include <iostream>
#include <conio.h>

#include "Player.h"
#include "Map.h"

class SpecialFunc
{
protected:
    SpecialFunc() = default;
    void setColor(unsigned char color);
    void gotoxy(int x, int y);
    void marginsPattern(int x, int y);
    void credits();
    void instructions();
};

class Menu : public SpecialFunc
{
public:
    Menu() = default;
    void mainMenu();
    void playerMenu(Player& pl);
};

#endif // MENU_H
