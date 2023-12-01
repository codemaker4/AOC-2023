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

// Gets the first digit in a string, -1 if there is no digit
// "as1ce2or3cs" -> 1
int first_digit(char* str) {
    char *c = str;
    while (*c != '\0') {
        if (digit(*c) != -1) {
            return digit(*c);
        }
        c++;
    }

    return -1;
}

// Gets the last digit in a string, -1 if there is no digit
// "as1ce2or3cs" -> 3
int last_digit(char* str) {
    char *c = str + strlen(str);
    while (c >= str) {
        if (digit(*c) != -1) {
            return digit(*c);
        }
        c--;
    }

    return -1;
}

// Checks if str starts with prefix
// "asd" "asd123" -> 1
// "asd" "123asd" -> 0
// "asd123" "asd" -> 0
// "asd" "asd" -> 1
int is_prefix(char *prefix, char *str) {
    while (*prefix != '\0' && *str != '\0') {
        if (*prefix != *str) {
            return 0;
        }
        prefix++;
        str++;
    }

    return *prefix == '\0';
}

// replaces first char of a written digit with its digit character.
// xxxoneightx -> xxx1n8ightx
void replace_nums(char *str) {
    const char nums[][BUFSIZE] = {
        "one", "two", "three", "four", "five",
        "six", "seven", "eight", "nine"
    };

    while (*str != '\0') {
        for (int i = 0; i < 9; i++) {
            if (is_prefix((char*) nums[i], str)) {
                *str = '1' + i;
                break;
            }
        }
        str++;
    }
}

int main(void) {
    char line[BUFSIZE];
    int sum = 0;

    while (fgets(line, BUFSIZE, stdin)) {
        replace_nums(line);
        sum += first_digit(line) * 10 + last_digit(line);
    }

    printf("%d\n", sum);
    return 1;
}