#include "Stadium.h"

void FootballTeam::addPlayer(const FootballPlayer& player)
{
    if (players.size() < 11)
    {
        players.push_back(player);
    }
}

FootballPlayer FootballTeam::getRandPl() const
{
    int index { rand() % players.size() };
    return players[index];
}

void FootballTeam::displayTeam() const
{
    std::cout << "Team: " << name << "\nPlayers\n";
    for (const auto& player : players)
    {
        player.display();
    }
}

void FootballGame::playMatch()
{
    system("cls");

    std::cout << "Minute 1: The match has started!\n";
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    for (std::size_t mins { 2 }; mins <= 90; ++mins)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));

        int event { rand() % 15 }; // Change to 15 to lower the chances of scoring

        if (event == 0)
        {
            FootballPlayer player = teamA.getRandPl();
            std::vector<std::string> passMessages {
                player.getName() + " (#" + std::to_string(player.getShirtNr()) + ") passes to a teammate.",
                player.getName() + " (#" + std::to_string(player.getShirtNr()) + ") makes a quick pass forward.",
                player.getName() + " (#" + std::to_string(player.getShirtNr()) + ") sends a long ball across the field."
            };
            std::cout << "Minute " << mins << ": " << passMessages[rand() % passMessages.size()] << "\n";
        }
        else if (event == 1)
        {
            FootballPlayer player = teamB.getRandPl();
            std::vector<std::string> shotMessages {
                player.getName() + " (#" + std::to_string(player.getShirtNr()) + ") takes a shot on goal!",
                player.getName() + " (#" + std::to_string(player.getShirtNr()) + ") attempts a long-range shot!",
                player.getName() + " (#" + std::to_string(player.getShirtNr()) + ") fires the ball towards the net!"
            };
            std::cout << "Minute " << mins  << ": " << shotMessages[rand() % shotMessages.size()] << "\n";
        }
        else if (event == 2)
        {
            FootballPlayer player = teamA.getRandPl();
            std::cout << "Minute " << mins << ": Corner for " << teamA.getName() << ". " << player.getName()
                      << " is preparing to take the corner.\n";
        }
        else if (event == 3)
        {
            FootballPlayer player = teamB.getRandPl();
            std::cout << "Minute " << mins << ": Handball by " << player.getName() << ". Free kick awarded to " << teamA.getName() << ".\n";
        }
        else if (event == 4)
        {
            FootballPlayer scorer = teamA.getRandPl();
            std::cout << "Minute " << mins << ": GOOOAL! " << scorer.getName() << " (#" << scorer.getShirtNr()
                      << ", " << scorer.getPosition() << ") scores for " << teamA.getName() << "!\n";
            teamAGoals++;
        }
        else if (event == 5)
        {
            FootballPlayer scorer = teamB.getRandPl();
            std::cout << "Minute " << mins << ": GOOOAL! " << scorer.getName() << " (#" << scorer.getShirtNr()
                      << ", " << scorer.getPosition() << ") scores for " << teamB.getName() << "!\n";
            teamBGoals++;
        }
        else if (event == 6)
        {
            FootballPlayer player = teamA.getRandPl();
            std::vector<std::string> yellowCardMessages {
                player.getName() + " (#" + std::to_string(player.getShirtNr()) + ") receives a yellow card for a reckless tackle.",
                player.getName() + " (#" + std::to_string(player.getShirtNr()) + ") is shown a yellow card for time-wasting.",
                player.getName() + " (#" + std::to_string(player.getShirtNr()) + ") gets a yellow card for dissent."
            };
            std::cout << "Minute " << mins << ": " << yellowCardMessages[rand() % yellowCardMessages.size()] << "\n";
        }
        else if (event == 7)
        {
            FootballPlayer player = teamB.getRandPl();
            std::vector<std::string> redCardMessages {
                player.getName() + " (#" + std::to_string(player.getShirtNr()) + ") is sent off with a red card for violent conduct!",
                player.getName() + " (#" + std::to_string(player.getShirtNr()) + ") receives a red card after a second yellow.",
                player.getName() + " (#" + std::to_string(player.getShirtNr()) + ") is shown a straight red card for a dangerous foul!"
            };
            std::cout << "Minute " << mins << ": " << redCardMessages[rand() % redCardMessages.size()] << "\n";
        }
        else if (event == 8)
        {
            FootballPlayer player = teamA.getRandPl();
            std::vector<std::string> injuryMessages {
                player.getName() + " (#" + std::to_string(player.getShirtNr()) + ") goes down injured. A substitution might be needed.",
                player.getName() + " (#" + std::to_string(player.getShirtNr()) + ") looks hurt. Medical team is on the field.",
                player.getName() + " (#" + std::to_string(player.getShirtNr()) + ") suffers a knock. He might not continue."
            };
            std::cout << "Minute " << mins << ": " << injuryMessages[rand() % injuryMessages.size()] << "\n";
        }
        else if (event == 9)
        {
            FootballPlayer player = teamB.getRandPl();
            std::vector<std::string> foulMessages {
                player.getName() + " (#" + std::to_string(player.getShirtNr()) + ") commits a foul. Free kick for " + teamA.getName() + ".",
                player.getName() + " (#" + std::to_string(player.getShirtNr()) + ") fouls his opponent. Dangerous position for " + teamA.getName() + ".",
                player.getName() + " (#" + std::to_string(player.getShirtNr()) + ") brings down a player. Free kick awarded to " + teamA.getName() + "."
            };
            std::cout << "Minute " << mins << ": " << foulMessages[rand() % foulMessages.size()] << "\n";
        }
        else if (event == 10)
        {
            FootballPlayer player = teamA.getRandPl();
            std::cout << "Minute " << mins << ": Free kick for " << teamA.getName() << ". " << player.getName()
                      << " is preparing to take it.\n";
        }
    }

    std::cout << "Minute 90: The match is over!\n";
    std::cout << "Final score: " << teamA.getName() << " " << teamAGoals << " - " << teamBGoals << " " << teamB.getName() << "\n";
}
