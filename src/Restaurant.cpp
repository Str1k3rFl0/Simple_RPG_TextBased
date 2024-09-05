#include "Restaurant.h"

void Restaurant::showMenu()
{
    std::cout << "----- Welcome to the Restaurant -----\n";
    showCategory("Food", foodMenu);
    showCategory("Drinks", drinkMenu);
    showCategory("Sauces", sauceMenu);
    showCategory("Desserts", dessertMenu);
}

void Restaurant::showCategory(const std::string& title, const std::map<std::string, int>& category)
{
    std::cout << "\n" << title << " Menu:\n";
    for (const auto& item : category)
    {
        std::cout << std::setw(15) << item.first << ": " << item.second << " coins\n";
    }
}

void Restaurant::takeOrder()
{
    std::string item{};
    int quantity{};

    while (true)
    {
        std::cout << "\nEnter item to order (or type 'done' to finish): ";
        std::cin >> item;

        if (item == "done")
        {
            break;
        }

        if (foodMenu.count(item) || drinkMenu.count(item) || sauceMenu.count(item) || dessertMenu.count(item))
        {
            std::cout << "Enter quantity: ";
            std::cin >> quantity;

            if (order.count(item))
            {
                order[item] += quantity;
            }
            else
            {
                order[item] = quantity;
            }

            std::cout << item << " added to your order.\n";
        }
        else
        {
            std::cout << "Item not found on the menu!\n";
        }
    }
}

int Restaurant::calcTotal()
{
    int total { 0 };

    for (const auto& entry : order)
    {
        int price{ 0 };
        if (foodMenu.count(entry.first))
        {
            price = foodMenu[entry.first];
        }
        else if (drinkMenu.count(entry.first))
        {
            price = drinkMenu[entry.first];
        }
        else if (drinkMenu.count(entry.first))
        {
            price = sauceMenu[entry.first];
        }
        else if (dessertMenu.count(entry.first))
        {
            price = dessertMenu[entry.first];
        }

        total += price * entry.second;
    }

    return total;
}

void Restaurant::processPayment(Player& pl)
{
    int total { calcTotal() };

    std::cout << "\nYour total is: " << total << " coins.\n";

    if (pl.getMoney() >= total)
    {
        pl.setMoney(pl.getMoney() - total);
        pl.updateFile("Player.txt");
        std::cout << "Payment successful! You now have " << pl.getMoney() << " coins left.\n";
    }
    else
    {
        std::cout << "Insufficient funds! Your need " << total - pl.getMoney() << " more coins.\n";
    }
}
