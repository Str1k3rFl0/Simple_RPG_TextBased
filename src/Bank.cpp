#include "Bank.h"

std::string Bank::genCardNum()
{
    std::string _numCard;
    std::stringstream _numCardStream;

    int n1 = rand() % 9999;
    int n2 = rand() % 9999;
    int n3 = rand() % 9999;
    int n4 = rand() % 9999;
    _numCardStream << std::setw(4) << std::setfill('0') << n1 << ' '
                   << std::setw(4) << n2 << ' '
                   << std::setw(4) << n3 << ' '
                   << std::setw(4) << n4;
    _numCard = _numCardStream.str();
    _numCardStream.str("");

    return _numCard;
}

std::string Bank::genPIN()
{
    std::string gPin;
    for (std::size_t i { 0 }; i < 4; ++i)
    {
        gPin += std::to_string(rand() % 10);
    }

    return gPin;
}

std::string Bank::genExpDate()
{
    std::mt19937 mt{static_cast<unsigned long>(std::chrono::high_resolution_clock::now().time_since_epoch().count())};
    std::uniform_int_distribution<int> monthDist{1, 12};
    std::uniform_int_distribution<int> yearDist{0, 9}; // Generăm ultimele două cifre ale anului

    int month { monthDist(mt) };
    int year { 24 + yearDist(mt) };

    std::stringstream expDateStream;
    expDateStream << std::setw(2) << std::setfill('0') << month << "/"
                  << std::setw(2) << std::setfill('0') << year;
    return expDateStream.str();
}

std::string Bank::genCVV()
{
    std::string gCVC;
    for (std::size_t i { 0 }; i < 3; ++i)
    {
        gCVC += std::to_string(rand() % 10);
    }

    return gCVC;
}

void Bank::createCard(Player& pl)
{
    system("cls");

    std::string cardNumber = genCardNum();
    std::string expDate = genExpDate();
    std::string cvv = genCVV();
    std::string PIN = genPIN();
    double balance { 0 };

    std::cout << "\nCreating the card number...\n";
    Sleep(1000);
    std::cout << "[+] Card Number: " << cardNumber;

    std::cout << "\nCreating the Exp. Date...\n";
    Sleep(1000);
    std::cout << "[+] Exp. Date: " << expDate;

    std::cout << "\nCreating the CVV code...\n";
    Sleep(1000);
    std::cout << "[+] CVV code: " << cvv;

    std::cout << "\nCreating PIN...\n";
    Sleep(1000);
    std::cout << "[+] PIN code: " << PIN;

    std::ofstream cardFile(pl.getName() + "_card.txt");
    if (cardFile.is_open())
    {
        cardFile << "Card Number: " << cardNumber << "\n";
        cardFile << "Exp. Date: " << expDate << "\n";
        cardFile << "CVV: " << cvv << "\n";
        cardFile << "PIN: " << PIN << "\n";
        cardFile << "Balance: " << balance <<  "\n";
        cardFile.close();
        std::cout << "\nCard created successfully!\n";
    }
    else
    {
        std::cerr << "Error creating card file!\n";
    }
}

void Bank::showCardInfo(const Player& pl) const
{
    system("cls");

    std::string playerName { pl.getName() };

    std::string cardFileName { playerName + "_card.txt" };

    std::ifstream cardFile(cardFileName);

    if (!cardFile.is_open()) {
        std::cerr << "Error: Unable to open the card file for player " << playerName << ".\n";
        return;
    }

    std::string fileCardNumber{};
    std::string fileExpiryDate{};
    std::string fileCVV{};
    std::string filePIN{};
    double fileBalance { 0.0 };

    std::string line{};

    while (std::getline(cardFile, line))
    {
        if (line.find("Card Number:") == 0)
        {
            fileCardNumber = line.substr(12);
        }
        else if (line.find("Exp. Date:") == 0)
        {
            fileExpiryDate = line.substr(11);
        }
        else if (line.find("CVV:") == 0)
        {
            fileCVV = line.substr(5);
        }
        else if (line.find("PIN:") == 0)
        {
            filePIN = line.substr(5);
        }
        else if (line.find("Balance:") == 0)
        {
            fileBalance = std::stod(line.substr(9));
        }
    }

    cardFile.close();

    if (fileCardNumber.empty() || fileExpiryDate.empty() || fileCVV.empty() || filePIN.empty())
    {
        std::cerr << "Error: Failed to read all card details for player " << playerName << ".\n";
        return;
    }

    std::string userPIN{};
    std::cout << "Please enter your PIN to view card details: ";
    std::cin >> userPIN;

    if (userPIN != filePIN)
    {
        std::cerr << "Error: Incorrect PIN. Access denied.\n";
        return;
    }

    std::cout << "Card Details for " << playerName << ":\n";
    std::cout << "Card Number: " << fileCardNumber << "\n";
    std::cout << "Exp. Date: " << fileExpiryDate << "\n";
    std::cout << "CVV: " << fileCVV << "\n";
    std::cout << "PIN: " << filePIN << "\n";
    std::cout << "Balance: " << fileBalance << "\n";

}

void Bank::deposit(Player& pl) {
    std::string playerName = pl.getName();

    std::string cardFileName = playerName + "_card.txt";
    std::ifstream cardFile(cardFileName);

    if (!cardFile.is_open()) {
        std::cerr << "Error: Unable to open the card file for player " << playerName << ".\n";
        return;
    }

    std::string fileCardNumber;
    std::string fileExpDate;
    std::string fileCVV;
    std::string filePIN;
    double fileBalance { 0.0 };

    std::string line;
    while (std::getline(cardFile, line))
    {
        if (line.find("Card Number:") == 0)
        {
            fileCardNumber = line.substr(12);
        }
        else if (line.find("Exp. Date:") == 0)
        {
            fileExpDate = line.substr(11);
        }
        else if (line.find("CVV:") == 0)
        {
            fileCVV = line.substr(5);
        }
        else if (line.find("PIN:") == 0)
        {
            filePIN = line.substr(5);
        }
        else if (line.find("Balance:") == 0)
        {
            fileBalance = std::stod(line.substr(9));
        }
    }

    cardFile.close();

    if (fileCardNumber.empty() || fileExpDate.empty() || fileCVV.empty() || filePIN.empty())
    {
        std::cerr << "Error: Failed to read all card details for player " << playerName << ".\n";
        return;
    }

    std::string userPIN;
    std::cout << "Please enter your PIN to deposit money: ";
    std::cin >> userPIN;

    if (userPIN != filePIN)
    {
        std::cerr << "Error: Incorrect PIN. Access denied.\n";
        return;
    }

    double depositAmount;
    std::cout << "Enter the amount you want to deposit: ";
    std::cin >> depositAmount;

    if (depositAmount <= 0)
    {
        std::cerr << "Error: Invalid deposit amount.\n";
        return;
    }

    if (pl.getMoney() < depositAmount)
    {
        std::cerr << "Error: Insufficient funds in your account to deposit that amount.\n";
        return;
    }

    pl.setMoney(pl.getMoney() - depositAmount);
    fileBalance += depositAmount;

    std::ofstream outFile(cardFileName);
    if (outFile.is_open())
    {
        outFile << "Card Number: " << fileCardNumber << "\n";
        outFile << "Exp. Date: " << fileExpDate << "\n";
        outFile << "CVV: " << fileCVV << "\n";
        outFile << "PIN: " << filePIN << "\n";
        outFile << "Balance: " << fileBalance << "\n";
        outFile.close();

        std::cout << "Deposit successful! New balance: " << fileBalance << "\n";
        pl.updateMoneyInFile("Player.txt");

    }
    else
    {
        std::cerr << "Error: Unable to update the card file.\n";
    }
}

void Bank::withdraw(Player& pl)
{
    std::string plName { pl.getName() };
    std::string cardFileName { plName + "_card.txt" };

    std::ifstream cardFile(cardFileName);
    if (!cardFile.is_open())
    {
        std::cerr << "Error: Unable to open the card file for player " << plName << "\n";
        return;
    }

    std::string fileCardNumber{};
    std::string fileExpDate{};
    std::string fileCVV{};
    std::string filePIN{};
    double fileBalance { 0.0 };

    std::string line{};
    while (std::getline(cardFile, line))
    {
        if (line.find("Card Number:") == 0)
        {
            fileCardNumber = line.substr(12);
        }
        else if (line.find("Exp. Date:") == 0)
        {
            fileExpDate = line.substr(11);
        }
        else if (line.find("CVV:") == 0)
        {
            fileCVV = line.substr(5);
        }
        else if (line.find("PIN:") == 0)
        {
            filePIN = line.substr(5);
        }
        else if (line.find("Balance:") == 0)
        {
            fileBalance = std::stod(line.substr(9));
        }
    }

    cardFile.close();

    if (fileCardNumber.empty()|| fileExpDate.empty() || fileCVV.empty() || filePIN.empty())
    {
        std::cerr << "Error: Failed to read all card details for player " << plName << "\n";
        return;
    }

    std::string userPIN{};
    std::cout << "Please enter your PIN to withdraw funds: ";
    std::cin >> userPIN;

    if (userPIN != filePIN)
    {
        std::cerr << "Error: Incorrect PIN. Access denied.\n";
        return;
    }

    double amountWithdraw{};
    std::cout << "Enter the amount to withdraw: ";
    std::cin >> amountWithdraw;

    if (amountWithdraw <= 0)
    {
        std::cerr << "Error: Amount must be positive.\n";
        return;
    }

    if (amountWithdraw > fileBalance)
    {
        std::cerr << "Error: Insufficient funds.\n";
        return;
    }

    fileBalance -= amountWithdraw;

    std::ofstream updatedCardFile(cardFileName);
    if (updatedCardFile.is_open())
    {
        updatedCardFile << "Card Number: " << fileCardNumber << "\n";
        updatedCardFile << "Exp. Date: " << fileExpDate << "\n";
        updatedCardFile << "CVV: " << fileCVV << "\n";
        updatedCardFile << "PIN: " << filePIN << "\n";
        updatedCardFile << "Balance: " << fileBalance << "\n";
        updatedCardFile.close();
        std::cout << "Withdraw successfull! New balance: " << fileBalance << "\n";
    }
    else
    {
        std::cerr << "Error updating card file!\n";
        return;
    }

    double plBalance { pl.getMoney() };
    if (plBalance >= amountWithdraw)
    {
        pl.setMoney(plBalance + amountWithdraw);
        pl.updateFile("Player.txt");
    }
    else
    {
        std::cerr << "Error: Insufficient funds in player account.\n";
    }
}
