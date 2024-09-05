#ifndef STADIUM_H
#define STADIUM_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <thread>
#include <ctime>

#define RED "\033[31m"
#define GREEN "\033[32M"
#define RESET "\033[0m"

class FootballPlayer
{
private:
    std::string name{};
    int age{};
    int shirtNum{};
    std::string position{};

public:
    FootballPlayer(const std::string& plName, int plAge, int plShirtNr, const std::string& pos)
        : name { plName }, age { plAge }
        , shirtNum { plShirtNr }, position { pos }
    {
    }

    const std::string& getName() const { return name; }
    int getShirtNr() const { return shirtNum; }
    const std::string& getPosition() const { return position; }

    void display() const
    {
        std::cout << "Name: " << name << ", Shirt number: " << shirtNum
                  << ", Position: " << position << "\n";
    }
};

class FootballTeam
{
private:
    std::string name{};
    std::vector<FootballPlayer> players{};

public:
    FootballTeam(const std::string& teamName)
        : name { teamName }
    {
    }

    void addPlayer(const FootballPlayer& player);

    const std::string& getName() const { return name; }
    const std::vector<FootballPlayer>& getPlayers() const { return players; }

    FootballPlayer getRandPl() const;
    void displayTeam() const;
};

class FootballGame
{
private:
    FootballTeam teamA;
    FootballTeam teamB;
    int teamAGoals{};
    int teamBGoals{};

public:
    FootballGame(FootballTeam a, FootballTeam b)
        : teamA { a }, teamB { b }, teamAGoals { 0 }, teamBGoals { 0 }
    {
    }

    void playMatch();
};

#endif // STADIUM_H
