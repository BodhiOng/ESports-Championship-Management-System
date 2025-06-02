#include <iostream>
#include <cstring>
#include <limits>
using namespace std;
using std::streamsize;
using std::numeric_limits;

const int MAX_SPECTATORS = 1000;
const int MAX_VIPS = 100;
const int MAX_STREAMERS = 50;
const int STREAMER_SLOTS = 3;
const int VIP_SLOTS = 3;
const int REGULAR_SLOTS = 3;
const int TOTAL_VIEWING_SLOTS = STREAMER_SLOTS + VIP_SLOTS + REGULAR_SLOTS;

struct Spectator {
    int id;
    char name[50];
    bool isVIP;
    bool isStreamer;
};

class SpectatorQueue {
private:
    const int maxSize;
    Spectator* queue;
    int front, rear;
    int capacity;
    int count;

public:
    SpectatorQueue(int size) : maxSize(size), front(0), rear(-1), count(0) {
        capacity = size;
        queue = new Spectator[size];
    }

    ~SpectatorQueue() {
        delete[] queue;
    }

    bool isFull() {
        return (count == capacity);
    }

    bool isEmpty() {
        return (count == 0);
    }

    bool enqueue(const Spectator& spec) {
        if (isFull()) {
            cout << "Queue is full!" << endl;
            return false;
        }
        rear = (rear + 1) % capacity;
        queue[rear] = spec;
        count++;
        return true;
    }

    bool dequeue(Spectator& spec) {
        if (isEmpty()) {
            return false;
        }
        spec = queue[front];
        front = (front + 1) % capacity;
        count--;
        return true;
    }

    void displayQueue() {
        if (isEmpty()) {
            cout << "Queue is empty!" << endl;
            return;
        }
        int i = front;
        int cnt = 0;
        while (cnt < count) {
            cout << "ID: " << queue[i].id
                 << " | Name: " << queue[i].name
                 << " | Type: "
                 << (queue[i].isStreamer ? "Streamer" : (queue[i].isVIP ? "VIP" : "Regular")) << endl;
            i = (i + 1) % capacity;
            cnt++;
        }
    }
};

class LiveStreamManager {
private:
    SpectatorQueue regularQueue;
    SpectatorQueue vipQueue;
    SpectatorQueue streamerQueue;

    int currentStreamers;
    int currentVIPs;
    int currentRegulars;
    int nextID;

public:
    Spectator* streamerViewingArea;
    Spectator* vipViewingArea;
    Spectator* regularViewingArea;

    LiveStreamManager() : regularQueue(MAX_SPECTATORS), vipQueue(MAX_VIPS), streamerQueue(MAX_STREAMERS),
                         currentStreamers(0), currentVIPs(0), currentRegulars(0), nextID(1) {
        streamerViewingArea = new Spectator[STREAMER_SLOTS];
        vipViewingArea = new Spectator[VIP_SLOTS];
        regularViewingArea = new Spectator[REGULAR_SLOTS];
    }

    ~LiveStreamManager() {
        delete[] streamerViewingArea;
        delete[] vipViewingArea;
        delete[] regularViewingArea;
    }

    void addSpectator(const char* name, bool isVIP = false, bool isStreamer = false) {
        if (isStreamer) {
            if (streamerQueue.isFull()) {
                cout << "Streamer queue is full! Cannot add more streamers." << endl;
                return;
            }
        } else if (isVIP) {
            if (vipQueue.isFull()) {
                cout << "VIP queue is full! Cannot add more VIPs." << endl;
                return;
            }
        } else {
            if (regularQueue.isFull()) {
                cout << "Regular queue is full! Cannot add more regular spectators." << endl;
                return;
            }
        }

        Spectator spec;
        spec.id = nextID++;
        strncpy(spec.name, name, 49);
        spec.name[49] = '\0';
        spec.isVIP = isVIP;
        spec.isStreamer = isStreamer;

        if (isStreamer) {
            streamerQueue.enqueue(spec);
        } else if (isVIP) {
            vipQueue.enqueue(spec);
        } else {
            regularQueue.enqueue(spec);
        }

        cout << "Added " << (isStreamer ? "Streamer" : (isVIP ? "VIP" : "Regular"))
             << " spectator: " << name << " (ID: " << spec.id << ")" << endl;
    }

    void manageViewingArea() {
        // Fill streamer slots first
        while (currentStreamers < STREAMER_SLOTS) {
            Spectator nextViewer;
            if (streamerQueue.dequeue(nextViewer)) {
                streamerViewingArea[currentStreamers++] = nextViewer;
                cout << "Streamer " << nextViewer.name << " (ID: " << nextViewer.id
                     << ") has entered the viewing area" << endl;
            } else {
                break; // No more streamers in queue
            }
        }

        // Fill VIP slots next
        while (currentVIPs < VIP_SLOTS) {
            Spectator nextViewer;
            if (vipQueue.dequeue(nextViewer)) {
                vipViewingArea[currentVIPs++] = nextViewer;
                cout << "VIP " << nextViewer.name << " (ID: " << nextViewer.id
                     << ") has entered the viewing area" << endl;
            } else {
                break; // No more VIPs in queue
            }
        }

        // Fill regular slots last
        while (currentRegulars < REGULAR_SLOTS) {
            Spectator nextViewer;
            if (regularQueue.dequeue(nextViewer)) {
                regularViewingArea[currentRegulars++] = nextViewer;
                cout << "Regular spectator " << nextViewer.name << " (ID: " << nextViewer.id
                     << ") has entered the viewing area" << endl;
            } else {
                break; // No more regular spectators in queue
            }
        }
    }

    bool isSlotEmpty(int slotType, int slotIndex) {
        switch (slotType) {
            case 1: // Streamer
                return (slotIndex >= currentStreamers);
            case 2: // VIP
                return (slotIndex >= currentVIPs);
            case 3: // Regular
                return (slotIndex >= currentRegulars);
            default:
                return true;
        }
    }

    void releaseViewingSlot(int slotType, int slotIndex) {
        Spectator* area = nullptr;
        int* currentCount = nullptr;
        string areaName;

        switch (slotType) {
            case 1: // Streamer
                area = streamerViewingArea;
                currentCount = &currentStreamers;
                areaName = "Streamer";
                break;
            case 2: // VIP
                area = vipViewingArea;
                currentCount = &currentVIPs;
                areaName = "VIP";
                break;
            case 3: // Regular
                area = regularViewingArea;
                currentCount = &currentRegulars;
                areaName = "Regular";
                break;
            default:
                cout << "Invalid slot type!" << endl;
                return;
        }

        if (slotIndex < 0 || slotIndex >= *currentCount) {
            cout << "Invalid slot index!" << endl;
            return;
        }

        cout << area[slotIndex].name << " (ID: " << area[slotIndex].id
             << ") has left the " << areaName << " viewing area" << endl;

        // Shift everyone after this slot forward
        for (int i = slotIndex; i < *currentCount - 1; i++) {
            area[i] = area[i + 1];
        }

        (*currentCount)--;

        // Try to fill the newly emptied slot
        manageViewingArea();
    }

    // Getters for private member variables
    int getCurrentStreamers() { return currentStreamers; }
    int getCurrentVIPs() { return currentVIPs; }
    int getCurrentRegulars() { return currentRegulars; }

    void displayStatus() {
        cout << "\n=== LIVE STREAM STATUS ===" << endl;

        // Streamer viewing area
        cout << "\n=== STREAMER VIEWING AREA (" << currentStreamers << "/" << STREAMER_SLOTS << ") ===" << endl;
        for (int i = 0; i < currentStreamers; i++) {
            cout << streamerViewingArea[i].name
                 << " (ID: " << streamerViewingArea[i].id << ")" << endl;
        }

        // VIP viewing area
        cout << "\n=== VIP VIEWING AREA (" << currentVIPs << "/" << VIP_SLOTS << ") ===" << endl;
        for (int i = 0; i < currentVIPs; i++) {
            cout << vipViewingArea[i].name
                 << " (ID: " << vipViewingArea[i].id << ")" << endl;
        }

        // Regular viewing area
        cout << "\n=== REGULAR VIEWING AREA (" << currentRegulars << "/" << REGULAR_SLOTS << ") ===" << endl;
        for (int i = 0; i < currentRegulars; i++) {
            cout << regularViewingArea[i].name
                 << " (ID: " << regularViewingArea[i].id << ")" << endl;
        }

        // Queues
        cout << "\n=== WAITING QUEUES ===" << endl;

        cout << "\nStreamer Queue:" << endl;
        streamerQueue.displayQueue();

        cout << "\nVIP Queue:" << endl;
        vipQueue.displayQueue();

        cout << "\nRegular Queue:" << endl;
        regularQueue.displayQueue();

        cout << endl;
    }
};

int main() {
    LiveStreamManager manager;
    int choice;
    char name[50];

    cout << "=== eSports Championship Live Stream Management ===\n" << endl;

    while (true) {
        cout << "\nMenu:" << endl;
        cout << "1. Add Regular Spectator" << endl;
        cout << "2. Add VIP Spectator" << endl;
        cout << "3. Add Streamer" << endl;
        cout << "4. Release Viewing Slot" << endl;
        cout << "   a. Release Streamer Slot" << endl;
        cout << "   b. Release VIP Slot" << endl;
        cout << "   c. Release Regular Slot" << endl;
        cout << "5. Show Status" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        if (!(cin >> choice)) {
            // Clear the error state
            cin.clear();
            // Discard invalid input
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number between 1 and 6.\n";
            continue;
        }

        // Clear any remaining characters in the input buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                cout << "Enter spectator name: ";
                cin.getline(name, 50);
                manager.addSpectator(name);
                manager.manageViewingArea();
                break;

            case 2:
                cout << "Enter VIP name: ";
                cin.getline(name, 50);
                manager.addSpectator(name, true);
                manager.manageViewingArea();
                break;

            case 3:
                cout << "Enter streamer name: ";
                cin.getline(name, 50);
                manager.addSpectator(name, false, true);
                manager.manageViewingArea();
                break;

            case 4: {
                // Show current status first
                manager.displayStatus();

                // Show available slots for release
                cout << "\n=== AVAILABLE SLOTS FOR RELEASE ===" << endl;

                // Show streamer slots
                cout << "a. Streamer Slots: ";
                int streamerCount = manager.getCurrentStreamers();
                if (streamerCount > 0) {
                    for (int i = 0; i < streamerCount; i++) {
                        cout << "Slot " << i << ", ";
                    }
                } else {
                    cout << "(All empty)";
                }

                // Show VIP slots
                cout << "\nb. VIP Slots: ";
                int vipCount = manager.getCurrentVIPs();
                if (vipCount > 0) {
                    for (int i = 0; i < vipCount; i++) {
                        cout << "Slot " << i << ", ";
                    }
                } else {
                    cout << "(All empty)";
                }

                // Show regular slots
                cout << "\nc. Regular Slots: ";
                int regularCount = manager.getCurrentRegulars();
                if (regularCount > 0) {
                    for (int i = 0; i < regularCount; i++) {
                        cout << "Slot " << i << ", ";
                    }
                } else {
                    cout << "(All empty)";
                }
                cout << "\n";

                // Get area selection
                char areaChoice;
                cout << "Select area (a=Streamer, b=VIP, c=Regular, x=Cancel): ";
                cin >> areaChoice;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                if (tolower(areaChoice) == 'x') {
                    cout << "Operation cancelled." << endl;
                    break;
                }

                int slotType = 0;
                int currentSlots = 0;
                string areaName;

                switch (tolower(areaChoice)) {
                    case 'a':
                        slotType = 1; // Streamer
                        currentSlots = manager.getCurrentStreamers();
                        areaName = "Streamer";
                        break;
                    case 'b':
                        slotType = 2; // VIP
                        currentSlots = manager.getCurrentVIPs();
                        areaName = "VIP";
                        break;
                    case 'c':
                        slotType = 3; // Regular
                        currentSlots = manager.getCurrentRegulars();
                        areaName = "Regular";
                        break;
                    default:
                        cout << "Invalid area selection!" << endl;
                        break;
                }

                if (slotType > 0) {
                    if (currentSlots == 0) {
                        cout << areaName << " area is already empty!" << endl;
                        break;
                    }

                    cout << "\n" << areaName << " area has " << currentSlots << " active slot" << (currentSlots != 1 ? "s" : "") << ":\n";

                    // Display each occupied slot with details
                    for (int i = 0; i < currentSlots; i++) {
                        string viewerName;
                        int viewerId;

                        // Get the spectator details based on the area type
                        switch (slotType) {
                            case 1: // Streamer
                                viewerName = manager.streamerViewingArea[i].name;
                                viewerId = manager.streamerViewingArea[i].id;
                                cout << "Slot " << i << ": " << viewerName << " (ID: " << viewerId << ")" << endl;
                                break;
                            case 2: // VIP
                                viewerName = manager.vipViewingArea[i].name;
                                viewerId = manager.vipViewingArea[i].id;
                                cout << "Slot " << i << ": " << viewerName << " (ID: " << viewerId << ")" << endl;
                                break;
                            case 3: // Regular
                                viewerName = manager.regularViewingArea[i].name;
                                viewerId = manager.regularViewingArea[i].id;
                                cout << "Slot " << i << ": " << viewerName << " (ID: " << viewerId << ")" << endl;
                                break;
                        }
                    }

                    cout << "\nEnter slot number to release (or -1 to cancel): ";

                    int slotIndex;
                    if (!(cin >> slotIndex)) {
                        cout << "Please enter a valid number!" << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    } else if (slotIndex == -1) {
                        cout << "Operation cancelled." << endl;
                    } else if (slotIndex < 0 || slotIndex >= currentSlots) {
                        cout << "Invalid slot number! Please choose ";
                        if (currentSlots == 1) {
                            cout << "0";
                        } else {
                            cout << "between 0 and " << (currentSlots - 1);
                        }
                        cout << "." << endl;
                    } else {
                        manager.releaseViewingSlot(slotType, slotIndex);
                    }
                }
                break;
            }

            case 5:
                manager.displayStatus();
                break;

            case 6:
                cout << "Exiting..." << endl;
                return 0;

            default:
                cout << "Invalid choice!" << endl;
        }
    }

    return 0;
}
