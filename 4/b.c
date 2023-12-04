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

// Reads an integer from the start of the string for the given length. If a char is not a digit,
// it is read as a zero. Returns the integer read and sets the string pointer to the first char
// after the given length.
int read_int_len(char **str, int len) {
    int num = 0;

    for (int i = 0; i < len; i++) {
        int digit_read = digit(**str);
        if (digit_read == -1) {
            digit_read = 0;
        }
        num *= 10;
        num += digit_read;
        (*str)++;
    }

    return num;
}

int main(void) {
    char line[BUFSIZE];
    int scores[BUFSIZE];
    int copies[BUFSIZE];
    int games = 0;

    // Read all the scratchcards
    while (fgets(line, BUFSIZE, stdin)) {
        if (line[0] == '\n' || line[0] == '\0') {
            continue;
        }
        
        // Skip ptr to the first have_num  
        char *ptr = line;
        while (*ptr != ':') {
            ptr++;
        }
        ptr += 2;
        int have_nums[BUFSIZE];
        int have_nums_count = 0;

        // Put all the have_nums in an array
        while (*ptr != '|') {
            have_nums[have_nums_count] = read_int_len(&ptr, 2);
            have_nums_count++;
            ptr++;
        }
        
        ptr += 2; // skip "| "
        int score = 0;

        // Find win_nums in the have_nums array and calculate card score
        while (*ptr != '\0') {
            int win_num =  read_int_len(&ptr, 2);
            
            for(int i = 0; i < have_nums_count; i++) {
                if (win_num == have_nums[i]) {
                    score++;
                }
            }

            ptr++; // skip space after num
        }

        // Put scores and original copy of card in arrays
        scores[games] = score;
        copies[games] = 1;
        games++;
    }

    int sum = 0;

    // Calculate all card copies and the sum of the cards
    for (int i = 0; i < games; i++) {
        for (int j = i + 1; j <= i + scores[i]; j++) {
            copies[j] += copies[i];
        }
        sum += copies[i];
    }

    printf("%d\n", sum);

    return 0;
}