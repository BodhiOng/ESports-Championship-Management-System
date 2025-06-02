#include "TournamentManager.hpp"
#include <iostream>
using namespace std;

int main() {
    TournamentManager manager;

    manager.loadRegistrations("registrations.csv");

    cout << "\nProcessing registrations...\n";
    manager.processCheckIns();

    manager.displayCheckInQueue();

    manager.withdrawPlayer("Charlie");

    manager.registerReplacement("Frank", 1);

    manager.displayCheckInQueue();

    manager.saveWithdrawalsToFile("withdrawals.csv");
    manager.saveCheckInLogToFile("checkin_log.csv");

    cout << "\nData written to withdrawals.csv and checkin_log.csv\n";

    return 0;
}
