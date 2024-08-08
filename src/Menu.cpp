#include "Menu.h"

void SpecialFunc::setColor(unsigned char color)
{
    SetConsoleTextAttribute( GetStdHandle ( STD_OUTPUT_HANDLE ), color );
}

void SpecialFunc::gotoxy(int x, int y)
{
    static HANDLE h = nullptr;
    if (!h)
    {
        h = GetStdHandle( STD_OUTPUT_HANDLE );
    }
    COORD c = { x, y };
    SetConsoleCursorPosition( h, c );
}

void SpecialFunc::marginsPattern(int x, int y)
{
    for (int i { 0 }; i < x; i++)
    {
        for (int j { 0 }; j < y; j++)
        {
            if (i <= 1 || i >= x - 2)
            {
                std::cout << '*';
            }
            else
            {
                if (j <= 1 || j >= y - 2)
                {
                    std::cout << '*';
                }
                else
                {
                    std::cout << ' ';
                }
            }
        }
        std::cout << '\n';
    }
}

void SpecialFunc::credits()
{
    system("cls");
    marginsPattern(29, 120);
    gotoxy(37, 11);
    std::cout << "This mini-RPG project was made by Str1k3rFl0" << std::endl;
    gotoxy(2, 26);
    std::cout << "Press ENTER to go to main menu...";
    _getch();
}

void SpecialFunc::instructions()
{
    system("cls");
    marginsPattern(29, 120);
    gotoxy(2, 4);
    std::cout << "Type NORTH -> to move to the North" << std::endl;
    gotoxy(2, 5);
    std::cout << "Type SOUTH -> to move to the South" << std::endl;
    gotoxy(2, 6);
    std::cout << "Type WEST -> to move to the West" << std::endl;
    gotoxy(2, 7);
    std::cout << "Type EAST -> to move to the East" << std::endl;
    gotoxy(2, 8);
    std::cout << "Type LOOK -> to know what locations are around you." << std::endl;
    gotoxy(2, 9);
    std::cout << "Type STATS -> to show player stats." << std::endl;
    gotoxy(2, 10);
    std::cout << "Type OPTIONS -> to show all verbs." << std::endl;
    gotoxy(2, 11);
    std::cout << "TYPE QUIT -> to quit the game and return to main menu." << std::endl;

    gotoxy(2, 26);
    std::cout << "Press ENTER to go to main menu...";
    _getch();
}

void Menu::playerMenu(Player& pl)
{
    char ch{};
    const char* fileName { "Player.txt" };

    do
    {
        system("cls");
        HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );
        SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);

        marginsPattern(29, 120);

        gotoxy(45, 6);
        std::cout << "============================";
        gotoxy(45, 8);
        std::cout << "         PLAYER MENU        ";
        gotoxy(45, 10);
        std::cout << "============================";
        gotoxy(50, 14);
        setColor( 0x0A );
        std::cout << "[1] CREATE ACCOUNT" << std::endl;
        gotoxy(50, 15);
        setColor( 0x07 );
        std::cout << "[2] SHOW ACCOUNT" << std::endl;
        gotoxy(50, 16);
        setColor( 0x04 );
        std::cout << "[3] MODIFY ACCOUNT" << std::endl;
        gotoxy(50, 17);
        setColor( 0x0D );
        std::cout << "[4] DELETE ACCOUNT" << std::endl;
        gotoxy(50, 18);
        setColor( 0x0B );
        std::cout << "[0] BACK TO MAIN MENU" << std::endl;
        gotoxy(2, 26);
        std::cout << "Choose an option :: ";
        std::cin >> ch;
        system("cls");
        switch (ch)
        {
            case '1': pl.createAccount(fileName); break;
            case '2': pl.showAccount(fileName); break;
            case '3': pl.modifyAccount(fileName); break;
            case '4': pl.deleteAccount(fileName); break;
            case '0': mainMenu(); break;
            default: std::cout << '\a';
        }
    } while (ch != '0');
}

void Menu::mainMenu()
{
    char ch{};
    const char* fileName { "Player.txt" };

    Player pl{};
    Map map{};

    do
    {
        system("cls");
        HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );
        SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);

        marginsPattern(29, 120);

        gotoxy(45, 6);
        std::cout << "=====================================";
        gotoxy(45, 8);
        std::cout << "             RPG HIPODROM            ";
        gotoxy(45, 10);
        std::cout << "=====================================";
        gotoxy(56, 14);
        setColor( 0x0A );
        std::cout << "[1] PLAYER MENU" << std::endl;
        gotoxy(56, 15);
        setColor( 0x07 );
        std::cout << "[2] PLAY GAME" << std::endl;
        gotoxy(56, 16);
        setColor( 0x0D );
        std::cout << "[3] CREDITS" << std::endl;
        gotoxy(56, 17);
        setColor( 0x03 );
        std::cout << "[4] INSTRUCTIONS" << std::endl;
        gotoxy(56, 18);
        setColor( 0x0B );
        std::cout << "[0] EXIT" << std::endl;
        gotoxy(2, 26);
        std::cout << "Choose an option :: ";
        std::cin >> ch;
        system("cls");
        switch (ch)
        {
            case '1': playerMenu(pl); break;
            case '2': map.playGame(); break;
            case '3': credits(); break;
            case '4': instructions(); break;
            case '0': exit(0);
            default: std::cout << '\a';
        }
    } while (ch != '0');
}
