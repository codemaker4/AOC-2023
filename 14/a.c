#include <assert.h>
#include <stdio.h>
#include <string.h>
#define BUFSIZE 1024

typedef char chargrid[BUFSIZE][BUFSIZE];

void chargrid_print(chargrid grid, int cols, int rows) {
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            putchar(grid[row][col]);
        }
        putchar('\n');
    }
}

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

    int sum;

    for (int col = 0; col < cols; col++) {
        grid_roll_north(grid, col, rows);
        sum += calc_col_load(grid, col, rows);
    }

    printf("%d\n", sum);

    return 0;
}