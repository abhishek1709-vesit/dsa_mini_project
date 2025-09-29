#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_SIZE 100
#define MAX_NAME 50

// Global variables for Queue (Participants)
char participants[MAX_SIZE][MAX_NAME];
int queue_front = 0;
int queue_rear = -1;
int queue_count = 0;

// Global variables for Stack (Winning Numbers)
int winning_numbers[MAX_SIZE];
int stack_top = -1;

// Queue Functions
void initQueue() {
    queue_front = 0;
    queue_rear = -1;
    queue_count = 0;
}

int isQueueEmpty() {
    return queue_count == 0;
}

int isQueueFull() {
    return queue_count == MAX_SIZE;
}

void enqueue(char* name) {
    if (isQueueFull()) {
        printf("Queue is full! Cannot add more participants.\n");
        return;
    }
    queue_rear = (queue_rear + 1) % MAX_SIZE;
    strcpy(participants[queue_rear], name);
    queue_count++;
    printf("Participant '%s' added to lottery!\n", name);
}

void dequeue(char* name) {
    if (isQueueEmpty()) {
        strcpy(name, "");
        return;
    }
    strcpy(name, participants[queue_front]);
    queue_front = (queue_front + 1) % MAX_SIZE;
    queue_count--;
}

// Stack Functions
void initStack() {
    stack_top = -1;
}

int isStackEmpty() {
    return stack_top == -1;
}

int isStackFull() {
    return stack_top == MAX_SIZE - 1;
}

void push(int number) {
    if (isStackFull()) {
        printf("Stack is full!\n");
        return;
    }
    winning_numbers[++stack_top] = number;
}

int pop() {
    if (isStackEmpty()) {
        return -1;
    }
    return winning_numbers[stack_top--];
}

// Utility Functions
void displayParticipants() {
    if (isQueueEmpty()) {
        printf("No participants in the lottery yet!\n");
        return;
    }
    
    printf("\n=== LOTTERY PARTICIPANTS ===\n");
    int temp_front = queue_front;
    for (int i = 0; i < queue_count; i++) {
        printf("%d. %s\n", i + 1, participants[temp_front]);
        temp_front = (temp_front + 1) % MAX_SIZE;
    }
    printf("Total participants: %d\n\n", queue_count);
}

void generateWinningNumbers(int count) {
    printf("\n=== GENERATING WINNING NUMBERS ===\n");
    
    // Clear any existing numbers in stack
    initStack();
    
    srand(time(NULL));
    
    printf("Winning numbers (in reverse order): ");
    for (int i = 0; i < count; i++) {
        int number = (rand() % 99) + 1; // Numbers between 1-99
        push(number);
        printf("%d ", number);
    }
    printf("\n");
}

void displayWinningNumbers() {
    if (isStackEmpty()) {
        printf("No winning numbers generated yet!\n");
        return;
    }
    
    printf("\n=== WINNING NUMBERS (Last to First) ===\n");
    int temp_numbers[MAX_SIZE];
    int temp_top = -1;
    
    // Copy to temp stack to preserve original
    int number;
    while (!isStackEmpty()) {
        number = pop();
        temp_numbers[++temp_top] = number;
        printf("%d ", number);
    }
    
    // Restore original stack
    while (temp_top >= 0) {
        push(temp_numbers[temp_top--]);
    }
    printf("\n\n");
}

void drawWinners(int numWinners) {
    if (isQueueEmpty()) {
        printf("No participants to draw from!\n");
        return;
    }
    
    if (numWinners > queue_count) {
        numWinners = queue_count;
    }
    
    printf("\n=== LOTTERY DRAW RESULTS ===\n");
    srand(time(NULL)); // Seed randomness
    
    for (int i = 0; i < numWinners; i++) {
        // Pick a random index from queue
        int winnerIndex = rand() % queue_count;

        // Find that participant
        int actualIndex = (queue_front + winnerIndex) % MAX_SIZE;
        char winner[MAX_NAME];
        strcpy(winner, participants[actualIndex]);

        // Print winner
        printf("Winner #%d: %s\n", i + 1, winner);

        // Remove the winner from the queue
        // Shift elements to maintain queue correctly
        for (int j = winnerIndex; j < queue_count - 1; j++) {
            int srcIndex = (queue_front + j + 1) % MAX_SIZE;
            int destIndex = (queue_front + j) % MAX_SIZE;
            strcpy(participants[destIndex], participants[srcIndex]);
        }
        queue_rear = (queue_rear - 1 + MAX_SIZE) % MAX_SIZE;
        queue_count--;
    }
    
    printf("\nCongratulations to all winners!\n");
}

// Update main function to remove unwanted options
int main() {
    int choice;
    char name[MAX_NAME];
    int numWinners;
    
    // Initialize data structures
    initQueue();
    
    printf("Welcome to the Simple Lottery Simulator!\n");
    printf("Using Queue for participants.\n");
    
    while (1) {
        // Display menu directly in main function
        printf("\n========== LOTTERY SIMULATOR ==========\n");
        printf("1. Add Participant\n");
        printf("2. View All Participants\n");
        printf("3. Draw Winners\n");
        printf("4. Exit\n");
        printf("=======================================\n");
        printf("Enter your choice: ");
        
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter participant name: ");
                scanf("%s", name);
                enqueue(name);
                break;
                
            case 2:
                displayParticipants();
                break;
                
            case 3:
                printf("How many winners to draw? ");
                scanf("%d", &numWinners);
                if (numWinners > 0) {
                    drawWinners(numWinners);
                } else {
                    printf("Please enter a positive number.\n");
                }
                break;
                
            case 4:
                printf("Thank you for using the Lottery Simulator!\n");
                printf("Final participants remaining: %d\n", queue_count);
                exit(0);
                
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    
    return 0;
}