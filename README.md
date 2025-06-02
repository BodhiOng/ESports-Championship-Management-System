# eSports Championship Management System

This is an E-Sports Championship Management System developed as part of the CT077-3-2-DSTR (Data Structures) group assignment for the Asia Pacific University (APU) in 2025. 

## System Overview

This project implements a complete esports tournament management system using custom data structures (without using STL containers like `<list>` or `<vector>`). The system is divided into four main components:

## Components

### 1. Match Scheduling & Player Progression

Manages the competition structure and player advancement through tournament stages.

- Fair match pairings based on player rankings
- Dynamic tournament bracket updates
- Efficient flow management of matches through qualifier, group, and knockout stages

### 2. Tournament Registration & Player Queueing

Handles player registrations, check-ins, and tournament start procedures.

- Player check-in system
- Priority handling for early-bird signups and wildcard entries
- Efficient management of withdrawals and replacements

### 3. Live Stream & Spectator Queue Management

Ensures a well-managed viewing experience for different types of spectators.

- Priority-based viewer management for:
  - Streamers (highest priority)
  - VIPs (medium priority)
  - Regular spectators (lowest priority)
- Efficient audience overflow management
- Dedicated viewing slots for live-streaming setups

### 4. Game Result Logging & Performance History

Records and maintains match outcomes and player statistics.

- Recent match results storage for quick review
- Structured history for player performance tracking
- Easy access to past results for tournament analysis

## Technical Implementation

### Data Structures Used

The system implements and utilizes the following custom data structures:

- **Stacks**: For managing match history, player progression, and result logging
- **Queues**: For handling tournament registrations and standard spectator management
- **Priority Queues**: For VIP and streamer management in viewing areas
- **Circular Queues**: For efficient rotation of players and spectators

### Getting Started

#### Prerequisites

- C++ compiler (supporting C++11 or later)
- No external libraries required (custom implementations of all data structures)

#### Compilation

```bash
g++ -o esports_championship main.cpp task1_*.cpp task2_*.cpp task3_*.cpp task4_*.cpp
```

#### Running the Application

```bash
./esports_championship
```

## Usage

1. Run the program
2. Use the menu to access different system components:
   - Match scheduling and player progression
   - Tournament registration and player queueing
   - Live stream and spectator management
   - Game result logging and performance history
3. Follow on-screen instructions for specific operations within each component

## Project Structure

- `main.cpp`: Entry point and menu system
- `Task1_*/`: Match scheduling and player progression implementation
- `Task2_*/`: Tournament registration and player queueing implementation
- `Task3_*/`: Live stream and spectator queue management implementation
- `Task4_*/`: Game result logging and performance history implementation

## Contributors

This project was developed as part of the CT077-3-2-DSTR Lab Evaluation Work #2 at Asia Pacific University.

## License

This project is licensed under the [MIT License](LICENSE).
