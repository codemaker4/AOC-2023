#include <assert.h>
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

#define CARD_COUNT 13

int card_to_rank(char card) {
    char cards[] = "23456789TJQKA";
    for (int i = 0; i < CARD_COUNT; i++) {
        if (cards[i] == card) {
            return i;
        }
    }
    assert(0);
}

#define HANDSIZE 5
typedef char hand[HANDSIZE];

int hand_type(hand hand) {
    int found_ranks[HANDSIZE];
    int found_ranks_counts[HANDSIZE];
    int total_found_ranks = 0;
    int max_rank_count = 0;
    for (int i = 0; i < HANDSIZE; i++) {
        int was_found = 0;
        for (int j = 0; j < total_found_ranks; j++) {
            if (found_ranks[j] == card_to_rank(hand[i])) {
                found_ranks_counts[j] ++;
                if (found_ranks_counts[j] > max_rank_count) {
                    max_rank_count = found_ranks_counts[j];
                }
                was_found = 1;
                break;
            }
        }
        if (!was_found) {
            found_ranks[total_found_ranks] = card_to_rank(hand[i]);
            found_ranks_counts[total_found_ranks] = 1;
            total_found_ranks++;
            if (max_rank_count < 1) {
                max_rank_count = 1;
            }
        }
    }

    if (max_rank_count == 5 && total_found_ranks == 1) {
        return 6; // Five of a kind
    }

    if (max_rank_count == 4 && total_found_ranks == 2) {
        return 5; // Four of a kind
    }

    if (max_rank_count == 3 && total_found_ranks == 2) {
        return 4; // Full house
    }

    if (max_rank_count == 3 && total_found_ranks == 3) {
        return 3; // Three of a kind
    }

    if (max_rank_count == 2 && total_found_ranks == 3) {
        return 2; // Two pair
    }

    if (max_rank_count == 2 && total_found_ranks == 4) {
        return 1; // One pair
    }

    if (max_rank_count == 1 && total_found_ranks == 5) {
        return 0; // High card
    }

    assert(0);
}

// Returns a score number that is unique for each distinct hand that can be used to sort the hand
int hand_to_score(hand hand) {
    int rank = hand_type(hand);

    for (int i = 0; i < HANDSIZE; i++) {
        rank *= CARD_COUNT;
        rank += card_to_rank(hand[i]);
    }

    return rank;
}

typedef struct {
    hand hand;
    int score;
    int bid;
} hand_data;

hand_data read_hand(char *str) {
    hand_data hand;
    for (int i = 0; i < HANDSIZE; i++) {
        assert(*str != '\0');
        hand.hand[i] = *str;
        str++;
    }
    str++;
    hand.bid = read_int(&str);
    assert(hand.bid != -1);
    hand.score = hand_to_score(hand.hand);
    return hand;
}

typedef struct {
    hand_data hands[BUFSIZE];
    int hand_count;
} hand_array;

void hand_array_insert_sort(hand_array *array, hand_data hand_to_sort) {
    if (array->hand_count == BUFSIZE) {
        assert(0);
    }
    for (int i = 0; i < array->hand_count; i++) {
        hand_data temp = array->hands[i];
        if (temp.score > hand_to_sort.score) {
            array->hands[i] = hand_to_sort;
            hand_to_sort = temp;
        }
    }
    array->hands[array->hand_count] = hand_to_sort;
    array->hand_count++;
}

int main(void) {
    char line[BUFSIZE];
    hand_array array;
    array.hand_count = 0;

    // Read all the hands and sort them
    while (fgets(line, BUFSIZE, stdin)) {
        if (line[0] == '\n' || line[0] == '\0') {
            continue;
        }

        hand_array_insert_sort(&array, read_hand(line));
    }

    // Calculate the sum of the ranked bids
    int sum = 0;
    for (int i = 0; i < array.hand_count; i++) {
        sum += array.hands[i].bid * (i + 1);
    }

    printf("%d\n", sum);

    return 0;
}