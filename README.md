# Simple Lottery Simulator

This is a C program that simulates a simple lottery system using data structures:
- Queue for managing participants
- Stack for storing winning numbers

## Features

- Add participants to the lottery
- View all current participants
- Generate random winning numbers
- Draw random winners from participants
- Interactive menu-driven interface

## Data Structures

### Queue (Participants)
- Implemented using a circular array
- First-In-First-Out (FIFO) behavior
- Stores participant names

### Stack (Winning Numbers)
- Implemented using an array
- Last-In-First-Out (LIFO) behavior
- Stores randomly generated winning numbers

## Functions

### Queue Operations
- `enqueue()` - Add a participant to the queue
- `dequeue()` - Remove a participant from the queue
- `isQueueEmpty()` - Check if queue is empty
- `isQueueFull()` - Check if queue is full
- `displayParticipants()` - Show all participants

### Stack Operations
- `push()` - Add a number to the stack
- `pop()` - Remove a number from the stack
- `isStackEmpty()` - Check if stack is empty
- `isStackFull()` - Check if stack is full
- `generateWinningNumbers()` - Generate random winning numbers
- `displayWinningNumbers()` - Show all winning numbers

### Lottery Operations
- `drawWinners()` - Randomly select winners from participants

## How to Compile and Run

```bash
gcc project.c -o lottery
./lottery
```

## Usage

1. Compile the program using gcc
2. Run the executable
3. Use the menu to:
   - Add participants
   - View participants
   - Draw winners
   - Exit the program

## Implementation Details

The program uses a circular queue implementation for efficient memory usage and a simple stack for managing winning numbers. The drawing mechanism randomly selects participants and properly maintains the queue structure after each draw.