#ifndef PLAYER_HPP
#define PLAYER_HPP
//purpose : define player struct + file loading function
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
using namespace std;

struct Player {
    int id;
    char name[50];
    int ranking;
};

// Loads players from players.csv into an array
void loadPlayers(Player players[], int &count) {
    ifstream file("players.csv");
    if (!file.is_open()) {
        cout << "Error: Could not open players.csv" << endl;
        return;
    }

    string line;
    getline(file, line); // Skip header line

    while (getline(file, line)) {
        Player p;
        sscanf(line.c_str(), "%d,%49[^,],%d", &p.id, p.name, &p.ranking);
        players[count++] = p;
    }

    file.close();
}

#endif
