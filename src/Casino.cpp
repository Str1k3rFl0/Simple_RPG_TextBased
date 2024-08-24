#include "Casino.h"

Casino::Casino(Player& pl)
    : totalMoney { 0 }
    , bet { 0 }
    , pl { pl }
{
    srand(static_cast<unsigned int>(time(nullptr)));
}

Casino::Casino(double money)
    : totalMoney { money }
{
    srand(static_cast<unsigned int>(time(nullptr)));
    initDeck();
}

void Casino::startGame()
{
    std::string option{};
    int op{};

    do
    {
        system("cls");

        std::cout << "\nTotal balance: " << totalMoney << " coins\n";
        std::cout << "Choose Slot Machine:\n";
        std::cout << "[1] Slot Machine 3 Rolls\n";
        std::cout << "[2] Slot Machine 9 Rolls\n";
        std::cout << "[3] Slot Machine 36 Rolls\n";
        std::cout << "[4] Dog Race\n";
        std::cout << "[5] Roulette Game\n";
        std::cout << "[6] BlackJack\n";
        std::cout << "[7] Dice Game\n";
        std::cout << "[8] Tic-Tac-Toe\n";
        std::cout << "[9] War Card Game\n";
        std::cout << "[10] High Low Card Game\n";
        std::cout << "[11] Loto 6/49\n";
        std::cout << "[12] LUCKY SIX\n";
        std::cout << "[0] Go back\n";
        std::cout << "Enter your choice: ";
        std::cin >> op;

        switch (op)
        {
            case 1:
                {
                    std::cout << "\nEnter your bet: ";
                    std::cin >> bet;
                    if (bet > totalMoney)
                    {
                        std::cout << "Your bet is larger than your current balance. Try again.\n";
                        continue;
                    }
                    int slot1 { rand() % 5 + 1 };
                    int slot2 { rand() % 5 + 1 };
                    int slot3 { rand() % 5 + 1 };
                    slotMachine(slot1, slot2, slot3);
                    calcTotalMoney(slot1, slot2, slot3);
                    break;
                }

            case 2:
                std::cout << "\nEnter your bet: ";
                std::cin >> bet;
                if (bet > totalMoney)
                {
                    std::cout << "Your bet is larger than your current balance. Try again.\n";
                    continue;
                }
                slotMachine3x3();
                break;

            case 3:
                std::cout << "\nEnter your bet: ";
                std::cin >> bet;
                if (bet > totalMoney)
                {
                    std::cout << "Your bet is larger than your current balance. Try again.\n";
                    continue;
                }
                slotMachine6x6();
                break;

            case 4:
                startDogRace();
                break;

            case 5:
                playRoullete();
                break;

            case 6:
                playBlackJack();
                break;

            case 7:
                playDiceGame();
                break;

            case 8:
                playTicTacToe();
                break;

            case 9:
                startWar();
                break;

            case 10:
                playHighLow();
                break;

            case 11:
                playLotto();
                break;

            case 12:
                playLuckySix();
                break;

            case 0: break;

            default:
                std::cout << "Invalid choice!\n";
                break;
        }

        if (totalMoney == 0)
        {
            std::cout << "\nYou are out of money!\n";
            break;
        }

        std::cout << "\nDo you want to play again? (yes/no): ";
        std::cin >> option;

    } while (option != "no");
}

std::string Casino::getSymbol(int slot)
{
    static const std::vector<std::string> symbols = { "plums", "melons", "grapes", "lemons", "cherries", "wild", "scatter" };
    if (slot < 1 || slot > symbols.size())
    {
        std::cerr << "Invalid slot value: " << slot << std::endl;
        return "invalid";
    }
    return symbols[slot - 1];
}

int Casino::getRandSymIndex()
{
    static const std::vector<double> prob { 0.2, 0.2, 0.2, 0.2, 0.1, 0.05, 0.01 };
    double randValue { static_cast<double>(rand()) / RAND_MAX };
    double cmtProbability { 0.0 };
    for (std::size_t i { 0 }; i < prob.size(); ++i)
    {
        cmtProbability += prob[i];
        if (randValue <= cmtProbability)
        {
            return i;
        }
    }

    return prob.size() - 1;
}

std::string Casino::centerString(const std::string& str, int width)
{
    int padding { width - static_cast<int>(str.size()) };
    int padLeft { padding / 2 };
    int padRight { padding - padLeft };
    return std::string(padLeft, ' ') + str + std::string(padRight, ' ');
}

void Casino::slotMachine(int& slot1, int& slot2, int& slot3)
{
    /*
    switch (slot1)
    {
        case 1: std::cout << "Dropped: " << plums << '\t'; break;
        case 2: std::cout << "Dropped: " << melons << '\t'; break;
        case 3: std::cout << "Dropped: " << grapes << '\t'; break;
        case 4: std::cout << "Dropped: " << lemons << '\t'; break;
        case 5: std::cout << "Dropped: " << cherries << '\t'; break;
    }

    switch (slot2)
    {
        case 1: std::cout << "Dropped: " << plums << '\t'; break;
        case 2: std::cout << "Dropped: " << melons << '\t'; break;
        case 3: std::cout << "Dropped: " << grapes << '\t'; break;
        case 4: std::cout << "Dropped: " << lemons << '\t'; break;
        case 5: std::cout << "Dropped: " << cherries << '\t'; break;
    }

    switch (slot3)
    {
        case 1: std::cout << "Dropped: " << plums; break;
        case 2: std::cout << "Dropped: " << melons; break;
        case 3: std::cout << "Dropped: " << grapes; break;
        case 4: std::cout << "Dropped: " << lemons; break;
        case 5: std::cout << "Dropped: " << cherries; break;
    }
    std::cout << '\n';
    */
    std::cout << "Dropped: " << getSymbol(slot1) << '\t';
    std::cout << "Dropped: " << getSymbol(slot2) << '\t';
    std::cout << "Dropped: " << getSymbol(slot3) << '\n';
}

void Casino::slotMachine3x3()
{
    const int ROWS { 3 };
    const int COLS { 3 };
    const int slotWidth { 12 };
    std::vector<std::vector<int>> matrix(ROWS, std::vector<int>(COLS));

    for (std::size_t i { 0 }; i < ROWS; ++i)
    {
        for (std::size_t j { 0 }; j < COLS; ++j)
        {
            matrix[i][j] = getRandSymIndex();
        }
    }

    std::vector<bool> winningRows(ROWS, false);
    std::vector<bool> winningCols(COLS, false);
    bool winningDiag1 { true };
    bool winningDiag2 { true };

    for (std::size_t i { 0 }; i < ROWS; ++i)
    {
        bool sameRow { true };
        for (std::size_t j { 1 }; j < COLS; ++j)
        {
            if (matrix[i][j] != matrix[i][0] && matrix[i][j] != 5)
            {
                sameRow = false;
                break;
            }
        }
        winningRows[i] = sameRow;
    }

    for (std::size_t j { 0 }; j < COLS; ++j)
    {
        bool sameCol { true };
        for (std::size_t i { 1 }; i < ROWS; ++i)
        {
            if (matrix[i][j] != matrix[0][j] && matrix[i][j] != 5)
            {
                sameCol = false;
                break;
            }
        }
        winningCols[j] = sameCol;
    }

    for (std::size_t i { 1 }; i < ROWS; ++i)
    {
        if (matrix[i][i] != matrix[0][0] && matrix[i][i] != 5)
        {
            winningDiag1 = false;
        }
        if (matrix[i][COLS - i - 1] != matrix[0][COLS - 1] && matrix[i][COLS - i - 1] != 5)
        {
            winningDiag2 = false;
        }
    }

    double winAmount { calcWin(matrix) };

    std::cout << "+------------+------------+------------+\n";

    for (std::size_t i { 0 }; i < ROWS; ++i)
    {
        std::cout << "|";
        for (std::size_t j { 0 }; j < COLS; ++j)
        {
            std::string centeredSymbol = centerString(symbols[matrix[i][j]], slotWidth);
            bool isWinning = winningRows[i] || winningCols[j] || (i == j && winningDiag1) || (i + j == ROWS - 1 && winningDiag2);

            if (isWinning)
            {
                if (matrix[i][j] == 5)
                {
                    std::cout << "\033[42m" << centeredSymbol << "\033[0m" << "|";
                }
                else
                {
                    std::cout << "\033[43m" << centeredSymbol << "\033[0m" << "|";
                }
            }
            else
            {
                std::cout << centeredSymbol << "|";
            }
        }
        std::cout << "\n";

        if (i != ROWS - 1)
        {
            std::cout << "+------------+------------+------------+\n";
        }
    }

    std::cout << "+------------+------------+------------+\n";

    if (winAmount > 0)
    {
        std::cout << "Congratulation! You've won " << winAmount << " coins.\n";
        totalMoney += winAmount;
    }
    else
    {
        std::cout << "You didn't win anything.\n";
        totalMoney -= bet;
    }

    std::cout << "Your new balance is: " << totalMoney << " coins.\n";

    pl.setMoney(static_cast<int>(totalMoney));
    if (!pl.updateFile("Player.txt"))
    {
        std::cerr << "Failed to update the account file.\n";
    }
}

void Casino::slotMachine6x6()
{
    const int ROWS { 6 };
    const int COLS { 6 };
    const int slotWidth { 12 };
    std::vector<std::vector<int>> matrix(ROWS, std::vector<int>(COLS));

    // Inițializează matricea de simboluri
    for (std::size_t i { 0 }; i < ROWS; ++i)
    {
        for (std::size_t j { 0 }; j < COLS; ++j)
        {
            matrix[i][j] = getRandSymIndex();
        }
    }

    // Verifică câte linii, coloane și diagonale au simboluri câștigătoare
    std::vector<bool> winningRows(ROWS, false);
    std::vector<bool> winningCols(COLS, false);
    bool winningDiag1 { true };
    bool winningDiag2 { true };
    int scatterCount { 0 };

    // Verifică câte `SCATTER` sunt
    for (const auto& row : matrix)
    {
        scatterCount += std::count(row.begin(), row.end(), 6);
    }

    // Verifică rânduri câștigătoare
    for (std::size_t i { 0 }; i < ROWS; ++i)
    {
        bool sameRow { true };
        for (std::size_t j { 1 }; j < COLS; ++j)
        {
            if (matrix[i][j] != matrix[i][0] && matrix[i][j] != 6)
            {
                sameRow = false;
                break;
            }
        }
        winningRows[i] = sameRow;
    }

    // Verifică coloane câștigătoare
    for (std::size_t j { 0 }; j < COLS; ++j)
    {
        bool sameCol { true };
        for (std::size_t i { 1 }; i < ROWS; ++i)
        {
            if (matrix[i][j] != matrix[0][j] && matrix[i][j] != 6)
            {
                sameCol = false;
                break;
            }
        }
        winningCols[j] = sameCol;
    }

    // Verifică diagonale câștigătoare
    for (std::size_t i { 1 }; i < ROWS; ++i)
    {
        if (matrix[i][i] != matrix[0][0] && matrix[i][i] != 6)
        {
            winningDiag1 = false;
        }
        if (matrix[i][COLS - i - 1] != matrix[0][COLS - 1] && matrix[i][COLS - i - 1] != 6)
        {
            winningDiag2 = false;
        }
    }

    // Calcul câștig
    double winAmount { calcWin(matrix) };

    std::cout << "+------------+------------+------------+------------+------------+------------+\n";

    for (std::size_t i { 0 }; i < ROWS; ++i)
    {
        std::cout << "|";
        for (std::size_t j { 0 }; j < COLS; ++j)
        {
            std::string centeredSymbol = centerString(symbols[matrix[i][j]], slotWidth);

            bool isWinning = winningRows[i] || winningCols[j] || (i == j && winningDiag1) || (i + j == ROWS - 1 && winningDiag2);

            if (scatterCount == 3 && matrix[i][j] == 6)
            {
                // Colorează SCATTER
                std::cout << "\033[42m" << centeredSymbol << "\033[0m" << "|";
            }
            else if (isWinning)
            {
                // Colorează fructele câștigătoare
                std::cout << "\033[43m" << centeredSymbol << "\033[0m" << "|"; // Fundal galben pentru fructe câștigătoare
            }
            else
            {
                std::cout << centeredSymbol << "|";
            }
        }
        std::cout << "\n";

        if (i != ROWS - 1)
        {
            std::cout << "+------------+------------+------------+------------+------------+------------+\n";
        }
    }

    std::cout << "+------------+------------+------------+------------+------------+------------+\n";

    if (winAmount > 0)
    {
        std::cout << "Congratulation! You've won " << winAmount << " coins.\n";
        totalMoney += winAmount;
    }
    else
    {
        std::cout << "You didn't win anything.\n";
        totalMoney -= bet;
    }

    std::cout << "Your new balance is: " << totalMoney << " coins.\n";

    pl.setMoney(static_cast<int>(totalMoney));
    if (!pl.updateFile("Player.txt"))
    {
        std::cerr << "Failed to update the account file.\n";
    }
}

void Casino::calcTotalMoney(int& slot1, int& slot2, int& slot3)
{
    double win { 0 };

    if (slot1 == slot2 && slot1 == slot3)
    {
        std::cout << "\nCongratulations! You've won!\n";
        win = { bet * 3 };
        std::cout << "You earned " << win << " coins\n";
    }
    else if (slot1 == slot2 || slot1 == slot3 || slot2 == slot3)
    {
        std::cout << "\nCongratulations! You've won!\n";
        win = { bet * 2 };
        std::cout << "You earned " << win << " coins\n";
    }
    else
    {
        std::cout << "\nYou didn't win anything.\n";
        totalMoney -= bet;
    }

    totalMoney += win;
    std::cout << "Your new balance is: " << totalMoney << " coins\n";

    pl.setMoney(static_cast<int>(totalMoney));
    if (!pl.updateFile("Player.txt"))
    {
        std::cerr << "Failed to updated the account file.\n";
    }
}

double Casino::calcWin(const std::vector<std::vector<int>>& matrix)
{
    double win { 0 };
    const int ROWS { matrix.size() };
    const int COLS { matrix[0].size() };

    for (std::size_t i { 0 }; i < ROWS; ++i)
    {
        bool same { true };
        for (std::size_t j = 1; j < COLS; ++j)
        {
            if (matrix[i][j] != matrix[i][0] && matrix[i][j] != 5)
            {
                same = false;
                break;
            }
        }
        if (same)
        {
            win += bet * 1.5;
        }
    }

    for (std::size_t j { 0 }; j < COLS; ++j)
    {
        bool same { true };
        for (std::size_t i { 1 }; i < ROWS; ++i)
        {
            if (matrix[i][j] != matrix[0][j] && matrix[i][j] != 5)
            {
                same = false;
                break;
            }
        }
        if (same)
        {
            win += bet * 1.5;
        }
    }

    bool sameDiag1 { true };
    bool sameDiag2 { true };

    for (std::size_t i { 1 }; i < ROWS; ++i)
    {
        if (matrix[i][i] != matrix[0][0] && matrix[i][i] != 5)
        {
            sameDiag1 = false;
        }
        if (matrix[i][COLS - i - 1] != matrix[0][COLS - 1] && matrix[i][COLS - i - 1] != 5)
        {
            sameDiag2 = false;
        }
    }

    if (sameDiag1)
    {
        win += bet * 2;
    }
    if (sameDiag2)
    {
        win += bet * 2;
    }

    int scatterCount { 0 };
    for (const auto& row : matrix)
    {
        scatterCount += std::count(row.begin(), row.end(), 6);
    }

    if (scatterCount == 3)
    {
        win += bet * 5;
    }

    return win;
}


// -------------------------//
// ------- DOG-RACE ------- //
// -------------------------//
void Casino::printDogTrack(const std::vector<int>& dogs) const
{
    const int trackLenght { 20 };
    const char trackChar { '=' };
    const char dogChar { '#' };

    for (std::size_t i { 0 }; i < 7; ++i)
    {
        for (std::size_t j { 0 }; j < trackLenght; ++j)
        {
            if (j == dogs[i])
            {
                std::cout << dogChar;
            }
            else
            {
                std::cout << trackChar;
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

double Casino::calWinnings(int pos) const
{
    switch (pos)
    {
        case 1: return bet * 4;
        case 2: return bet * 2;
        case 3: return bet * 1.5;
        default: return 0;
    }
}

void Casino::dogRace()
{
    const int numDogs = 7;
    const int trackLength = 20;
    std::vector<int> dogs(numDogs, 0);
    std::vector<int> finishOrder;
    double winnings = 0;

    for (int i = 0; i < numDogs; ++i)
    {
        dogs[i] = 0;
    }

    std::cout << "Choose your dog (1-7): ";
    int plBetDog;
    std::cin >> plBetDog;

    if (plBetDog < 1 || plBetDog > 7)
    {
        std::cout << "Incorrect number. Try again!\n";
        return;
    }

    std::cout << "How much money you bet?: ";
    std::cin >> bet;

    if (bet <= 0 || bet > totalMoney)
    {
        std::cout << "Not enough money. Try again!\n";
        return;
    }

    bool raceOngoing = true;

    while (raceOngoing) {
        system("cls");
        printDogTrack(dogs);

        for (int i = 0; i < numDogs; ++i)
        {
            if (dogs[i] < trackLength - 1)
            {
                dogs[i] += rand() % 2;
            }

            if (dogs[i] == trackLength - 1 && std::find(finishOrder.begin(), finishOrder.end(), i) == finishOrder.end())
            {
                finishOrder.push_back(i);
                if (finishOrder.size() == numDogs)
                {
                    raceOngoing = false;
                    break;
                }
            }
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    std::cout << "Final List:\n";
    for (size_t i = 0; i < finishOrder.size(); ++i) {
        std::cout << "Place " << (i + 1) << ": Dog " << (finishOrder[i] + 1) << "\n";
    }

    //int winDogIndex = finishOrder.front();
    //int plPos = std::find(finishOrder.begin(), finishOrder.end(), plBetDog - 1) - finishOrder.begin() + 1;

    auto it = std::find(finishOrder.begin(), finishOrder.end(), plBetDog - 1);
    int plPos = (it != finishOrder.end()) ? std::distance(finishOrder.begin(), it) + 1 : 0;

    if (plPos <= 3)
    {
        bet = calWinnings(plPos);
        std::cout << "You win " << bet << " coins!" << '\n';
        totalMoney += bet;
    }
    else
    {
        std::cout << "You lost. You bet was on dog with number " << plBetDog
                  << "\nAnd the winner dog is the number " << (finishOrder.front() + 1) << "." << std::endl;
        totalMoney -= bet;
    }

    std::cout << "Your actual sold is: " << totalMoney << " coins.\n";
}

void Casino::startDogRace()
{
    std::cout << "Dog race!\n";
    dogRace();
}


// ---------------------------//
// ------- BLACK-JACK ------- //
// ---------------------------//
void Casino::initDeck()
{
    deck.clear();

    for (std::size_t i { 2 }; i <= 10; ++i)
    {
        deck.push_back(i);
        deck.push_back(i);
        deck.push_back(i);
        deck.push_back(i);
    }

    for (std::size_t i { 0 }; i < 4; ++i)
    {
        deck.push_back(10); // J
        deck.push_back(10); // Q
        deck.push_back(10); // K
    }

    for (std::size_t i { 0 }; i < 4; ++i)
    {
        deck.push_back(11); // A
    }

    std::random_shuffle(deck.begin(), deck.end());
}

int Casino::drawCard()
{
    if (deck.empty())
    {
        initDeck();
    }
    int card { deck.back() };
    deck.pop_back();
    return card;
}

int Casino::calcHandValue(const std::vector<int>& hand) const
{
    int value { 0 };
    int aceCount { 0 };

    for (int card : hand)
    {
        value += card;
        if (card == 11)
        {
            aceCount++;
        }
    }

    while (value > 21 && aceCount > 0)
    {
        value -= 10;
        aceCount--;
    }

    return value;
}

void Casino::placeBet()
{
    std::cout << "You have " << totalMoney << " coins.\n";
    std::cout << "Place your bet: ";
    std::cin >> bet;

    if (bet <= 0 || bet > totalMoney)
    {
        std::cout << "Invalid bet amount.\n";
        return;
    }
}

void Casino::playBlackJack()
{
    system("cls");

    placeBet();

    std::vector<int> plHand{};
    std::vector<int> dlHand{};

    plHand.push_back(drawCard());
    plHand.push_back(drawCard());
    dlHand.push_back(drawCard());
    dlHand.push_back(drawCard());

    std::cout << "Your hand: ";
    for (int card : plHand)
    {
        std::cout << card << " ";
    }
    std::cout << "(total: " << calcHandValue(plHand) << ")\n";

    std::cout << "Dealer's visible card: " << dlHand[0] << "\n";

    bool plBusted { false };
    while (true)
    {
        std::cout << "Hit or Stand? (h/s): ";
        char ch{};
        std::cin >> ch;

        if (ch == 'h')
        {
            plHand.push_back(drawCard());
            std::cout << "Your hand: ";
            for (int card : plHand)
            {
                std::cout << card << " ";
            }
            std::cout << "(total: " << calcHandValue(plHand) << ")\n";

            if (calcHandValue(plHand) > 21)
            {
                std::cout << "You busted!\n";
                plBusted = true;
                break;
            }
        }
        else if (ch == 's')
        {
            break;
        }
        else
        {
            std::cout << "Invalid choice. Please enter 'h' or 's'.\n";
        }
    }

    if (!plBusted)
    {
        std::cout << "Dealer's hand: ";
        for (int card : dlHand)
        {
            std::cout << card << " ";
        }
        std::cout << "(total: " << calcHandValue(dlHand) << ")\n";

        while (calcHandValue(dlHand) < 17)
        {
            dlHand.push_back(drawCard());
            std::cout << "Dealer draws a card: ";
            for (int card : dlHand)
            {
                std::cout << card << " ";
            }
            std::cout << "(total: " << calcHandValue(dlHand) << ")\n";
        }

        if (calcHandValue(dlHand) > 21)
        {
            std::cout << "Dealer busted! You win!\n";
            totalMoney += bet;
        }
        else
        {
            int plTotal { calcHandValue(plHand) };
            int dlTotal { calcHandValue(dlHand) };

            if (plTotal > dlTotal)
            {
                std::cout << "You win!\n";
                totalMoney += bet;
            }
            else if (plTotal < dlTotal)
            {
                std::cout << "Dealer wins. You lose.\n";
                totalMoney -= bet;
            }
            else
            {
                std::cout << "It's a tie!\n";
            }
        }
    }
    else
    {
        totalMoney -= bet;
    }
}


// --------------------------//
// ------- DICE GAME ------- //
// --------------------------//
void Casino::playDiceGame()
{
    system("cls");

    std::string player { "You" };
    std::string aiPlayer { "AI" };
    char ch{};

    double totalAIMoney { 1000 };

    do
    {
        std::cout << "\nCheck the current sold...";
        Sleep(1000);
        std::cout << '\n';
        std::cout << player << " have " << totalMoney << " coins.\n";
        std::cout << aiPlayer << " have " << totalAIMoney << " coins.\n";

        if (totalMoney <= 0)
        {
            std::cout << '\n' << player << " have no money left.\n";
            std::cout << aiPlayer << " win and he have a total of " << totalAIMoney << " coins.\n";
            break;
        }
        else if (totalAIMoney <= 0)
        {
            std::cout << '\n' << aiPlayer << " have no money left.\n";
            std::cout << player << " win and he have a total of " << totalMoney << " coins.\n";
            break;
        }
        else
        {
            std::cout << '\n' << player << " have current sold: " << totalMoney << " coins.\n";
            std::cout << aiPlayer << " have current sold: " << totalAIMoney << " coins.\n";
        }

        std::cout << "\nBoth player must have the same bet to play!\n";
        std::cout << player << " place your bet: ";
        std::cin >> bet;

        double betAI { bet };
        std::cout << aiPlayer << " placed the bet: " << betAI << " coins.\n";

        int dice1 { rand() % 6 + 1 };
        int dice2 { rand() % 6 + 1 };

        std::cout << '\n' << player << " throw the dice...\n";
        Sleep(1500);
        std::cout << "Dropped: " << dice1 << '\n';

        std::cout << '\n' << aiPlayer << " throw the dice...\n";
        Sleep(1500);
        std::cout << "Dropped: " << dice2 << '\n';

        if (dice1 > dice2)
        {
            std::cout << player << " win!!!\n";
            totalMoney += betAI;
            totalAIMoney -= bet;
        }
        else if (dice1 < dice2)
        {
            std::cout << aiPlayer << " win!!!\n";
            totalAIMoney += bet;
            totalMoney -= betAI;
        }
        else
        {
            std::cout << '\n' << "It was equal!\n";
        }

        std::cout << "\nYou want to play again? (y/n): ";
        std::cin >> ch;
    } while (ch == 'y' || ch == 'Y');

    std::cout << "Thanks for playing!\n";
}

// -------------------------//
// ------- ROULETTE ------- //
// -------------------------//
std::string Casino::getColor(int number)
{
    if (number == 0 || number == 37)
    {
        return "Green";
    }
    else if (std::find(redNums.begin(), redNums.end(), number) != redNums.end())
    {
        return "Red";
    }
    else
    {
        return "Black";
    }
}

void Casino::calcRouletteWin(int betType, int betCh, int result)
{
    if (betType == 1)
    {
        if (betCh == result)
        {
            std::cout << "You win! Exact number!\n";
            totalMoney += bet * 35;
        }
        else
        {
            std::cout << "You lost. The extract number was " << result << ".\n";
            totalMoney -= bet;
        }
    }
    else if (betType == 2)
    {
        std::string resultColor { getColor(result) };
        std::string betColor { (betCh == 1) ? "Red" : (betCh == 2) ? "Black" : "Green" };

        if (resultColor == betColor)
        {
            std::cout << "You win! The correct color!\n";
            if (betColor == "Green")
            {
                totalMoney += bet * 14;
            }
            else
            {
                totalMoney += bet * 2;
            }
        }
        else
        {
            std::cout << "You lose. The extract color was " << resultColor << ".\n";
            totalMoney -= bet;
        }
    }
    else if (betType == 3)
    {
        if ((betCh == 1 && result >= 1 && result <= 18) ||
            (betCh == 2 && result >= 19 && result <= 36))
        {
            std::cout << "You win! The correct interval!\n";
            totalMoney += bet * 2;
        }
        else
        {
            std::cout << "You lost. The extract number was " << result << ".\n";
            totalMoney -= bet;
        }
    }
}

void Casino::playRoullete()
{
    srand(time(0));
    int betType{};
    int betCh{};

    system("cls");

    std::cout << "\nTotal balance: " << totalMoney << " coins\n";
    std::cout << "Choose the type for the bet:\n";
    std::cout << "[1] Bet for exact number\n";
    std::cout << "[2] Bet on color (1 = Red, 2 = Black, 3 = Green)\n";
    std::cout << "[3] Bet on interval (1 = 1-18, 2 = 19-36)\n";
    std::cout << "Enter your choice: ";
    std::cin >> betType;

    std::cout << "How much money do you want to bet?: ";
    std::cin >> bet;

    if (bet > totalMoney)
    {
        std::cout << "The bet is higher than your current sold!\n";
        return;
    }

    switch (betType)
    {
        case 1:
            {
                std::cout << "Choose a number between 0 and 36 (or 37 for 00): ";
                std::cin >> betCh;
                if (betCh < 0 || betCh > 37)
                {
                    std::cout << "Invalid number!\n";
                    return;
                }
                break;
            }

        case 2:
            {
                std::cout << "Choose color (1 = Red, 2 = Black, 3 = Green): ";
                std::cin >> betCh;
                if (betCh < 1 || betCh > 3)
                {
                    std::cout << "Invalid color!\n";
                    return;
                }
                break;
            }

        case 3:
            {
                std::cout << "Choose from interval (1 = 1-18, 2 = 19-36): ";
                std::cin >> betCh;

                if (betCh < 1 || betCh > 2)
                {
                    std::cout << "Invalid interval!\n";
                    return;
                }
                break;
            }

        default: std::cout << "Invalid option!\n"; break;
    }

    int result = rand() % 38;
    std::cout << "The wheel turned! The extract number is: " << (result == 37 ? "00" : std::to_string(result)) << "\n";

    calcRouletteWin(betType, betCh, result);

    std::cout << "Your current sold is " << totalMoney << " coins.\n";
}


// ----------------------------//
// ------- TIC-TAC-TOE ------- //
// ----------------------------//
void Casino::printBoard()
{
    std::cout << '\n';
    for (std::size_t i { 0 }; i < 3; i++)
    {
        std::cout << " " << board[i][0] << " | " << board[i][1] << " | " << board[i][2] << '\n';
        if (i < 2)
        {
            std::cout << "---|---|---\n";
        }
    }

    std::cout << '\n';
}

bool Casino::isWinner(char player)
{
    for (std::size_t i { 0 }; i < 3; i++)
    {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
        {
            return true;
        }
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player)
        {
            return true;
        }
    }

    if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
    {
        return true;
    }
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
    {
        return true;
    }

    return false;
}

bool Casino::isBoardFull()
{
    for (std::size_t i { 0 }; i < 3; i++)
    {
        for (std::size_t j { 0 }; j < 3; j++)
        {
            if (board[i][j] == ' ')
            {
                return false;
            }
        }
    }

    return true;
}

void Casino::playerMove()
{
    int row{};
    int col{};

    std::cout << "Choose row (1-3) and column (1-3), with space between numbers: ";
    std::cin >> row >> col;

    while (row < 1 || row > 3 || col < 1 || col > 3 || board[row - 1][col - 1] != ' ')
    {
        std::cout << "Invalid movement! Choose another row and column: ";
        std::cin >> row >> col;
    }

    board[row - 1][col - 1] = 'X';
}

void Casino::aiMove()
{
    for (std::size_t i = 0; i < 3; i++)
    {
        for (std::size_t j = 0; j < 3; j++)
        {
            if (board[i][j] == ' ')
            {
                board[i][j] = 'O';
                if (isWinner('O'))
                {
                    std::cout << "The AI choose the move (" << i+1 << ", " << j+1 << ")\n";
                    return; // AI win!
                }
                board[i][j] = ' ';
            }
        }
    }

    for (std::size_t i = 0; i < 3; i++)
    {
        for (std::size_t j = 0; j < 3; j++)
        {
            if (board[i][j] == ' ')
            {
                board[i][j] = 'X';
                if (isWinner('X'))
                {
                    board[i][j] = 'O';
                    std::cout << " The AI block position (" << i+1 << ", " << j+1 << ")\n";
                    return;
                }
                board[i][j] = ' ';
            }
        }
    }

    srand(time(0));
    int row{}, col{};

    do
    {
        row = rand() % 3;
        col = rand() % 3;
    } while (board[row][col] != ' ');

    std::cout << "The AI choose the move (" << row+1 << ", " << col+1 << ")\n";
    board[row][col] = 'O';
}

void Casino::resetBoard()
{
    board = { {' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '} };
}

void Casino::calcTicTacToeWin(char result)
{
    if (result == 'X')
    {
        std::cout << "Congratulation! You win!\n";
        totalMoney += bet * 2.5;
    }
    else if (result == 'O')
    {
        std::cout << "The AI win! You lost!\n";
        totalMoney -= bet;
    }
    else
    {
        std::cout << "Equal.\n";
    }

    std::cout << "You current sold is: " << totalMoney << " coins.\n";
}

void Casino::playTicTacToe()
{
    system("cls");
    char winner { ' ' };
    resetBoard();

    std::cout << "\nTotal Balance: " << totalMoney << " coins.\n";
    std::cout << "Enter your bet: ";
    std::cin >> bet;

    if (bet > totalMoney)
    {
        std::cout << "Your bet is higher than your current sold!\n";
        return;
    }

    while (!isBoardFull())
    {
        printBoard();
        playerMove();

        if (isWinner('X'))
        {
            winner = 'X';
            break;
        }

        if (!isBoardFull())
        {
            aiMove();
            if (isWinner('O'))
            {
                winner = 'O';
                break;
            }
        }
    }

    if (winner == ' ')
    {
        std::cout << "Its equal!\n";
    }

    printBoard();
    calcTicTacToeWin(winner);
}


// ------------------------------//
// ------- WAR CARD GAME ------- //
// ------------------------------//
int Casino::drawWarCard()
{
    return rand() % 13 + 1;
}

void Casino::calcWarResult(int plCard, int dlCard)
{
    if (plCard > dlCard)
    {
        std::cout << "\nYou win!\n";
        totalMoney += bet;
    }
    else if (plCard < dlCard)
    {
        std::cout << "\nDealer wins!\n";
        totalMoney -= bet;
    }
    else
    {
        std::cout << "\nIt's a tie!\n";
    }

    std::cout << "\nCurrent balance: " << totalMoney << " coins.\n";
}

void Casino::startWar()
{
    system("cls");

    std::cout << "\nThis game is about who have the bigger number card\n";
    std::cout << "\nEnter your bet: ";
    std::cin >> bet;
    if (bet > totalMoney)
    {
        std::cout << "Your bet is larger than your current sold. Try again!\n";
        return;
    }

    int plCard { drawWarCard() };
    int dlCard { drawWarCard() };

    std::cout << "\nYou drew a card with value: " << plCard << '\n';
    std::cout << "Dealer drew a card with value: " << dlCard << '\n';

    calcWarResult(plCard, dlCard);
}


// -----------------------------//
// ------ HIGH LOW GAME ------- //
// -----------------------------//
int Casino::drawHGCard()
{
    return std::rand() % 13 + 1;
}

double Casino::calcMultiplier(int corrGuess)
{
    return 1.25 + ((corrGuess / 5 - 1) * .50);
}

bool Casino::askToContinue()
{
    std::string response{};
    std::cout << "Do you want to continue guessing? (yes/no): ";
    std::cin >> response;
    return response == "yes";
}

void Casino::playHighLow()
{
    std::cout << "\n *** High-Low Card Game ***\n";

    std::cout << "\nNumber of cards: 1-13\n";
    std::cout << "\nEnter your bet: ";
    std::cin >> bet;
    if (bet > totalMoney)
    {
        std::cout << "Your bet is larger than your current balance. Try again!\n";
        return;
    }

    int currCard { drawHGCard() };
    int corrGuess { 0 };

    while (true)
    {
        std::cout << "\nCurrent card value: " << currCard << '\n';
        char guess{};
        std::cout << "Will the next card be higher (h) or lower (l)?: ";
        std::cin >> guess;

        int nextCard { drawHGCard() };
        std::cout << "Next card value: " << nextCard << '\n';

        if (nextCard == currCard)
        {
            std::cout << "The next card is the same as the current card. Considered a correct guess.\n";
            corrGuess++;
        }
        else if ((guess == 'h' && nextCard > currCard) ||
                (guess == 'l' && nextCard < currCard))
        {
            corrGuess++;
            currCard = nextCard;

            if (corrGuess % 5 == 0)
            {
                double multiplier { calcMultiplier(corrGuess) };
                double winAmount { bet * multiplier };
                totalMoney += winAmount;
                std::cout << "Congratulation! You guessed correctly " << corrGuess << " times.\n";
                std::cout << "You won " << winAmount << " coins.\n";

                if(!askToContinue())
                {
                    std::cout << "Game over. Total correct guesses: " << corrGuess << " times.\n";
                    break;
                }
            }
        }
        else
        {
            std::cout << "Wrong guess! Game over.\n";
            std::cout << "Total correct guesses: " << corrGuess << '\n';
            totalMoney -= bet;
            break;
        }
    }
}


// ------------------------- //
// ------- LOTO 6/49 ------- //
// ------------------------- //

std::vector<int> Casino::genWinNums()
{
    std::vector<int> nums(49);
    for (std::size_t i { 0 }; i < 49; ++i)
    {
        nums[i] = i + 1;
    }

    std::random_shuffle(nums.begin(), nums.end());

    std::vector<int> winNums(nums.begin(), nums.begin() + 6);
    std::sort(winNums.begin(), winNums.end());
    return winNums;
}

void Casino::checkWinNums(const std::vector<int>& plNumbers, const std::vector<int>& winNumbers)
{
    int corrNums { 0 };

    std::cout << "\nYour numbers: ";
    for (int num : plNumbers)
    {
        if (std::find(winNumbers.begin(), winNumbers.end(), num) != winNumbers.end())
        {
            std::cout << "\033[32m" << num << " \033[0m";
            corrNums++;
        }
        else
        {
            std::cout << num << " ";
        }
    }

    std::cout << "\n\nYou guessed " << corrNums << " number(s) correctly.\n";

    if (corrNums >= 4)
    {
        double winnings { calcLotoWin(corrNums) };
        totalMoney += winnings;
        std::cout << "Congratulations! You won " << winnings << " coins.\n";
    }
    else
    {
        totalMoney -= bet;
        std::cout << "Sorry, you did not win. Better luck next time!\n";
    }

    std::cout << "Total balance: " << totalMoney << " coins\n";
}

double Casino::calcLotoWin(int corrNumbers)
{
    switch (corrNumbers)
    {
        case 4: return bet * 2.25;
        case 5: return bet * 4;
        case 6: return bet * 35;
        default: return 0;
    }
}

void Casino::playLotto()
{
    std::cout << "\n *** Loto 6/49 *** \n";

    std::cout << "\nEnter your bet: ";
    std::cin >> bet;
    if (bet > totalMoney)
    {
        std::cout << "Your bet is higher than your current balance. Try again!\n";
        return;
    }

    std::vector<int> plNums(6);
    std::cout << "\nEnter your 6 numbers (between 1 and 49): ";
    for (int& num : plNums)
    {
        std::cin >> num;
        while (num < 1 || num > 49)
        {
            std::cout << "Invalid number! Please enter a number between 1 and 49: ";
            std::cin >> num;
        }
    }

    std::vector<int> winNums { genWinNums() };

    std::cout << "\nWinning numbers: ";
    for (int num : winNums)
    {
        std::cout << "\033[32m" << num << " \033[0m";
    }

    checkWinNums(plNums, winNums);
}


// ------------------------- //
// ------- LUCKY SIX ------- //
// ------------------------- //

std::vector<int> Casino::genLuckySixNums()
{
    std::vector<int> nums(48);
    for (std::size_t i { 0 }; i < 48; ++i)
    {
        nums[i] = i + 1;
    }

    std::random_shuffle(nums.begin(), nums.end());

    std::vector<int> drNums(nums.begin(), nums.begin() + 35);
    return drNums;
}

void Casino::checkLuckySixNums(const std::vector<int>& plNums, const std::vector<int>& drNums)
{
    int corrNums { 0 };
    int lastBallPos { 0 };
    std::vector<bool> foundNums(6, false);

    std::cout << "\nFirst 5 balls: ";
    for (std::size_t i { 0 }; i < 5; ++i)
    {
        displayNums(plNums, drNums, i, "");
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    std::vector<int> firstWin { 10000, 7500, 5000, 2500, 1000, 500, 300, 200, 100 };
    for (std::size_t i { 5 }; i < 14; ++i)
    {
        displayNums(plNums, drNums, i, std::to_string(firstWin[i - 5]) + ": ");
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    std::cout << "\nRemaining balls (80-10): ";
    std::vector<int> secondWin { 80, 60, 50, 45, 40, 35, 30, 25, 20, 16, 13, 10 };
    for (std::size_t i { 14 }; i < 26; ++i)
    {
        displayNums(plNums, drNums, i, std::to_string(secondWin[i-14]) + ": ");
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    std::cout << "\nRemaining balls (9-1): ";
    std::vector<int> thirdWin { 9, 8, 7, 6, 5, 4, 3, 2, 1 };
    for (std::size_t i { 26 }; i < 35; ++i)
    {
        displayNums(plNums, drNums, i, std::to_string(thirdWin[i-26]) + ": ");
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    for (std::size_t i { 0 }; i < drNums.size(); ++i)
    {
        for (std::size_t j { 0 }; j < plNums.size(); ++j)
        {
            if (plNums[j] == drNums[i] && !foundNums[j])
            {
                corrNums++;
                foundNums[j] = true;
                lastBallPos = i + 1;
                if (corrNums == 6)
                {
                    break;
                }
            }
        }
        if (corrNums == 6);
    }

    if (corrNums == 6)
    {
        double wins { calcLuckySixWin(lastBallPos) };
        totalMoney += wins;
        std::cout << "\nCongratulations! You won " << wins << " coins.\n";
        std::cout << "Your last number was drawn at positon: " << lastBallPos << "\n";
    }
    else
    {
        totalMoney -= bet;
        std::cout << "\nSorry, you did not win. Better luck next time!\n";
    }

    std::cout << "Total balance: " << totalMoney << " coins.\n";
}

void Casino::displayNums(const std::vector<int>& plNums, const std::vector<int>& drNums,
        int position, const std::string& label)
{
    bool isHit { std::find(plNums.begin(), plNums.end(), drNums[position]) != plNums.end() };

    if (isHit)
    {
        std::cout << label << GREEN << drNums[position] << RESET << " ";
    }
    else
    {
        std::cout << label << drNums[position] << " ";
    }
}

double Casino::calcLuckySixWin(int lastBallPos)
{
    switch (lastBallPos)
    {
        case 1: case 2: case 3: case 4: case 5: case 6:
            return bet * 10000;
        case 7:
            return bet * 7500;
        case 8:
            return bet * 5000;
        case 9:
            return bet * 2500;
        case 10:
            return bet * 1000;
        case 11:
            return bet * 500;
        case 12:
            return bet * 300;
        case 13:
            return bet * 200;
        case 14:
            return bet * 100;
        case 15:
            return bet * 80;
        case 16:
            return bet * 60;
        case 17:
            return bet * 50;
        case 18:
            return bet * 45;
        case 19:
            return bet * 40;
        case 20:
            return bet * 35;
        case 21:
            return bet * 30;
        case 22:
            return bet * 25;
        case 23:
            return bet * 20;
        case 24:
            return bet * 16;
        case 25:
            return bet * 13;
        case 26:
            return bet * 10;
        case 27:
            return bet * 9;
        case 28:
            return bet * 8;
        case 29:
            return bet * 7;
        case 30:
            return bet * 6;
        case 31:
            return bet * 5;
        case 32:
            return bet * 4;
        case 33:
            return bet * 3;
        case 34:
            return bet * 2;
        case 35:
            return bet * 1;   // Poziția 35 -> *1
        default:
            return 0;
    }
}

void Casino::playLuckySix()
{
    system("cls");
    std::cout << "\n ----- LUCKY SIX ----- \n";

    std::cout << "\nEnter your bet: ";
    std::cin >> bet;

    if (bet > totalMoney)
    {
        std::cout << "Your bet is higher than your current balance. Try again!\n";
        return;
    }

    std::vector<int> plNums(6);
    std::cout << "\nEnter your 6 numbers (1-48): ";
    for (int& num : plNums)
    {
        std::cin >> num;
        while (num < 1 || num > 48)
        {
            std::cout << "Invalid number! Please enter a number between 1 and 48: ";
            std::cin >> num;
        }
    }

    std::vector<int> drNums { genLuckySixNums() };
    checkLuckySixNums(plNums, drNums);
}
