#ifndef TOURNAMENTMANAGER_HPP
#define TOURNAMENTMANAGER_HPP

#include <queue>
#include <vector>
#include <string>

struct Player {
    std::string name;
    int priority;

    Player(const std::string& n, int p) : name(n), priority(p) {}

    bool operator<(const Player& other) const {
        return priority > other.priority;
    }
};

class TournamentManager {
private:
    std::priority_queue<Player> registrationQueue;
    std::queue<Player> checkInQueue;
    std::vector<Player> withdrawnPlayers;

public:
    void loadRegistrations(const std::string& filename);
    void processCheckIns();
    void displayCheckInQueue() const;
    void withdrawPlayer(const std::string& playerName);
    void registerReplacement(const std::string& playerName, int priority);
    void saveWithdrawalsToFile(const std::string& filename) const;
    void saveCheckInLogToFile(const std::string& filename) const;
};

#endif
