#include <stdio.h>
#include <string.h>
#define BUFSIZE 1024
#define EXPANSION 2

// Process the axis of galaxies, including the expansion. Returns the sum of the distances.
long process_axis(int *arr, int len) {
    // Calculate the total of the distances by keeping track of the total of the distances between
    // position i and all the galaxies to the right.
    long total = 0;
    long galaxies_dists_right = 0;
    long galaxies_right = 0;
    for (int i = len - 1; i >= 0; i--) {
        if (arr[i] == 0) {
            galaxies_dists_right += galaxies_right * EXPANSION;
        } else {
            total += galaxies_dists_right * arr[i];
            galaxies_right += arr[i];
            galaxies_dists_right += galaxies_right;
        }
    }

    return total;
}

int main(void) {
    // Read the input and count how many galaxies each row and col has.
    char line[BUFSIZE];
    int galaxy_cols[BUFSIZE] = {0};
    int galaxy_rows[BUFSIZE] = {0};
    int row = 0;
    int col = 0;

    while (fgets(line, BUFSIZE, stdin)) {
        if (line[0] == '\n' || line[0] == '\0') {
            continue;
        }

        for (col = 0; line[col] == '.' || line[col] == '#'; col++) {
            if (line[col] == '#') {
                galaxy_cols[col]++;
                galaxy_rows[row]++;
            }
        }

        row++;
    }

    // Because manhattan distances are used, each axis can be processed seperately. So for each
    // axis, process the expansion of empty space and then calculate the distances along that axis
    // for all the galaxies. The distance sums can be added together for the final answer.
    long sum = 0;
    sum += process_axis(galaxy_cols, col);
    sum += process_axis(galaxy_rows, row);

    printf("%ld\n", sum);

    return 0;
}