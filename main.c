#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BOARD_SIZE 100
#define NUM_PLAYERS 4

// Structure to store player information
struct Player {
    char name[20];
    int position;
    struct Player *next;
};

// Function to roll the dice
int rollDice() {
    return (rand() % 6) + 1;
}

// Function to check for snakes and ladders
int checkSnakesAndLadders(int position, int* action) {
    // Define snake and ladder positions
    int snakePositions[] = {17, 52, 70, 80, 88, 92, 96};
    int ladderPositions[] = {3, 5, 11, 19, 21, 35, 39, 44, 49, 57, 64, 71};

    // Snake and Ladder positions using Switch case
    switch (position) {
        case 3:
            *action = 1; // 1 represents climbing a ladder
            return 22; // position to go
        case 5:
            *action = 1;
            return 8;
        case 11:
            *action = 1;
            return 26;
        case 17:
            *action = 2; // 2 represents falling down a snake
            return 4;
        case 19:
            *action = 1;
            return 7;
        case 21:
            *action = 1;
            return 66;
        case 35:
            *action = 1;
            return 67;
        case 39:
            *action = 2;
            return 3;
        case 44:
            *action = 1;
            return 95;
        case 49:
            *action = 1;
            return 93;
        case 52:
            *action = 2;
            return 11;
        case 70:
            *action = 1;
            return 36;
        case 73:
            *action = 1;
            return 12;
        case 80:
            *action = 2;
            return 15;
        case 88:
            *action = 1;
            return 47;
        case 92:
            *action = 2;
            return 35;
        case 96:
            *action = 1;
            return 77;
        default:
            for (int i = 0; i < sizeof(snakePositions) / sizeof(snakePositions[0]); i++) {
                if (position == snakePositions[i]) {
                    *action = 2;
                    return 4;
                }
            }

            for (int i = 0; i < sizeof(ladderPositions) / sizeof(ladderPositions[0]); i++) {
                if (position == ladderPositions[i]) {
                    *action = 1;
                    return 22;
                }
            }

            // When a player wins max position = 100
            if (position > 100) {
                *action = 0;
                return 100;
            }
            *action = 0;
            return position;
    }
}

// Function to display the leaderboard
void displayLeaderboard(struct Player *head) {
    printf("\nLeaderboard:\n");
    struct Player *current = head;
    while (current != NULL) {
        printf("Player %s is at position %d\n", current->name, current->position);
        current = current->next;
    }
}

int main() {
    srand(time(NULL));
    int numPlayers, numDice, difficulty;

    // Input the number of players
    printf("Enter the number of players (2-%d):", NUM_PLAYERS);
    scanf("%d", &numPlayers);

    if (numPlayers < 2 || numPlayers > NUM_PLAYERS) {
        printf("Invalid number of players. Please enter a number between 2 and %d.\n", NUM_PLAYERS);
        return 1;
    }

    // Input the difficulty level
    printf("Select difficulty level:\n");
    printf("1. Easy\n2. Medium\n3. Hard\n");
    printf("Enter your choice (1-3):");
    scanf("%d", &difficulty);

    if (difficulty < 1 || difficulty > 3) {
        printf("Invalid difficulty level. Please enter a number between 1 and 3.\n");
        return 1;
    }

    numDice = (difficulty == 1) ? 1 : (difficulty == 2) ? 2 : 3;

    // Initialize players
    struct Player *head = NULL;
    for (int i = 0; i < numPlayers; i++) {
        struct Player *newPlayer = (struct Player *) malloc(sizeof(struct Player));
        if (newPlayer == NULL) {
            printf("Memory allocation failed.\n");
            return 1;
        }
        printf("Enter name for Player %d:", i + 1);
        scanf("%s", newPlayer->name);
        newPlayer->position = 1;
        newPlayer->next = head;
        head = newPlayer;
    }

    // Main game loop
    int winner = -1;
    while (winner == -1) {
        struct Player *current = head;
        while (current != NULL) {
            printf("\n%s's turn. Press enter to roll the dice.", current->name);
            getchar();
            getchar();
            int diceRoll = 0;
            for (int j = 0; j < numDice; j++) {
                diceRoll += rollDice();
            }
            printf("%s rolled a %d.\n", current->name, diceRoll);
            int action;
            int newPosition = checkSnakesAndLadders(current->position + diceRoll, &action);
            if (action == 1) {
                printf("%s climbed a ladder!\n", current->name);
            } else if (action == 2) {
                printf("%s fell down a snake!\n", current->name);
            }
            current->position = newPosition;

            // Update winner
            if (current->position == BOARD_SIZE) {
                winner = 1;
                break;
            }

            // Display player's position
            printf("%s is now at position %d.\n", current->name, current->position);

            current = current->next;
        }
    }

    // Display the winner
    struct Player *winnerPlayer = head;
    while (winnerPlayer != NULL) {
        if (winnerPlayer->position == BOARD_SIZE) {
            printf("\nCongratulations, %s is the winner!\n", winnerPlayer->name);
            break;
        }
        winnerPlayer = winnerPlayer->next;
    }

    // Display the leaderboard
    displayLeaderboard(head);
    
    struct Player *current = head;
    while (current != NULL) {
        struct Player *next = current->next;
        free(current);
        current = next;
    }

    return 0;
}
