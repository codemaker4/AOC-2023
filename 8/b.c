#include <stddef.h>
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

// Calculates the greatest common divisor of a and b
long calc_gcd(long a, long b) {
    while (b != 0) {
        long temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

// Calculates the least common multiple of a and b
long calc_lcm(long a, long b) {
    return (a / calc_gcd(a, b)) * b;
}

#define NODENAMELEN 3
#define ALPHABET 26

typedef char nodename[NODENAMELEN] ;

typedef struct {
    nodename name;
    nodename left;
    nodename right;
} node;

typedef node node_array[ALPHABET * ALPHABET * ALPHABET];

// Convert capital letter char to its zero-indexed pos in the albphabet.
int char_to_int(char c) {
    return (int) c - 'A';
}

// Interprets a nodename as a base 26 number and returns that number.
int nodename_to_int(nodename nodename) {
    int num = 0;
    for (int i = 0; i < NODENAMELEN; i++) {
        num *= ALPHABET;
        num += char_to_int(nodename[i]);
    }
    return num;
}

// Check if two nodenames are equal. 1 of equal, 0 if different.
int nodename_eq(nodename a, nodename b) {
    for (int i = 0; i < NODENAMELEN; i++) {
        if (a[i] != b[i]) {
            return 0;
        }
    }
    return 1;
}

// Gets a node name and a node array and returns the address that a node with that name would have.
node *nodename_to_arr_ptr(node_array array, nodename nodename) {
    return &array[nodename_to_int(nodename)];
}

void set_node(node_array array, node n) {
    *nodename_to_arr_ptr(array, n.name) = n;
}

node *get_node(node_array array, nodename nodename) {
    return nodename_to_arr_ptr(array, nodename);
}

int main(void) {
    // Get the LR directions
    char directions[BUFSIZE];
    fgets(directions, BUFSIZE, stdin);

    // Read the nodes
    char line[BUFSIZE];
    node_array array;
    node *nodes_follow[BUFSIZE];
    int nodes_follow_count = 0;

    while (fgets(line, BUFSIZE, stdin)) {
        if (line[0] == '\n' || line[0] == '\0') {
            continue;
        }
        
        node node;
        memcpy(node.name, line, sizeof(nodename));
        memcpy(node.left, line + 7, sizeof(nodename));
        memcpy(node.right, line + 12, sizeof(nodename));
        set_node(array, node);

        // Keep track of the starting nodes as well
        if (node.name[NODENAMELEN - 1] == 'A') {
            nodes_follow[nodes_follow_count] = get_node(array, node.name);
            nodes_follow_count++;
        }
    }

    // Follow the different node paths and keep track of each path's length.
    char *ptr = line;
    int steps = 1;
    int periods[BUFSIZE] = {};
    int nodes_left = nodes_follow_count;

    while (nodes_left) {
        int is_right;
        switch (*ptr) {
            case 'L':
                is_right = 0;
                ptr++;
                break;
            case 'R':
                is_right = 1;
                ptr++;
                break;
            default:
                ptr = directions;
                continue;
        }

        for (int i = 0; i < nodes_follow_count; i++) {
            if (periods[i] != 0) {
                continue;
            }

            if (is_right) {
                nodes_follow[i] = get_node(array, nodes_follow[i]->right);
            } else {
                nodes_follow[i] = get_node(array, nodes_follow[i]->left);
            }

            if (nodes_follow[i]->name[NODENAMELEN - 1] == 'Z') {
                periods[i] = steps;
                nodes_left--;
            }
        }
        steps++;    
    }

    // The first time all the paths are done at the same time is equal to the LCM of the path
    // lengths. LCM is commutative, so a loop like this calculates the LCM of all the periods.
    long lcm = periods[0];

    for (int i = 1; i < nodes_follow_count; i++) {
        lcm = calc_lcm(lcm, periods[i]);
    }

    printf("%ld\n", lcm);

    return 0;
}