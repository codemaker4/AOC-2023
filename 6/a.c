#include <inttypes.h>
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

int mils_traveled(int mils_button, int mils_time) {
    mils_time -= mils_button;
    return mils_button * mils_time;
}

int main(void) {
    char line[BUFSIZE];

    // Get race max time data
    int races = 0;
    int maxtimes[BUFSIZE];
    
    fgets(line, BUFSIZE, stdin);
    char *ptr = line;

    while (*ptr != '\0') {
        int num = read_int(&ptr);
        if (num != -1) {
            maxtimes[races] = num;
            races++;
        }
    }

    // Get race distance data
    races = 0;
    int distances[BUFSIZE];
    
    fgets(line, BUFSIZE, stdin);
    ptr = line;

    while (*ptr != '\0') {
        int num = read_int(&ptr);
        if (num != -1) {
            distances[races] = num;
            races++;
        }
    }

    // Calculate amount of button presses that are long enough
    int options = 1;

    for (int i = 0; i < races; i++) {
        int sum = 0;
        for (int j = 1; j < maxtimes[i]; j++) {
            printf("race: dist: %d, maxtime: %d, presstime: %d, distdone: %d\n", distances[i], maxtimes[i], j, mils_traveled(j, maxtimes[i]));
            if (mils_traveled(j, maxtimes[i]) > distances[i]) {
                sum ++;
            }
        }
        options *= sum;
        printf("sum: %d\n\n", sum);
    }

    printf("%d\n", options);

    return 0;
}