#include "Map.h"

void Map::setLocations()
{
    locs[CENTRE].description.assign("Center");
    locs[CENTRE].exits_to_loc[NORTH] = BANK;
    locs[CENTRE].exits_to_loc[WEST] = HOME;
    locs[CENTRE].exits_to_loc[SOUTH] = PARK;
    locs[CENTRE].exits_to_loc[EAST] = HOSPITAL;

    locs[BANK].description.assign("Bank");
    locs[BANK].exits_to_loc[NORTH] = NONE;
    locs[BANK].exits_to_loc[WEST] = NONE;
    locs[BANK].exits_to_loc[SOUTH] = CENTRE;
    locs[BANK].exits_to_loc[EAST] = NONE;

    locs[HOME].description.assign("Home");
    locs[HOME].exits_to_loc[NORTH] = NONE;
    locs[HOME].exits_to_loc[WEST] = NONE;
    locs[HOME].exits_to_loc[SOUTH] = NONE;
    locs[HOME].exits_to_loc[EAST] = CENTRE;

    locs[PARK].description.assign("Park");
    locs[PARK].exits_to_loc[NORTH] = CENTRE;
    locs[PARK].exits_to_loc[WEST] = NONE;
    locs[PARK].exits_to_loc[SOUTH] = SUPERMARKET;
    locs[PARK].exits_to_loc[EAST] = NONE;

    locs[SUPERMARKET].description.assign("SuperMarket");
    locs[SUPERMARKET].exits_to_loc[NORTH] = PARK;
    locs[SUPERMARKET].exits_to_loc[WEST] = NONE;
    locs[SUPERMARKET].exits_to_loc[SOUTH] = NONE;
    locs[SUPERMARKET].exits_to_loc[EAST] = NONE;

    locs[HOSPITAL].description.assign("Hospital");
    locs[HOSPITAL].exits_to_loc[NORTH] = NONE;
    locs[HOSPITAL].exits_to_loc[WEST] = CENTRE;
    locs[HOSPITAL].exits_to_loc[SOUTH] = NONE;
    locs[HOSPITAL].exits_to_loc[EAST] = NONE;
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
}

void Map::showOptions()
{
    std::cout << "Type NORTH -> to move to the North" << std::endl;
    std::cout << "Type SOUTH -> to move to the South" << std::endl;
    std::cout << "Type WEST -> to move to the West" << std::endl;
    std::cout << "Type EAST -> to move to the East" << std::endl;
    std::cout << "Type LOOK -> to know what locations are around you." << std::endl;
    std::cout << "Type STATS -> to show player stats." << std::endl;
    std::cout << "Type OPTIONS -> to show all verbs." << std::endl;
    std::cout << "TYPE QUIT -> to quit the game and return to main menu." << std::endl;
}

void Map::sectionCommand(std::string& cmd, std::string& wd1, std::string& wd2)
{
    /*
    std::string subStr{};
    std::vector<std::string> words{};
    char search { ' ' };

    // Split command into vector
    for (std::size_t i { 0 }; i < cmd.size(); i++)
    {
        if (cmd.at(i) != search)
        {
            subStr.insert(subStr.end(), cmd.at(i));
        }

        if (i == cmd.size() - 1)
        {
            words.push_back(subStr);
            subStr.clear();
        }

        if (cmd.at(i) == search)
        {
            words.push_back(subStr);
            subStr.clear();
        }
    }

    // Clear out any blanks
    for (std::size_t i = words.size() - 1; i > 0; i--)
    {
        if (words.at(i) == "")
        {
            words.erase(words.begin() + i);
        }
    }

    // Make words upper case
    for (std::size_t i { 0 }; i < words.size(); i++)
    {
        for (std::size_t j { 0 }; j < words.at(i).size(); j++)
        {
            if (islower(words.at(i).at(j)))
            {
                words.at(i).at(j) = toupper(words.at(i).at(j));
            }
        }
    }

    if (words.size() == 0)
    {
        std::cout << "No command given." << '\n';
    }

    if (words.size() == 1)
    {
        wd1 = words.at(0);
    }

    if (words.size() == 2)
    {
        wd1 = words.at(0);
        wd2 = words.at(1);
    }

    if (words.size() > 2)
    {
        std::cout << "Command too long. Only type one or two words (direction or verb and noun)" << '\n';
    }
    */

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
            std::cout << "Verb not implemented." << '\n';
            return true;
        }
    }

    std::cout << "No valid command entered." << '\n';
    return false;
}

void Map::playGame()
{
    Menu menu{};
    Player pl{};
    const char* fileName { "Player.txt" };
    bool authenticated { false };

    /*
    while (!authenticated)
    {
        std::cout << "Please log in to start the game.\n";
        authenticated = pl.authenticate(fileName);
        if (!authenticated)
        {
            std::cout << "Failed to log in. Please try again.\n";
            std::cout << "Press ENTER...\n";
            _getch();
        }
    }
    */

    std::string name{};
    std::string password{};
    while (!authenticated)
    {
        std::cout << "Enter your name: ";
        std::cin >> name;
        std::cout << "Enter your password: ";
        std::cin >> password;

        if (pl.loadAccount(fileName, name, password))
        {
            std::cout << "Welcome, " << pl.getName() << "!\n";
            std::cout << "Press ENTER to continue...";
            _getch();
            authenticated = true;
        }
        else
        {
            std::cout << "Incorrect name or password. Please try again!\n";
        }
    }
    system("cls");

    pl.setName(name);
    pl.setPassword(password);

    std::string command{};
    std::string word1{};
    std::string word2{};

    while (word1 != "QUIT")
    {
        command.clear();
        std::cout << "What should I do? :: ";
        std::getline(std::cin, command);
        std::cout << "\nYour raw command was " << command << '\n';
        word1.clear();
        word2.clear();
        sectionCommand(command, word1, word2);

        if (word1 != "QUIT")
        {
            parser(word1, word2, pl);
        }
        else
        {
            menu.mainMenu();
        }
    }
}
