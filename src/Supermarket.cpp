#include "Supermarket.h"

Supermarket::Supermarket()
{
    products[1] = { "Bread", 2 };
    products[2] = { "Milk", 5 };

    stock[1] = 100;
    stock[2] = 50;

    loadStock();
}

void Supermarket::showProducts() const
{
    std::cout << "Available products:\n";
    for (const auto& p : products)
    {
        int id { p.first };
        const auto& namePrice { p.second };
        int price { namePrice.second };
        int availableStock { stock.at(id) };
        std::cout << id << ". " << namePrice.first << " - " << price
                  << " coins (Stock: " << availableStock << ")\n";
    }
}

void Supermarket::buyProduct(Player& pl)
{
    int ch { 0 };
    int quantity { 0 };
    int cost { 0 };

    showProducts();

    std::cout << "Enter the product number to buy: ";
    std::cin >> ch;

    if (products.find(ch) == products.end())
    {
        std::cout << "Invalid choice!\n";
        return;
    }

    cost = products[ch].second;
    int availableStock { stock[ch] };

    std::cout << "Enter quantity: ";
    std::cin >> quantity;

    if (quantity > availableStock)
    {
        std::cout << "Not enough stock!\n";
        return;
    }

    int totalCost { cost * quantity };
    if (pl.getMoney() < totalCost)
    {
        std::cout << "Not enough money!\n";
        return;
    }

    pl.setMoney(pl.getMoney() - totalCost);
    stock[ch] -= quantity;

    pl.addItem(products[ch].first, quantity);

    if (!pl.updateFile("Player.txt"))
    {
        std::cout << "Failed to update account.\n";
    }

    std::cout << "Purchase successful! You bought " << quantity << " item(s) "
              << "and you spent " << totalCost << " coins.\n";
    std::cout << "Money left: " << pl.getMoney() << " coins.\n";

    saveStock();

}

void Supermarket::saveStock() const
{
    std::ofstream myFile("stock.txt");
    if (!myFile.is_open())
    {
        std::cerr << "Error opening stock file for writin.\n";
        return;
    }

    for (const auto& s : stock)
    {
        myFile << s.first << ' ' << s.second << '\n';
    }
}

void Supermarket::loadStock()
{
    std::ifstream myFile("stock.txt");
    if (!myFile.is_open())
    {
        std::cerr << "Error opening stock file for reading!\n";
        stock[1] = 100;
        stock[2] = 50;
        return;
    }

    int id{};
    int quantity{};
    while (myFile >> id >> quantity)
    {
        stock[id] = quantity;
    }
}
