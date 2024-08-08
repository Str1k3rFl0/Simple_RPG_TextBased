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

enum DIRECTIONS { NORTH, WEST, SOUTH, EAST };
enum LOCATIONS { CENTRE, BANK, SUPERMARKET, HOSPITAL, HOME, PARK };
enum VERBS { LOOK, STATS, OPTIONS };

const int NONE { -1 };
const int DIRS { 4 };
const int LOCS { 6 };
const int VERB { 3 };

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

public:
    void setLocations();
    void setDirections();
    void setVerbs();
    void sectionCommand(std::string& cmd, std::string& wd1, std::string& wd2);
    void lookAround();
    bool parser(const std::string& wd1, const std::string& wd2, Player& pl);
    void showOptions();

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
