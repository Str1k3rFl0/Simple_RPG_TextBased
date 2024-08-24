#ifndef CASINO_H
#define CASINO_H

#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <thread>
#include <chrono>
#include <string>
#include <vector>
#include <ctime>

#define RESET "\033[0m"
#define GREEN "\033[32m"

#include "Player.h"

class Casino
{
private:
    double totalMoney{};
    double bet{};
    //std::string plums{};
    //std::string melons{};
    //std::string grapes{};
    //std::string lemons{};
    //std::string cherries{};

    int chDog{};

    std::vector<std::string> symbols { "plums", "melons", "grapes", "lemons", "cherries", "wild", "scatter" };
    std::vector<int> deck{};
    std::vector<int> redNums { 1, 3, 5, 7, 9, 12, 14, 16, 18, 19, 21, 23, 25, 27, 30, 32, 34, 36 };

    std::vector<std::vector<char>> board
    {
        { ' ', ' ', ' ' },
        { ' ', ' ', ' ' },
        { ' ', ' ', ' ' }
    };

    Player pl{};

public:
    Casino(Player& pl);
    Casino(double money);

    // Functions for Slot Machine
    void startGame();
    std::string getSymbol(int slot);
    int getRandSymIndex();
    void slotMachine(int& slot1, int& slot2, int& slot3);
    void slotMachine3x3();
    void slotMachine6x6();
    void calcTotalMoney(int& slot1, int& slot2, int& slot3);
    double calcWin(const std::vector<std::vector<int>>& matrix);

    // Functions for Dog Race
    void startDogRace();
    void dogRace();
    void printDogTrack(const std::vector<int>& dogs) const;
    double calWinnings(int pos) const;

    // Functions for BlackJack
    void initDeck();
    int drawCard();
    int calcHandValue(const std::vector<int>& hand) const;
    void placeBet();
    void playBlackJack();

    // Functions for Dice Game
    void playDiceGame();

    // Functions for Roulette Game
    void playRoullete();
    std::string getColor(int number);
    void calcRouletteWin(int betType, int betCh, int result);

    // Functions for Tic-Tac-Toe
    void playTicTacToe();
    void printBoard();
    bool isWinner(char player);
    bool isBoardFull();
    void playerMove();
    void aiMove();
    void resetBoard();
    void calcTicTacToeWin(char result);

    // Functions for War Cards Game
    void startWar();
    int drawWarCard();
    void calcWarResult(int plCard, int dlCard);

    // Functions for High Low Game
    void playHighLow();
    int drawHGCard();
    double calcMultiplier(int corrGuess);
    bool askToContinue();

    // Functions for Loto 6/49
    void playLotto();
    std::vector<int> genWinNums();
    void checkWinNums(const std::vector<int>& plNumbers, const std::vector<int>& winNumbers);
    double calcLotoWin(int corrNumbers);

    // Functions for Lucky Six
    void playLuckySix();
    std::vector<int> genLuckySixNums();
    void checkLuckySixNums(const std::vector<int>& plNums, const std::vector<int>& drNums);
    double calcLuckySixWin(int lastBallPos);
    void displayNums(const std::vector<int>& plNums, const std::vector<int>& drNums,
                     int position, const std::string& label);

    double getTotalMoney() const { return totalMoney; }
    void setTotalMoney(double money) { totalMoney = money; }

    std::string centerString(const std::string& str, int width);

};

#endif // CASINO_H
