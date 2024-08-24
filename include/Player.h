#ifndef PLAYER_H
#define PLAYER_H

#include <windows.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <conio.h>
#include <string>
#include <map>

class Player
{
private:
    std::string _name{};
    std::string _age{};
    std::string _sex{};
    std::string _occupation{ "None" };
    std::string _password{};
    int money { 100 };

    std::map<std::string, int> inventory{};

public:
    Player() = default;

    void setName(const std::string& name) { _name = name; }
    void setPassword(const std::string& pass) { _password = pass; }
    void setMoney(int amount) { money = amount; }

    void enterName();
    void enterAge();
    void enterSex();
    void enterPass();

    const std::string& getName() const;
    const std::string& getAge() const;
    const std::string& getSex() const;
    const std::string& getPassword() const;

    int getMoney() { return money; }

    void createAccount(const char* fileName);
    bool showAccount(const char* fileName);
    void modifyDetails(const char* fileName,
        const std::string& oldLine, const std::string& newLine);
    void modifyAccount(const char* fileName);
    bool deleteAccount(const char* fileName);
    bool loadAccount(const char* fileName,
        const std::string& name, const std::string& password);
    bool updateFile(const char* fileName);

    void addItem(const std::string& item, int quantity);
    void saveInventory() const;
    void loadInventory();
    void showInventory() const;
    void initInventory();
    std::string getInvFileName() const { return _name + "_inventory.txt"; }

    void updateMoneyInFile(const char* fileName) { updateFile(fileName); }

    // JUST FOR TEST
    bool increaseMoney(int amount)
    {
        if (money >= amount) { money += amount; return true; } return false;
    }

    void showStats(const char* fileName) const;
};

#endif // PLAYER_H
