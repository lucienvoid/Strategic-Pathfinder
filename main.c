#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "maze.h"
#include "queue.h"
#include "solver.h"

// Function to handle manual movement mode
void manual_mode(char maze[MAZE_SIZE][MAZE_SIZE]) {
    Position player = find_start(maze);
    Position end = find_end(maze);

    if (player.row == -1) {
        printf("Start position not found!\n");
        return;
    }

    // Replace start position with player
    maze[player.row][player.col] = PLAYER;

    printf("=== MANUAL MODE ===\n");
    printf("Use WASD keys to move:\n");
    printf("W = Up, A = Left, S = Down, D = Right\n");
    printf("Q = Quit to main menu\n");
    printf("Goal: Reach the 'E' (end) position\n\n");

    char input;
    while (1) {
        print_maze(maze);

        // Check if player reached the end
        if (player.row == end.row && player.col == end.col) {
            printf("Congratulations! You reached the end!\n");
            break;
        }

        printf("Current position: (%d, %d)\n", player.row, player.col);
        printf("Enter move (WASD) or Q to quit: ");

        scanf(" %c", &input);
        input = toupper(input);

        if (input == 'Q') {
            printf("Returning to main menu...\n");
            break;
        }

        int new_row = player.row;
        int new_col = player.col;

        // Calculate new position based on input
        switch (input) {
            case 'W': // Up
                new_row = player.row - 1;
                break;
            case 'S': // Down
                new_row = player.row + 1;
                break;
            case 'A': // Left
                new_col = player.col - 1;
                break;
            case 'D': // Right
                new_col = player.col + 1;
                break;
            default:
                printf("Invalid input! Use W, A, S, D, or Q\n");
                continue;
        }

        // Check if the move is valid
        if (is_valid_move(maze, new_row, new_col)) {
            // Clear current position (but don't overwrite the end)
            if (maze[player.row][player.col] == PLAYER) {
                maze[player.row][player.col] = PATH;
            }

            // Move player to new position
            player.row = new_row;
            player.col = new_col;

            // Mark new position (but don't overwrite the end)
            if (maze[player.row][player.col] != END) {
                maze[player.row][player.col] = PLAYER;
            }

            printf("Moved successfully!\n");
        } else {
            printf("Invalid move! You can't move into walls or outside the maze.\n");
        }

        printf("\n");
    }
}

// Function to handle automatic BFS mode
void auto_mode(char maze[MAZE_SIZE][MAZE_SIZE]) {
    printf("=== AUTOMATIC BFS MODE ===\n");
    printf("The program will solve the maze using Breadth-First Search...\n\n");

    printf("Original maze:\n");
    print_maze(maze);

    if (solve_maze_bfs(maze)) {
        printf("\nSolved maze (path marked with '*'):\n");
        print_maze(maze);
        printf("Legend: S = Start, E = End, * = Solution Path\n");
    } else {
        printf("\nMaze could not be solved!\n");
    }
}

// Display the main menu
void show_menu() {
    printf("\n=== STRATEGIC PATHFINDING IN DISCRETE SPACES ===\n");
    printf("1. Manual Mode (Use WASD keys to navigate)\n");
    printf("2. Automatic Mode (BFS Algorithm)\n");
    printf("3. Exit\n");
    printf("Choose an option (1-3): ");
}

int main() {
    char maze[MAZE_SIZE][MAZE_SIZE];
    char original_maze[MAZE_SIZE][MAZE_SIZE];
    int choice;

    printf("Welcome to the Maze Solver!\n");
    printf("Generating a %dx%d maze...\n", MAZE_SIZE, MAZE_SIZE);

    // Generate the maze once
    generate_maze(original_maze);

    printf("\nMaze Legend:\n");
    printf("# = Wall\n");
    printf(". = Path\n");
    printf("S = Start\n");
    printf("E = End\n\n");

    while (1) {
        show_menu();

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Please enter a number.\n");
            // Clear input buffer
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
            case 1:
                // Reset maze for manual mode
                for (int i = 0; i < MAZE_SIZE; i++) {
                    for (int j = 0; j < MAZE_SIZE; j++) {
                        maze[i][j] = original_maze[i][j];
                    }
                }
                manual_mode(maze);
                break;

            case 2:
                // Reset maze for auto mode
                for (int i = 0; i < MAZE_SIZE; i++) {
                    for (int j = 0; j < MAZE_SIZE; j++) {
                        maze[i][j] = original_maze[i][j];
                    }
                }
                auto_mode(maze);
                break;

            case 3:
                printf("Thank you for using the Maze Solver!\n");
                printf("Goodbye!\n");
                return 0;

            default:
                printf("Invalid choice! Please select 1, 2, or 3.\n");
                break;
        }

        printf("\n");
    }

    return 0;
}
