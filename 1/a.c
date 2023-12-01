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


// Gets the first digit in a string
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

// Gets the last digit in a string
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

int main(void) {
    char line[BUFSIZE];
    int sum = 0;

    while (fgets(line, BUFSIZE, stdin)) {
        sum += first_digit(line) * 10 + last_digit(line);
    }

    printf("%d\n", sum);
    return 1;
}