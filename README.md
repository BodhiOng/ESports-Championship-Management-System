# eSports Championship Management System

A C++ application that manages live streaming viewers for an eSports championship with different priority levels for viewers.

## Features

- **Priority-based Viewer Management**: Three priority levels for viewers:
  - **Streamers** (highest priority)
  - **VIPs** (medium priority)
  - **Regular** spectators (lowest priority)

- **Viewing Area Allocation**: Automatic allocation of viewers to limited viewing slots based on priority:
  - 3 Streamer slots
  - 3 VIP slots
  - 3 Regular spectator slots

- **Queue Management**: Separate queues for each viewer type with maximum capacity limits:
  - Up to 50 Streamers
  - Up to 100 VIPs
  - Up to 1000 Regular spectators

## How It Works

1. **Adding Viewers**:
   - Add viewers with their name and type (Streamer, VIP, or Regular)
   - Each viewer is assigned a unique ID
   - Viewers are placed in their respective queues

2. **Viewing Area Management**:
   - The system automatically fills viewing slots based on priority
   - Streamers get first priority, followed by VIPs, then Regular spectators
   - When a viewer leaves, the next in line from the appropriate queue takes their place

3. **Queue Management**:
   - Viewers can be added to their respective queues
   - The system manages queue capacity and prevents overflow

## Getting Started

### Prerequisites

- C++ compiler (supporting C++11 or later)
- Standard Library (STL)

### Compilation

```bash
g++ task_3.cpp -o esports_manager
```

### Running the Application

```bash
./esports_manager
```

## Usage

1. Run the program
2. Use the menu to perform actions:
   - Add viewers (Streamer, VIP, or Regular)
   - Manage viewing area
   - View current queues
   - View current viewing area
   - Exit the program

## Code Structure

- `Spectator` struct: Stores viewer information (ID, name, type)
- `SpectatorQueue` class: Implements a circular queue for managing viewers
- `LiveStreamManager` class: Main class that handles the core functionality
  - Manages three separate queues (Streamer, VIP, Regular)
  - Handles viewing area allocation
  - Provides methods for adding/removing viewers

## Limitations

- Fixed number of viewing slots (3 per viewer type)
- Maximum queue sizes are fixed at compile time
- No persistent storage (all data is lost when program exits)

## Future Enhancements

1. Dynamic resizing of queues
2. Save/Load functionality for persistent data
3. Network support for remote management
4. More detailed statistics and reporting
5. GUI interface

## Author

[Bodhidharma Ong](https://github.com/BodhiOng)

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
