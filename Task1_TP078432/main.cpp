#include <iostream>
#include <cstdlib>
#include <ctime>
#include "player.hpp"
#include "priority_queue.hpp"
#include "match_queue.hpp"

using namespace std;

void simulateMatch(const Match& match, Player& winner) {
    // Higher rank wins OR random if same rank
    if (match.player1.ranking == match.player2.ranking) {
        winner = (rand() % 2 == 0) ? match.player1 : match.player2;
    } else {
        winner = (match.player1.ranking > match.player2.ranking) ? match.player1 : match.player2;
    }
    cout << match.player1.name << " vs " << match.player2.name << " -> Winner: " << winner.name << endl;
}

int main() {
    srand(time(0));  // seed for randomness
    Player players[100];
    int playerCount = 0;

    // Load players
    loadPlayers(players, playerCount);
    cout << "Loaded " << playerCount << " players.\n";

    // Insert into priority queue
    PriorityQueue pq;
    for (int i = 0; i < playerCount; i++) {
        pq.insert(players[i]);
    }

    int round = 1;

    while (pq.getSize() > 1) {
        cout << "\n--- Round " << round++ << " ---\n";
        MatchQueue mq;

        // Pair players into matches
        while (pq.getSize() >= 2) {
            Player p1 = pq.extractMax();
            Player p2 = pq.extractMax();

            Match m = { p1, p2 };
            mq.enqueue(m);
        }

        // If there's an odd player, auto-advance
        if (pq.getSize() == 1) {
            Player leftover = pq.extractMax();
            cout << leftover.name << " auto-advances to next round!\n";
            pq.insert(leftover);
        }

        // Simulate each match and insert winner back into PQ
        while (!mq.isEmpty()) {
            Match m = mq.dequeue();
            Player winner;
            simulateMatch(m, winner);
            pq.insert(winner);
        }
    }

    // Declare champion
    if (!pq.isEmpty()) {
        Player champion = pq.extractMax();
        cout << "\n Tournament Champion: " << champion.name << " (Rank " << champion.ranking << ")\n";
    }

    return 0;
}
