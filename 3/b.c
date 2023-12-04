#include <stdio.h>
#include <string.h>
#define BUFSIZE 1024

// Returns the digit as an int, or -1 if it is not a digit.
int digit(char c) {
    int digit = (int) c - '0';
    if (digit >= 0 && digit <= 9) {
        return digit;
    } else {
        return -1;
    }
}

// Reads an integer from the start of the string, and sets the pointer to the first non-digit char.
// Returns the integer, or -1 if the string did not start with a valid int.
int read_int(char **str) {
    int num = -1;

    while (1) {
        int digit_read = digit(**str);
        if (digit_read == -1) {
            if (num == -1) {
                (*str)++;
            }
            return num;
        }
        if (num == -1) {
            num = digit_read;
        } else {
            num *= 10;
            num += digit_read;
        }
        (*str)++;
    }
}

int main(void) {
    char line[BUFSIZE];
    char input[BUFSIZE][BUFSIZE];
    int row = 0;
    int col = 0;

    // Get input into 2d array
    while (fgets(line, BUFSIZE, stdin)) {
        if (line[0] == '\n' || line[0] == '\0') {
            continue;
        }
        strcpy(input[row], line);
        input[row][strlen(line) - 1] = '\0';
        col = strlen(input[row]);
        row++;
    }

    const int rows = row;
    const int cols = col;
    int sum = 0;

    // For each char in the 2d array:
    for (row = 0; row < rows; row++) {
        for (col = 0; col < cols; col++) {
            // If it is a gear...
            if (input[row][col] != '*') {
                continue;
            }

            // Find numbers near it.
            int ratio = -1;
            for (int srow = row - 1; srow <= row + 1; srow++) {
                int scol = col - 1;
                if (srow < 0 || srow >= rows || scol < 0) {
                    continue;
                }

                // Numbers might have already started further back.
                while (digit(input[srow][scol]) != -1) {
                    scol--;
                }
                scol++;

                for (scol = scol; scol <= col + 1 && scol < cols; scol++) {
                    char* ptr = &input[srow][scol];
                    int num = read_int(&ptr);

                    // If a number was found, and it was the second number, add the ratio.
                    if (num != -1) {
                        int len = ptr - &input[srow][scol];
                        scol += len - 1;
                        if (ratio == -1) {
                            ratio = num;
                        } else {
                            sum += ratio * num;
                        }
                    }
                }
            }
        }
    }

    printf("SUM: %d\n", sum);


    return 0;
}