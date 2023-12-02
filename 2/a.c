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
    int sum = 0;
    int game_id = 1;
    int red_max = 12;
    int green_max = 13;
    int blue_max = 14;

    while (fgets(line, BUFSIZE, stdin)) {
        // example line = Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green
        if (*line != 'G') {
            continue;
        }
        
        char* ptr = line + 5;
        read_int(&ptr);
        ptr += 2;

        int game_going = 1;
        while (game_going) {
            int num = read_int(&ptr);
            ptr++; // skip space after num
            switch (*ptr) {
                case 'r':
                    if (num > red_max) {
                        game_going = 0;
                    }
                    ptr += 3;
                    break;
                case 'g':
                    if (num > green_max) {
                        game_going = 0;
                    }
                    ptr += 5;
                    break;
                case 'b':
                    if (num > blue_max) {
                        game_going = 0;
                    }
                    ptr += 4;
                    break;
            }

            if (*ptr == ',' || *ptr == ';') {
                ptr += 2;
            } else {
                break;
            }
        }

        if (game_going == 1) {
            sum += game_id;
        }
        
        game_id++;
    }

    printf("%d\n", sum);
    return 0;
}