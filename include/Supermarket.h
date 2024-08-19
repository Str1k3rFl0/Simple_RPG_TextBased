#ifndef SUPERMARKET_H
#define SUPERMARKET_H

#include "Player.h"

#include <iostream>
#include <map>

class Supermarket
{
private:
    std::map<int, std::pair<std::string, int>> products{};
    std::map<int, int> stock{};

public:
    Supermarket();
    void showProducts() const;
    void buyProduct(Player& pl);
    void saveStock() const;
    void loadStock();
};

#endif // SUPERMARKET_H
