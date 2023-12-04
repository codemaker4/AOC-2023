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

            // If it is a number...
            char* ptr = &input[row][col];
            int num = read_int(&ptr);
            if (num != -1) {
                int len = ptr - &input[row][col];
                int should_be_counted = 0;

                // Search for symbols in the area.
                for (int srow = row - 1; srow <= row + 1; srow++) {
                    for (int scol = col - 1; scol <= col + len; scol++) {
                        if (srow < 0 || srow >= rows || scol < 0 || scol >= cols) {
                            continue;
                        }
                        char c = input[srow][scol];
                        if (c != '.' && c != 'x' && digit(c) == -1) {
                            should_be_counted = 1;
                        }
                    }
                }

                // If a symbol was found: add num to the sum and mark the number as already counted.
                if (should_be_counted) {
                    sum += num;
                    for (int wcol = col; wcol < col + len; wcol++) {
                        input[row][wcol] = 'x';
                    }
                }
            }
        }
    }

    printf("%d\n", sum);


    return 0;
}