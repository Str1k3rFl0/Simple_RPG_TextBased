#ifndef MAP_H
#define MAP_H

#include <windows.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <cctype>

#include "Menu.h"
#include "Player.h"
#include "Supermarket.h"
#include "Casino.h"

enum DIRECTIONS { NORTH, WEST, SOUTH, EAST };
enum LOCATIONS { CENTRE, BANK, SUPERMARKET, HOSPITAL, HOME, PARK, CASINO };
enum VERBS { LOOK, STATS, OPTIONS, ENTER, LEAVE, NEEDMONEY, INVENTORY, CLEAR };

const int NONE { -1 };
const int DIRS { 4 };
const int LOCS { 7 };
const int VERB { 8 };

class Map
{
public:
    struct Word
    {
        std::string word{};
        int code{};
    };

    struct Location
    {
        std::string description{};
        int exits_to_loc[DIRS];
    };

    Word verbs[VERB];
    Word dirs[DIRS];
    Location locs[LOCS];
    int location{};

    Player pl{};
    Supermarket sm{};
    Casino cas { pl.getMoney() };

    bool isInsideBuilding { false };

public:
    void setLocations();
    void setDirections();
    void setVerbs();
    void sectionCommand(std::string& cmd, std::string& wd1, std::string& wd2);
    void lookAround();
    bool parser(const std::string& wd1, const std::string& wd2, Player& pl);
    void showOptions();
    void enterBuilding();
    void leaveBuilding();

    void superMarketMenu(Player& pl);
    void casinoMenu(Player& pl);

    void showInventoryCommand(Player& pl)
    {
        pl.showInventory();
    }

public:
    Map() : location { CENTRE }
    {
        setLocations();
        setDirections();
        setVerbs();
    }

    void playGame();
};

#endif // MAP_H
