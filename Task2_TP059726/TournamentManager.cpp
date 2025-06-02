// TournamentManager.cpp
#include "TournamentManager.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

void TournamentManager::loadRegistrations(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    std::string line;

    if (!getline(file, line)) {
        std::cerr << "File is empty or unreadable" << std::endl;
        return;
    }

    while (getline(file, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string name, priorityStr;

        if (!getline(ss, name, ',') || !getline(ss, priorityStr)) {
            std::cerr << "Skipping malformed line: " << line << std::endl;
            continue;
        }

        try {
            int priority = std::stoi(priorityStr);
            registrationQueue.push(Player(name, priority));
            std::cout << "Registered player: " << name << " (Priority: " << priority << ")" << std::endl;
        }
        catch (const std::invalid_argument& e) {
            std::cerr << "Invalid priority for player " << name << ": " << priorityStr << std::endl;
            continue;
        }
    }
    file.close();
}

void TournamentManager::processCheckIns() {
    while (!registrationQueue.empty()) {
        Player p = registrationQueue.top();
        registrationQueue.pop();
        checkInQueue.push(p);
        std::cout << "Checked in: " << p.name << std::endl;
    }
}

void TournamentManager::displayCheckInQueue() const {
    std::queue<Player> temp = checkInQueue;
    std::cout << "\nCurrent check-in queue:" << std::endl;
    while (!temp.empty()) {
        Player p = temp.front();
        temp.pop();
        std::cout << p.name << std::endl;
    }
}

void TournamentManager::withdrawPlayer(const std::string& playerName) {
    std::queue<Player> temp;
    bool found = false;
    while (!checkInQueue.empty()) {
        Player p = checkInQueue.front();
        checkInQueue.pop();
        if (p.name == playerName) {
            found = true;
            withdrawnPlayers.push_back(p);
            std::cout << "Player " << playerName << " has withdrawn. Added to waiting list." << std::endl;
        }
        else {
            temp.push(p);
        }
    }
    checkInQueue = temp;

    if (!found) {
        std::cout << "Player " << playerName << " not found in check-in queue." << std::endl;
    }
}

void TournamentManager::registerReplacement(const std::string& playerName, int priority) {
    Player replacement(playerName, priority);
    checkInQueue.push(replacement);
    std::cout << "Registered replacement player: " << playerName << " (Priority: " << priority << ")" << std::endl;
}

void TournamentManager::saveWithdrawalsToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file for withdrawals: " << filename << std::endl;
        return;
    }
    file << "Name,Priority\n";
    for (const auto& player : withdrawnPlayers) {
        file << player.name << "," << player.priority << "\n";
    }
    file.close();
}

void TournamentManager::saveCheckInLogToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file for check-in log: " << filename << std::endl;
        return;
    }
    file << "Name,Priority\n";
    std::queue<Player> temp = checkInQueue;
    while (!temp.empty()) {
        Player p = temp.front();
        temp.pop();
        file << p.name << "," << p.priority << "\n";
    }
    file.close();
}
