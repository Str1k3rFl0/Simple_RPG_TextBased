#include "Player.h"

void Player::enterName()
{
    std::cout << "Enter your name :: ";
    std::cin >> _name;
}

void Player::enterAge()
{
    std::cout << "Enter your age :: ";
    std::cin >> _age;
}

void Player::enterSex()
{
    std::cout << "Enter your sex :: ";
    std::cin >> _sex;
}

void Player::enterPass()
{
    std::cout << "Enter your password :: ";
    std::cin >> _password;
}

const std::string& Player::getName() const
{
    return _name;
}

const std::string& Player::getAge() const
{
    return _age;
}

const std::string& Player::getSex() const
{
    return _sex;
}

const std::string& Player::getPassword() const
{
    return _password;
}

void Player::createAccount(const char* fileName)
{
    system("cls");

    enterName();
    enterAge();
    enterSex();
    enterPass();

    std::ofstream myFile(fileName, std::ios::app);
    myFile << getName() << ' ' << getAge()
           << ' ' << getSex() << ' ' << _occupation << ' '
           << getPassword() << ' ' << getMoney() << '\n';

    myFile.close();

    std::cout << "\n\nThis account is created successfully!";
    std::cout << "\nPress ENTER to continue...";
    _getch();
}

bool Player::showAccount(const char* fileName)
{
    system("cls");

    std::ifstream myFile(fileName, std::ios::in);

    std::cout << "Enter your name :: ";
    std::string tName{};
    std::cin >> tName;

    std::cout << "Enter your password :: ";
    std::string tPassword{};
    std::cin >> tPassword;

    if (!myFile.is_open())
    {
        std::cerr << "\nThe file can't be opened!\n";
        return false;
    }

    std::string line{};
    std::string oldLine{};
    while (std::getline(myFile, line))
    {
        std::istringstream iss { line };
        std::string fName{};
        std::string fAge{};
        std::string fSex{};
        std::string fOccupation{};
        std::string fPassword{};
        int fMoney{};

        if (iss >> fName >> fAge >> fSex >> fOccupation >> fPassword >> fMoney)
        {
            if (tName == fName && tPassword == fPassword)
            {
                system("cls");
                std::cout << "Account found:\n";
                std::cout << "Name: " << fName << '\n'
                          << "Age: " << fAge << '\n'
                          << "Sex: " << fSex << '\n'
                          << "Occupation: " << fOccupation << '\n'
                          << "Password: " << fPassword << '\n'
                          << "Money: " << fMoney << '\n';
                std::cout << "Press ENTER to continue...";
                _getch();

                return true;
            }
        }
    }

    myFile.close();
    std::cerr << "\nAccount not found or incorrect password!\n";
    std::cout << "Press ENTER to continue...";
    _getch();
    return false;
}

void Player::modifyDetails(const char* fileName,
    const std::string& oldLine, const std::string& newLine)
{
    std::ifstream myFile(fileName);
    std::ofstream tempFile("Temp.txt");
    std::string line{};

    while (std::getline(myFile, line))
    {
        if (line != oldLine)
        {
            tempFile << line << std::endl;
        }
        else
        {
            tempFile << newLine << std::endl;
        }
    }

    myFile.close();
    tempFile.close();

    remove(fileName);
    rename("Temp.txt", fileName);

    std::cout << "\nDetails updated successfully\n";
}

void Player::modifyAccount(const char* fileName)
{
    system("cls");

    std::ifstream myFile(fileName);

    std::cout << "Enter your name :: ";
    std::string tName{};
    std::cin >> tName;

    std::cout << "Enter your password :: ";
    std::string tPassword{};
    std::cin >> tPassword;

    std::string line{};
    std::string oldLine{};

    while (std::getline(myFile, line))
    {
        std::istringstream iss { line };
        std::string fName{};
        std::string fAge{};
        std::string fSex{};
        std::string fOccupation{};
        std::string fPassword{};
        int fMoney{};

        if (iss >> fName >> fAge >> fSex >> fOccupation >> fPassword >> fMoney)
        {
            if (tName == fName && tPassword == fPassword)
            {
                oldLine = line;
                break;
            }
        }
    }

    myFile.close();

    if (oldLine.empty())
    {
        std::cerr << "\nAccount not found or incorrect password!\n";
        std::cout << "Press ENTER to continue...";
        _getch();
        return;
    }

    std::cout << "\nWhich detail would you like to modify?\n";
    std::cout << "[1] Name " << std::endl;
    std::cout << "[2] Age " << std::endl;
    std::cout << "[3] Sex " << std::endl;
    std::cout << "[4] Password " << std::endl;
    std::cout << "[5] Money " << std::endl;
    std::cout << "\nEnter your choice: ";
    char ch{};
    std::cin >> ch;

    std::string newDetail{};
    int newMoney{};

    switch (ch)
    {
        case '1': std::cout << "Enter new name: ";
                  std::cin >> newDetail;
                  break;

        case '2': std::cout << "Enter new age: ";
                  std::cin >> newDetail;
                  break;

        case '3': std::cout << "Enter new sex: ";
                  std::cin >> newDetail;
                  break;

        case '4': std::cout << "Enter new password: ";
                  std::cin >> newDetail;
                  break;

        case '5': std::cout << "Enter new money amount: ";
                  std::cin >> newMoney;
                  break;

        default: std::cerr << "Invalid choice!\n"; return;
    }

    std::istringstream iss { oldLine };
    std::string fName{};
    std::string fAge{};
    std::string fSex{};
    std::string fOccupation{};
    std::string fPassword{};
    int fMoney{};

    iss >> fName >> fAge >> fSex >> fOccupation >> fPassword >> fMoney;

    switch (ch)
    {
        case '1': fName = newDetail; break;
        case '2': fAge = newDetail; break;
        case '3': fSex = newDetail; break;
        case '4': fPassword = newDetail; break;
        case '5': fMoney = newMoney; break;
    }

    std::string newLine { fName + " " + fAge + " " + fSex + " " + fOccupation + " " + fPassword + " " + std::to_string(fMoney) };
    modifyDetails(fileName, oldLine, newLine);

    std::cout << "\nModified account with success!\n";
    std::cout << "Press ENTER to continue...";
    _getch();
}

bool Player::loadAccount(const char* fileName,
        const std::string& name, const std::string& password)
{
    system("cls");

    std::ifstream myFile(fileName, std::ios::in);
    if (!myFile.is_open())
    {
        std::cerr << "The file can't be opened!";
        return false;
    }

    std::string line{};
    while (std::getline(myFile, line))
    {
        std::istringstream iss { line };
        std::string fName{};
        std::string fAge{};
        std::string fSex{};
        std::string fOccupation{};
        std::string fPassword{};
        int fMoney{};

        if (iss >> fName >> fAge >> fSex >> fOccupation >> fPassword >> fMoney)
        {
            if (name == fName && password == fPassword)
            {
                std::cout << "Account loaded successfully.\n";
                _name = fName;
                _age = fAge;
                _sex = fSex;
                _occupation = fOccupation;
                _password = fPassword;
                money = fMoney;

                loadInventory();

                myFile.close();
                return true;
            }
        }
    }

    std::cout << "Account not found or password incorrect.\n";
    myFile.close();
    return false;
}

bool Player::deleteAccount(const char* fileName)
{
    system("cls");

    std::ifstream myFile(fileName, std::ios::in);

    std::cout << "Enter your name :: ";
    std::string tName{};
    std::cin >> tName;

    std::cout << "Enter your password :: ";
    std::string tPassword{};
    std::cin >> tPassword;

    if (!myFile.is_open())
    {
        std::cerr << "\nThe file can't be opened!\n";
        return false;
    }

    std::string line{};
    std::string oldLine{};
    bool accFound { false };

    while (std::getline(myFile, line))
    {
        std::istringstream iss { line };
        std::string fName{};
        std::string fAge{};
        std::string fSex{};
        std::string fOccupation{};
        std::string fPassword{};
        int fMoney{};

        if (iss >> fName >> fAge >> fSex >> fOccupation >> fPassword >> fMoney)
        {
            if (tName == fName && tPassword == fPassword)
            {
                oldLine = line;
                accFound = true;
                break;
            }
        }
    }

    myFile.close();

    if (accFound)
    {
        char ch{};
        std::cout << "Are you sure you want to delete this account? (y/n): ";
        std::cin >> ch;

        if (ch == 'y' || ch == 'Y')
        {
            std::ifstream file(fileName);
            std::ofstream tempFile("Temp.txt");
            while (std::getline(file, line))
            {
                if (line != oldLine)
                {
                    tempFile << line << std::endl;
                }
            }

            file.close();
            tempFile.close();

            remove(fileName);
            rename("Temp.txt", fileName);

            std::cout << "\nAccount deleted successfully!\n";
            std::cout << "\nPress ENTER to continue...";
            _getch();
            return true;
        }
        else
        {
            std::cout << "\nAccount deletion canceled.\n";
            std::cout << "\nPress ENTER to continue...";
            _getch();
            return true;
        }
    }
    else
    {
        std::cout << "\nIncorrect name or password!\n";
        std::cout << "\nPress ENTER to continue...\n";
        _getch();
        return false;
    }
}

bool Player::updateFile(const char* fileName)
{
    std::ifstream myFile(fileName);
    std::ofstream tempFile("Temp.txt");
    std::string line{};

    if (!myFile.is_open())
    {
        std::cerr << "Error opening file.\n";
        return false;
    }

    while (std::getline(myFile, line))
    {
        std::istringstream iss { line };
        std::string fName{};
        std::string fAge{};
        std::string fSex{};
        std::string fOccupation{};
        std::string fPassword{};
        int fMoney{};

        if (iss >> fName >> fAge >> fSex >> fOccupation >> fPassword >> fMoney)
        {
            if (_name == fName && _password == fPassword)
            {
                fMoney = money;
                line = fName + " " + fAge + " " + fSex + " " + fOccupation + " " + fPassword + " " + std::to_string(fMoney);
            }
        }
        tempFile << line << std::endl;
    }

    myFile.close();
    tempFile.close();

    if (remove(fileName) != 0 || rename("Temp.txt", fileName) != 0)
    {
        std::cerr << "Error updating file.\n";
        return false;
    }

    saveInventory();

    return true;
}

void Player::showStats(const char* fileName) const
{
    std::ifstream myFile(fileName, std::ios::in);
    if (!myFile.is_open())
    {
        std::cerr << "The file can't be opened!";
        return;
    }

    std::string line{};
    while (std::getline(myFile, line))
    {
        std::istringstream iss { line };
        std::string fName{};
        std::string fAge{};
        std::string fSex{};
        std::string fOccupation{};
        std::string fPassword{};
        int fMoney{};

        if (iss >> fName >> fAge >> fSex >> fOccupation >> fPassword >> fMoney)
        {
            if (_name == fName && _password == fPassword)
            {
                std::cout << "\nPlayer Stats:\n";
                std::cout << "Name: " << fName << '\n'
                          << "Age: " << fAge << '\n'
                          << "Sex: " << fSex << '\n'
                          << "Occupation: " << fOccupation << '\n'
                          << "Money: " << fMoney << '\n';
                myFile.close();
                return;
            }
        }
    }

    std::cout << "Account not found or password incorrect.\n";
    myFile.close();
}

void Player::addItem(const std::string& item, int quantity)
{
    inventory[item] += quantity;
    saveInventory();
}

void Player::saveInventory() const
{
    std::ofstream invFile(getInvFileName(), std::ios::out);

    if (invFile.is_open())
    {
        for (const auto& pair : inventory)
        {
            invFile << pair.first << ' ' << pair.second << '\n';
        }
        invFile.close();
    }
    else
    {
        std::cerr << "Unable to open inventory file for saving!";
    }
}

void Player::loadInventory()
{
    std::ifstream invFile(getInvFileName(), std::ios::in);

    if (invFile.is_open())
    {
        std::string item;
        int quantity;
        while (invFile >> item >> quantity)
        {
            inventory[item] = quantity;
        }
        invFile.close();
    }
    else
    {
        std::cerr << "Unable to open inventory file for loading!";
    }
}

void Player::showInventory() const
{
    std::cout << "Inventory for " << _name << ":\n";
    if (inventory.empty())
    {
        std::cout << "Inventory is empty.\n";
    }
    else
    {
        for (const auto& pair : inventory)
        {
            std::cout << pair.first << ": " << pair.second << '\n';
        }
    }
}

void Player::initInventory()
{
    loadInventory();
}
