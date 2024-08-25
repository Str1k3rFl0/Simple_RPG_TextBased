#ifndef BANK_H
#define BANK_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <random>
#include <chrono>
#include <thread>
#include <ctime>

#include "Player.h"

class Bank
{
private:
    std::string pin;
    int balance { 0 };

    std::string genCardNum();
    std::string genPIN();
    std::string genExpDate();
    std::string genCVV();

    Player pl{};

public:
    void createCard(Player& pl);
    void showCardInfo(const Player& pl) const;
    void deposit(Player& pl);
    void withdraw(Player& pl);
};

#endif // BANK_H
