#include "Map.h"

void Map::setLocations()
{
    locs[CENTRE].description.assign("Center");
    locs[CENTRE].exits_to_loc[NORTH] = BANK;
    locs[CENTRE].exits_to_loc[WEST] = RESTAURANT;
    locs[CENTRE].exits_to_loc[SOUTH] = PARK;
    locs[CENTRE].exits_to_loc[EAST] = STADIUM;

    locs[BANK].description.assign("Bank");
    locs[BANK].exits_to_loc[NORTH] = NONE;
    locs[BANK].exits_to_loc[WEST] = NONE;
    locs[BANK].exits_to_loc[SOUTH] = CENTRE;
    locs[BANK].exits_to_loc[EAST] = NONE;

    locs[RESTAURANT].description.assign("Restaurant");
    locs[RESTAURANT].exits_to_loc[NORTH] = NONE;
    locs[RESTAURANT].exits_to_loc[WEST] = NONE;
    locs[RESTAURANT].exits_to_loc[SOUTH] = NONE;
    locs[RESTAURANT].exits_to_loc[EAST] = CENTRE;

    locs[PARK].description.assign("Park");
    locs[PARK].exits_to_loc[NORTH] = CENTRE;
    locs[PARK].exits_to_loc[WEST] = NONE;
    locs[PARK].exits_to_loc[SOUTH] = SUPERMARKET;
    locs[PARK].exits_to_loc[EAST] = CASINO;

    locs[SUPERMARKET].description.assign("SuperMarket");
    locs[SUPERMARKET].exits_to_loc[NORTH] = PARK;
    locs[SUPERMARKET].exits_to_loc[WEST] = NONE;
    locs[SUPERMARKET].exits_to_loc[SOUTH] = NONE;
    locs[SUPERMARKET].exits_to_loc[EAST] = NONE;

    locs[STADIUM].description.assign("Stadium");
    locs[STADIUM].exits_to_loc[NORTH] = NONE;
    locs[STADIUM].exits_to_loc[WEST] = CENTRE;
    locs[STADIUM].exits_to_loc[SOUTH] = NONE;
    locs[STADIUM].exits_to_loc[EAST] = NONE;

    locs[CASINO].description.assign("Casino");
    locs[CASINO].exits_to_loc[NORTH] = NONE;
    locs[CASINO].exits_to_loc[WEST] = PARK;
    locs[CASINO].exits_to_loc[SOUTH] = NONE;
    locs[CASINO].exits_to_loc[EAST] = NONE;

}

void Map::setDirections()
{
    dirs[NORTH].word = "NORTH";
    dirs[NORTH].code = NORTH;

    dirs[WEST].word = "WEST";
    dirs[WEST].code = WEST;

    dirs[SOUTH].word = "SOUTH";
    dirs[SOUTH].code = SOUTH;

    dirs[EAST].word = "EAST";
    dirs[EAST].code = EAST;
}

void Map::setVerbs()
{
    verbs[LOOK].word = "LOOK";
    verbs[LOOK].code = LOOK;

    verbs[STATS].word = "STATS";
    verbs[STATS].code = STATS;

    verbs[OPTIONS].word = "OPTIONS";
    verbs[OPTIONS].code = OPTIONS;

    verbs[ENTER].word = "ENTER";
    verbs[ENTER].code = ENTER;

    verbs[LEAVE].word = "LEAVE";
    verbs[LEAVE].code = LEAVE;

    verbs[NEEDMONEY].word = "NEEDMONEY";
    verbs[NEEDMONEY].code = NEEDMONEY;

    verbs[INVENTORY].word = "INVENTORY";
    verbs[INVENTORY].code = INVENTORY;

    verbs[CLEAR].word = "CLEAR";
    verbs[CLEAR].code = CLEAR;
}

void Map::showOptions()
{
    std::cout << "Type NORTH -> to move to the North." << std::endl;
    std::cout << "Type SOUTH -> to move to the South." << std::endl;
    std::cout << "Type WEST -> to move to the West." << std::endl;
    std::cout << "Type EAST -> to move to the East." << std::endl;
    std::cout << "Type LOOK -> to know what locations are around you." << std::endl;
    std::cout << "Type STATS -> to show player stats." << std::endl;
    std::cout << "Type OPTIONS -> to show all verbs." << std::endl;
    std::cout << "Type ENTER -> to enter into a building." << std::endl;
    std::cout << "Type LEAVE -> to leave the building." << std::endl;
    std::cout << "Type NEEDMONEY -> a small hack to increase money." << std::endl;
    std::cout << "Type INVENTORY -> show the player's inventory." << std::endl;
    std::cout << "Type CLEAR -> to clear the window." << std::endl;
    std::cout << "TYPE QUIT -> to quit the game and return to main menu." << std::endl;
}

void Map::enterBuilding()
{
    switch (location)
    {
        case SUPERMARKET:
            isInsideBuilding = true;
            std::cout << "\nEntering supermarket...\n";
            superMarketMenu(pl);
            break;

        case CASINO:
            {
                if (std::stoi(pl.getAge()) >= 18)
                {
                    isInsideBuilding = true;
                    std::cout << "\nEntering casino...\n";
                    cas.setTotalMoney(pl.getMoney());
                    casinoMenu(pl);
                    break;
                }
                else
                {
                    std::cout << "You need to have over or equal 18 years old\n";
                    break;
                }
            }

        case BANK:
            isInsideBuilding = true;
            bankMenu(pl);
            break;

        case STADIUM:
            isInsideBuilding = true;
            stadiumMenu(pl);
            break;

        case RESTAURANT:
            isInsideBuilding = true;
            restaurantMenu(pl);
            break;

        default: std::cout << "There is no building to enter here." << std::endl;
                 break;
    }
}

void Map::leaveBuilding()
{
    if (isInsideBuilding)
    {
        isInsideBuilding = false;
        std::cout << "You have left the building and returned to the outside.\n";
        std::cout << "You are now in " << locs[location].description << ".\n";
    }
    else
    {
        std::cout << "You are not inside a building to leave.\n";
    }
}

void Map::superMarketMenu(Player& pl)
{
    bool running { true };
    while (running)
    {
        std::cout << "You are in the supermarket.\n";
        std::cout << "1. Buy product\n";
        std::cout << "2. Leave supermarket\n";
        std::cout << "Enter your choice: ";
        char ch{};
        std::cin >> ch;
        switch (ch)
        {
            case '1': sm.buyProduct(pl); break;
            case '2': running = false; break;
            default: std::cout << "Invalid choice!\n"; break;
        }
    }
}

void Map::casinoMenu(Player& pl)
{
    bool running { true };
    while (running)
    {
        std::cout << "You are in the casino.\n";
        std::cout << "1. Games\n";
        std::cout << "2. Leave casino\n";
        std::cout << "Enter your choice: ";
        char ch{};
        std::cin >> ch;
        switch (ch)
        {
            case '1': cas.startGame();
                      pl.setMoney(cas.getTotalMoney());
                      pl.updateMoneyInFile("Player.txt");
                      break;

            case '2': running = false; break;
            default: std::cout << "Invalid choice!\n"; break;
        }
    }
}

void Map::bankMenu(Player& pl)
{
    system("cls");
    bool running { true };
    while (running)
    {
        std::cout << "You are in the bank.\n";
        std::cout << "1. Create Bank Account\n";
        std::cout << "2. View Bank Account\n";
        std::cout << "3. Deposit Money\n";
        std::cout << "4. Withdraw Money\n";
        std::cout << "5. Leave Bank\n";
        std::cout << "Enter your choice: ";
        char ch{};
        std::cin >> ch;

        switch (ch)
        {
            case '1': bank.createCard(pl); break;
            case '2': bank.showCardInfo(pl); break;
            case '3': bank.deposit(pl); break;
            case '4': bank.withdraw(pl); break;
            case '5': running = false; break;
            default: std::cout << "Invalid choice. Please try again.\n";
        }
    }
}

void Map::stadiumMenu(Player& pl)
{
    FootballTeam teamA("Team A");
    teamA.addPlayer(FootballPlayer("Andrew", 25, 10, "Forward"));
    teamA.addPlayer(FootballPlayer("Tomy", 22, 15, "Midfielder"));
    teamA.addPlayer(FootballPlayer("Sam", 27, 9, "Defender"));
    teamA.addPlayer(FootballPlayer("George", 24, 1, "Goalkeeper"));
    teamA.addPlayer(FootballPlayer("Paul", 29, 2, "Defender"));
    teamA.addPlayer(FootballPlayer("Luke", 26, 3, "Defender"));
    teamA.addPlayer(FootballPlayer("Nick", 28, 6, "Midfielder"));
    teamA.addPlayer(FootballPlayer("Chris", 21, 4, "Defender"));
    teamA.addPlayer(FootballPlayer("James", 24, 8, "Midfielder"));
    teamA.addPlayer(FootballPlayer("Michael", 23, 11, "Forward"));
    teamA.addPlayer(FootballPlayer("David", 30, 7, "Midfielder"));

    FootballTeam teamB("Team B");
    teamB.addPlayer(FootballPlayer("John", 23, 9, "Forward"));
    teamB.addPlayer(FootballPlayer("Alex", 26, 8, "Midfielder"));
    teamB.addPlayer(FootballPlayer("Mark", 29, 2, "Defender"));
    teamB.addPlayer(FootballPlayer("Steve", 25, 1, "Goalkeeper"));
    teamB.addPlayer(FootballPlayer("Victor", 27, 3, "Defender"));
    teamB.addPlayer(FootballPlayer("Philip", 28, 6, "Midfielder"));
    teamB.addPlayer(FootballPlayer("Brian", 22, 5, "Defender"));
    teamB.addPlayer(FootballPlayer("Harry", 24, 7, "Midfielder"));
    teamB.addPlayer(FootballPlayer("Edward", 25, 4, "Defender"));
    teamB.addPlayer(FootballPlayer("Oliver", 21, 11, "Forward"));
    teamB.addPlayer(FootballPlayer("Jason", 23, 10, "Forward"));

    FootballGame game(teamA, teamB);

    system("cls");
    bool running { true };
    while (running)
    {
        std::cout << "You are in the stadium.\n";
        std::cout << "1. Watch the soccer game\n";
        std::cout << "2. Leave the stadium\n";
        std::cout << "Enter your choice: ";
        char ch{};
        std::cin >> ch;

        switch (ch)
        {
            case '1': game.playMatch(); break;
            case '2': running = false; break;
            default: std::cout << "Invalid choice. Please try again.\n";
        }
    }
}

void Map::restaurantMenu(Player& pl)
{
    system("cls");
    bool running { true };
    while (running)
    {
        std::cout << "You are in the restaurant.\n";
        std::cout << "1. Show Menu\n";
        std::cout << "2. Take Order\n";
        std::cout << "3. View Order Summary\n";
        std::cout << "4. Pay and Exit\n";
        std::cout << "5. Leave Restaurant\n";
        std::cout << "Enter your choice: ";
        char ch{};
        std::cin >> ch;

        switch (ch)
        {
            case '1': rest.showMenu(); break;
            case '2': rest.takeOrder(); break;
            case '3': {
                        int total { rest.calcTotal() };
                        std::cout << "Order Summary:\n";
                        std::cout << "Total amount due: " << total << " coins\n";
                      }
                      break;
            case '4': rest.processPayment(pl); running = false; break;
            case '5': running = false; break;
            default: std::cout << "Invalid choice. Please try again.\n";
        }
    }
}

void Map::sectionCommand(std::string& cmd, std::string& wd1, std::string& wd2)
{
    std::vector<std::string> words{};
    std::string subStr{};

    for (char c : cmd)
    {
        if (c != ' ')
        {
            subStr += c;
        }
        else
        {
            if (!subStr.empty())
            {
                words.push_back(subStr);
                subStr.clear();
            }
        }
    }

    if (!subStr.empty()) {
        words.push_back(subStr);
    }

    words.erase(std::remove_if(words.begin(), words.end(), [](const std::string& s)
    {
        return s.empty();
    }), words.end());

    for (auto& word : words)
    {
        for (char& c : word)
        {
            c = toupper(c);
        }
    }

    if (words.size() == 0)
    {
        std::cout << "No command given" << '\n';
    }
    else if (words.size() == 1)
    {
        wd1 = words[0];
    }
    else if (words.size() == 2)
    {
        wd1 = words[0];
        wd2 = words[1];
    }
    else
    {
        std::cout << "Command too long. Only type one or two words (direction or verb and noun)" << '\n';
    }
}

void Map::lookAround()
{
    std::cout << "I am in " << locs[location].description << "." << '\n';

    for (int i { 0 }; i < DIRS; ++i)
    {
        if (locs[location].exits_to_loc[i] != NONE)
        {
            std::cout << "There is a road " << dirs[i].word
                      << " to a " << locs[locs[location].exits_to_loc[i]].description << "." << '\n';
        }
    }
}

bool Map::parser(const std::string& wd1, const std::string& wd2, Player& pl)
{
    for (int i { 0 }; i < DIRS; i++)
    {
        if (wd1 == dirs[i].word)
        {
            if (locs[location].exits_to_loc[dirs[i].code] != NONE)
            {
                location = locs[location].exits_to_loc[dirs[i].code];
                std::cout << "I am now in " << locs[location].description << "." << '\n';
                return true;
            }
            else
            {
                std::cout << "No road that way!" << '\n';
            }
        }
    }

    for (int i { 0 }; i < VERB; ++i)
    {
        if (wd1 == verbs[i].word)
        {
            if (verbs[i].code == LOOK)
            {
                lookAround();
                return true;
            }
            else if (verbs[i].code == STATS)
            {
                pl.showStats("Player.txt");
                return true;
            }
            else if (verbs[i].code == OPTIONS)
            {
                showOptions();
                return true;
            }
            else if (verbs[i].code == ENTER)
            {
                enterBuilding();
                return true;
            }
            else if (verbs[i].code == LEAVE)
            {
                leaveBuilding();
                return true;
            }
            else if (verbs[i].code == NEEDMONEY)
            {
                if (pl.increaseMoney(15))
                {
                    std::cout << "\nYou received 15 coins. Your new total is: " << pl.getMoney() << '\n';
                    if (pl.updateFile("player.txt"))
                    {
                        std::cout << "Account updated successfully.\n";
                    }
                }
                else
                {
                    std::cout << "Failed to increase money.\n";
                }
                return true;
            }
            else if (verbs[i].code == INVENTORY)
            {
                showInventoryCommand(pl);
                return true;
            }
            else if  (verbs[i].code == CLEAR)
            {
                system("cls");
            }

            std::cout << "Verb not implemented." << '\n';
            return true;
        }
    }

    std::cout << "No valid command entered." << '\n';
    return false;
}

void Map::playGame()
{
    std::string name;
    std::string password;

    std::cout << "Enter your name: ";
    std::cin >> name;
    std::cout << "Enter your password: ";
    std::cin >> password;

    if (!pl.loadAccount("Player.txt", name, password))
    {
        std::cerr << "Failed to load account. Exiting game.\n";
        return;
    }

    std::cout << "Welcome, " << pl.getName() << "!\n\n";

    bool running = true;
    while (running)
    {
        std::cout << "\nEnter a command: ";
        std::string cmd;
        std::getline(std::cin, cmd);

        std::string wd1, wd2;
        sectionCommand(cmd, wd1, wd2);

        if (wd1 == "QUIT")
        {
            running = false;
            std::cout << "Exiting the game. GoodBye!\n";
        }
        else
        {
            if (!parser(wd1, wd2, pl))
            {
                std::cout << "Invalid command. Type 'OPTIONS' to see available commands.\n";
            }
        }
    }

    pl.saveInventory();
    std::cout << '\n';
}
