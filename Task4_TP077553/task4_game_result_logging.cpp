#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>
using namespace std;

// === Player Linked List Node ===
struct PlayerNode {
    int id;
    string name;
    PlayerNode* next;
};

// === Match Stack Node ===
struct MatchNode {
    string player1, player2;
    int score1, score2;
    string date;
    MatchNode* next;
};

// === History Linked List Node ===
struct HistoryNode {
    string player;
    int score;
    string result;
    string date;
    HistoryNode* next;

    HistoryNode(string p, int s, string r, string d) {
        player = p;
        score = s;
        result = r;
        date = d;
        next = nullptr;
    }
};

// === Global Variables ===
PlayerNode* playerHead = nullptr;
int nextPlayerID = 1001;

MatchNode* matchTop = nullptr;
HistoryNode* historyHead = nullptr;

// === Utility Functions ===
void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int getValidatedInt(string prompt) {
    int x;
    while (true) {
        cout << prompt;
        if (cin >> x) {
            clearInput();
            return x;
        } else {
            cout << "❌ Invalid input. Please enter a number.\n";
            clearInput();
        }
    }
}

// === Player Management ===
bool playerExists(string name) {
    PlayerNode* temp = playerHead;
    while (temp) {
        if (temp->name == name) return true;
        temp = temp->next;
    }
    return false;
}

string getPlayerNameById(int id) {
    PlayerNode* temp = playerHead;
    while (temp) {
        if (temp->id == id) return temp->name;
        temp = temp->next;
    }
    return "";
}

void listPlayers() {
    if (!playerHead) {
        cout << "No players registered.\n";
        return;
    }
    cout << "\n=== Registered Players ===\n";
    PlayerNode* temp = playerHead;
    while (temp) {
        cout << temp->id << " - " << temp->name << "\n";
        temp = temp->next;
    }
}

void registerPlayer() {
    string name;
    cout << "Enter new player name: ";
    getline(cin, name);
    if (name.empty()) {
        cout << "❌ Name cannot be empty.\n";
        return;
    }
    if (playerExists(name)) {
        cout << "❌ Player already registered.\n";
        return;
    }

    PlayerNode* newPlayer = new PlayerNode;
    newPlayer->id = nextPlayerID++;
    newPlayer->name = name;
    newPlayer->next = playerHead;
    playerHead = newPlayer;

    cout << "✅ Player registered with ID: " << newPlayer->id << "\n";
}

// === Match Stack ===
void pushMatch(string p1, string p2, int s1, int s2, string date) {
    MatchNode* newMatch = new MatchNode{p1, p2, s1, s2, date, matchTop};
    matchTop = newMatch;
}

void displayRecentMatches() {
    if (!matchTop) {
        cout << "\nNo recent match results.\n";
        return;
    }
    cout << "\n=== Recent Match Results ===\n";
    MatchNode* temp = matchTop;
    while (temp) {
        cout << temp->date << ": " << temp->player1 << " (" << temp->score1 << ") vs "
             << temp->player2 << " (" << temp->score2 << ")\n";
        temp = temp->next;
    }
}

// === History Linked List ===
void addHistory(string name, int score, string result, string date) {
    HistoryNode* newNode = new HistoryNode(name, score, result, date);
    if (!historyHead) historyHead = newNode;
    else {
        HistoryNode* temp = historyHead;
        while (temp->next) temp = temp->next;
        temp->next = newNode;
    }
}

void viewPlayerHistory(string name) {
    HistoryNode* temp = historyHead;
    bool found = false;
    cout << "\n=== History for " << name << " ===\n";
    while (temp) {
        if (temp->player == name) {
            found = true;
            cout << temp->date << " - " << temp->result << " - Score: " << temp->score << "\n";
        }
        temp = temp->next;
    }
    if (!found) cout << "No records found for " << name << ".\n";
}

void viewAllHistory() {
    if (!historyHead) {
        cout << "\nNo match history recorded.\n";
        return;
    }
    cout << "\n=== All Match History ===\n";
    HistoryNode* temp = historyHead;
    while (temp) {
        cout << temp->date << ": " << temp->player << " - " << temp->result
             << " - Score: " << temp->score << "\n";
        temp = temp->next;
    }
}

// === File I/O ===
void saveToCSV(string p1, string p2, int s1, int s2, string date) {
    ofstream file("match_history.csv", ios::app);
    if (file)
        file << date << "," << p1 << "," << s1 << "," << p2 << "," << s2 << "\n";
}

void loadFromCSV() {
    ifstream file("match_history.csv");
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string date, p1, s1_str, p2, s2_str;
        if (!getline(ss, date, ',')) continue;
        if (!getline(ss, p1, ',')) continue;
        if (!getline(ss, s1_str, ',')) continue;
        if (!getline(ss, p2, ',')) continue;
        if (!getline(ss, s2_str, ',')) continue;

        int s1, s2;
        try {
            s1 = stoi(s1_str);
            s2 = stoi(s2_str);
        } catch (...) {
            continue;
        }

        string r1 = (s1 > s2) ? "WIN" : "LOSS";
        string r2 = (s2 > s1) ? "WIN" : "LOSS";

        pushMatch(p1, p2, s1, s2, date);
        addHistory(p1, s1, r1, date);
        addHistory(p2, s2, r2, date);
    }
}

// === Add Match ===
void addMatch() {
    if (!playerHead || !playerHead->next) {
        cout << "❌ At least two players must be registered.\n";
        return;
    }

    listPlayers();
    int id1 = getValidatedInt("Enter Player 1 ID: ");
    int id2 = getValidatedInt("Enter Player 2 ID: ");

    string p1 = getPlayerNameById(id1);
    string p2 = getPlayerNameById(id2);

    if (p1 == "" || p2 == "" || p1 == p2) {
        cout << "❌ Invalid player selection.\n";
        return;
    }

    int s1 = getValidatedInt("Enter " + p1 + "'s score: ");
    int s2 = getValidatedInt("Enter " + p2 + "'s score: ");
    string date;
    cout << "Enter match date (YYYY-MM-DD): ";
    getline(cin, date);

    string r1 = (s1 > s2) ? "WIN" : "LOSS";
    string r2 = (s2 > s1) ? "WIN" : "LOSS";

    pushMatch(p1, p2, s1, s2, date);
    addHistory(p1, s1, r1, date);
    addHistory(p2, s2, r2, date);
    saveToCSV(p1, p2, s1, s2, date);

    cout << "✅ Match recorded and saved.\n";
}

// === Menu ===
void showMenu() {
    cout << "\n===== ADMIN MENU =====\n"
         << "1. Register New Player\n"
         << "2. Add Match Result\n"
         << "3. View Recent Matches\n"
         << "4. View Player History\n"
         << "5. View All Match History\n"
         << "6. Exit\n"
         << "Enter choice: ";
}

// === Main ===
int main() {
    cout << "===================================\n";
    cout << "   WELCOME ADMIN - MATCH SYSTEM\n";
    cout << "===================================\n";

    loadFromCSV();

    int choice;
    while (true) {
        showMenu();
        if (!(cin >> choice)) {
            cout << "❌ Invalid input. Enter a number.\n";
            clearInput();
            continue;
        }
        clearInput();

        switch (choice) {
            case 1: registerPlayer(); break;
            case 2: addMatch(); break;
            case 3: displayRecentMatches(); break;
            case 4: {
                string name;
                cout << "Enter player name: ";
                getline(cin, name);
                viewPlayerHistory(name);
                break;
            }
            case 5: viewAllHistory(); break;
            case 6: cout << "Exiting... Goodbye!\n"; return 0;
            default: cout << "❌ Invalid choice. Try again.\n";
        }
    }
}
