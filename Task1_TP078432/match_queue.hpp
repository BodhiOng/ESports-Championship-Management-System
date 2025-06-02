#ifndef MATCH_QUEUE_HPP
#define MATCH_QUEUE_HPP
//purpose: stores scheduled matches using circular queue
#include "player.hpp"

struct Match {
    Player player1;
    Player player2;
};

class MatchQueue {
private:
    Match matches[100];
    int front, rear;

public:
    MatchQueue() {
        front = 0;
        rear = 0;
    }

    void enqueue(Match m) {
        matches[rear++] = m;
    }

    Match dequeue() {
        return matches[front++];
    }

    bool isEmpty() {
        return front == rear;
    }

    int size() {
        return rear - front;
    }
};

#endif
