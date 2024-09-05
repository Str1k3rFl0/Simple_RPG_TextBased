#ifndef RESTAURANT_H
#define RESTAURANT_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <map>

#include "Player.h"

class Restaurant
{
private:
    std::map<std::string, int> foodMenu
    {
        { "Pizza Margherita", 30 },
        { "Pizza Quattro Stagioni", 38 },
        { "Pizza Diavola", 41 },
        { "Pizza Prosciutto e Funghi", 32 },
        { "Pizza Tonno e Cipolla", 34 },
        { "Pizza Pepperoni", 35 },

        { "Classic Cheeseburger", 25 },
        { "Bacon Burger", 30 },
        { "BBQ Burger", 32 },
        { "Mushroom Swiss Burger", 27 },
        { "Veggie Burger", 20 },

        { "Spaghetti Carbonara", 25 },
        { "Fettuccine Alfredo", 25 },
        { "Penne Arrabbiata", 25 },
        { "Lasagna", 25 },
        { "Pesto Pasta", 25 }
    };

    std::map<std::string, int> drinkMenu
    {
        { "Cola", 5 },
        { "Pepsi", 6 },
        { "Lemonade", 14 },
        { "Orange Fresh", 18 }
    };

    std::map<std::string, int> sauceMenu
    {
        { "Ketchup", 5 },
        { "BBQ", 5 }
    };

    std::map<std::string, int> dessertMenu
    {
        { "Ice Cream", 8 },
        { "Cake", 15 },
        { "Pie", 12 }
    };

    std::map<std::string, int> order;

public:
    Restaurant() = default;

    void showMenu();
    void takeOrder();
    int calcTotal();
    void processPayment(Player& pl);

    void showCategory(const std::string& title, const std::map<std::string, int>& category);
};

#endif // RESTAURANT_H
