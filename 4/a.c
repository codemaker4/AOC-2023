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
    int sum = 0;

    while (fgets(line, BUFSIZE, stdin)) {
        if (line[0] == '\n' || line[0] == '\0') {
            continue;
        }

        printf("READING:\n%s", line);
        
        char *ptr = line;
        while (*ptr != ':') {
            ptr++;
        }
        ptr += 2;
        int have_nums[BUFSIZE];
        int have_nums_count = 0;

        while (*ptr != '|') {
            have_nums[have_nums_count] = read_int_len(&ptr, 2);
            printf("%d ", have_nums[have_nums_count]);
            have_nums_count++;
            ptr++; // skip space after num
        }
        
        ptr += 2; // skip "| "
        int score = 0;

        printf("\nHAVE_NUMS: %d\n", have_nums_count);
        printf("SCORING:\n");

        while (*ptr != '\0') {
            int win_num =  read_int_len(&ptr, 2);
            printf("%d ", win_num);
            
            for(int i = 0; i < have_nums_count; i++) {
                if (win_num == have_nums[i]) {
                    score = score == 0 ? 1 : score * 2;
                    printf(":)%d ", score);
                }
            }

            ptr++; // skip space after num
        }

        sum += score;

        printf("\nSCORE: %d\n", score);
    }

    printf("%d\n", sum);

    return 0;
}