#ifndef PLAYER_H
#define PLAYER_H

#include <windows.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <conio.h>
#include <string>

class Player
{
private:
    std::string _name{};
    std::string _age{};
    std::string _sex{};
    std::string _occupation{ "None" };
    std::string _password{};
    static inline int money { 100 };

public:
    void setName(const std::string& name) { _name = name; }
    void setPassword(const std::string& pass) { _password = pass; }

    void enterName();
    void enterAge();
    void enterSex();
    void enterPass();

    const std::string& getName() const;
    const std::string& getAge() const;
    const std::string& getSex() const;
    const std::string& getPassword() const;

    static int getMoney() { return money; }

    void createAccount(const char* fileName);
    bool showAccount(const char* fileName);
    void modifyDetails(const char* fileName,
        const std::string& oldLine, const std::string& newLine);
    void modifyAccount(const char* fileName);
    bool deleteAccount(const char* fileName);
    bool loadAccount(const char* fileName,
        const std::string& name, const std::string& password);

    void showStats(const char* fileName) const;
};

#endif // PLAYER_H
