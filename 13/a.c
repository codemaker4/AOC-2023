#include <assert.h>
#include <stdio.h>
#include <string.h>
#define BUFSIZE 1024

typedef char chargrid[BUFSIZE][BUFSIZE];

// Modify the grid such that it is diagonally mirrored. Also swap the values in rows and cols.
void chargrid_diagonal(chargrid grid, int *cols, int *rows) {
    chargrid temp;
    for (int row = 0; row < *rows; row++) {
        for (int col = 0; col < *cols; col++) {
            temp[col][row] = grid[row][col];
        }
    }

    int old_cols = *cols;
    *cols = *rows;
    *rows = old_cols;

    for (int row = 0; row < *rows; row++) {
        for (int col = 0; col < *cols; col++) {
            grid[row][col] = temp[row][col];
        }
    }
}

// Returns 1 if the grid is fully horisontally mirrored.
int is_horisontally_mirrored(chargrid grid, int cols, int rows) {
    if (rows % 2 != 0) {
        return 0;
    }

    for (int i = 0; i < rows / 2; i++) {
        if (strncmp(grid[i], grid[rows - i - 1], cols)) {
            return 0;
        }
    }

    return 1;
}

// Calculate if and where the grid has a horisontal mirror plane.
// Returns the amount of rows above the mirror plane, and 0 if it does not mirror.
int calc_mirror_horisontal(chargrid grid, int cols, int rows) {
    if (is_horisontally_mirrored(grid, cols, rows)) {
        return rows / 2;
    }

    for (int i = 1; i < rows - 1; i++) {
        if (is_horisontally_mirrored(grid, cols, rows - i)) {
            return (rows - i) / 2;
        }
        
        if (is_horisontally_mirrored(&grid[i], cols, rows - i)) {
            return (rows - i) / 2 + i;
        }
    }

    return 0;
}

// Calculate the mirror plane number of this grid. So either the number of rows above the horisontal
// mirror plane, or the cols to the left of the vertical mirror plane.
int calc_mirror_full(chargrid grid, int cols, int rows) {
    int sum = calc_mirror_horisontal(grid, cols, rows) * 100;
    chargrid_diagonal(grid, &cols, &rows);
    sum += calc_mirror_horisontal(grid, cols, rows);
    chargrid_diagonal(grid, &cols, &rows);
    return sum;
}

int main(void) {
    char line[BUFSIZE];
    chargrid grid;
    int cols = 0;
    int rows = 0;
    int sum = 0;

    while (fgets(line, BUFSIZE, stdin)) {
        if (line[0] == '\n' || line[0] == '\0') {
            int mirror_num = calc_mirror_full(grid, cols, rows);
            sum += mirror_num;
            printf("%d\n", mirror_num);
            cols = 0;
            rows = 0;
            continue;
        }

        memcpy(&grid[rows], line, sizeof(char) * strlen(line));
        rows++;
        cols = strlen(line) - 1; // remove \n.
    }

    assert(cols == 0);

    printf("%d\n", sum);

    return 0;
}