#include <assert.h>
#include <stdio.h>
#include <string.h>
#define BUFSIZE 1024

typedef char chargrid[BUFSIZE][BUFSIZE];

// Modify the column of the grid simulating that all the round rocks roll north.
void grid_roll_north(chargrid grid, int col, int rows) {
    for (int row = 1; row < rows; row++) {
        // If there is a round rock here, try to roll it north
        if (grid[row][col] == 'O') {
            int row_roll = row;
            while (row_roll > 0 && grid[row_roll - 1][col] == '.') {
                grid[row_roll][col] = '.';
                grid[row_roll - 1][col] = 'O';
                row_roll --;
            }
        }
    }
}

void grid_rotate_left(chargrid grid, int *cols, int *rows) {
    chargrid temp;
    for (int row = 0; row < *rows; row++) {
        for (int col = 0; col < *cols; col++) {
            temp[col][*rows - row - 1] = grid[row][col];
        }
    }

    int rows_temp = *rows;
    *rows = *cols;
    *cols = rows_temp;

    for (int row = 0; row < *rows; row++) {
        for (int col = 0; col < *cols; col++) {
            grid[row][col] = temp[row][col];
        }
    }
}

// Calculate the load of the column.
int calc_col_load(chargrid grid, int col, int rows) {
    int sum = 0;

    for (int row = 0; row < rows; row++) {
        if (grid[row][col] == 'O') {
            sum += rows - row;
        }
    }

    return sum;
}

// Do rock rolling and rotating.
void grid_cycle(chargrid grid, int rows, int cols) {
    for (int i = 0; i < 4; i++) {
        for (int col = 0; col < cols; col++) {
            grid_roll_north(grid, col, rows);
        }
        grid_rotate_left(grid, &cols, &rows);
    }
}

int main(void) {
    char line[BUFSIZE];
    chargrid grid;
    int cols = 0;
    int rows = 0;

    while (fgets(line, BUFSIZE, stdin)) {
        if (line[0] == '\n' || line[0] == '\0') {
            continue;
        }

        memcpy(&grid[rows], line, sizeof(char) * strlen(line));
        rows++;
        cols = strlen(line) - 1; // remove \n.
    }

    int history[BUFSIZE];
    int history_len = 0;

    for (int i = 0; i < 1000000000; i++) {
        grid_cycle(grid, rows, cols);
        int sum = 0;
        for (int col = 0; col < cols; col++) {
            sum += calc_col_load(grid, col, rows);
        }
        history[history_len] = sum;
        history_len++;


        for (int pattern_len = 10; pattern_len < history_len / 2; pattern_len++) {
            int is_match = 1;
            for (int j = 0; j < pattern_len; j++) {
                if (history[history_len - j - 1] != history[history_len - pattern_len - j - 1]) {
                    is_match = 0;
                    break;
                }
            }
            if (is_match) {
                int cycles_left = (1000000000 - history_len) % pattern_len;
                printf("%d\n", history[history_len - pattern_len + cycles_left - 1]);
                return 0;
            }
        }
    }

    // Just in case it never repeats for some reason.
    int sum = 0;
    for (int col = 0; col < cols; col++) {
        sum += calc_col_load(grid, col, rows);
    }
    printf("%d\n", sum);
    
    return 0;
}