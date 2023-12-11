#include <stdio.h>
#include <string.h>
#define BUFSIZE 1024

// Shifts the array over by 1. *arr is a ptr to the start of the element that gets duplicated during
// the shift, and len is the length of this sub array.
// 1234 -> 11234, len = 4
void galaxy_shift(int *arr, int len) {
    for (int i = len; i > 0; i--) {
        arr[i] = arr[i-1];
    }
}

// Process the axis of galaxies, including the expansion. Returns the sum of the distances.
int process_axis(int *arr, int len) {
    // Process expansion of empty space. Also calculate the sum of galaxies while we are at it.
    int galaxies_dists_right = 0;
    int galaxies_right = 0;
    for (int i = len - 1; i >= 0; i--) {
        if (arr[i] == 0) {
            galaxy_shift(&arr[i], len - i);
            len++;
            galaxies_dists_right += galaxies_right;
        } else if (i != 0) {
            galaxies_dists_right += arr[i] * i;
            galaxies_right += arr[i];
        }
    }

    // Calculate the total distances. Only right side to calculate each pair once.
    int total = 0;
    for (int i = 0; i < len; i++) {
        total += galaxies_dists_right * arr[i];
        galaxies_dists_right -= galaxies_right;
        galaxies_right -= arr[i+1];
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
    int sum = 0;
    sum += process_axis(galaxy_cols, col);
    sum += process_axis(galaxy_rows, row);

    printf("%d\n", sum);

    return 0;
}