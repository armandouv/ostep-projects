//
// Created by armandouv on 29/12/21.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool contains_substring(char *line, char *substring, size_t substring_size);
bool naive(char *line, char *substring, size_t m);
bool karp_rabin(char *line, char *substring, size_t m);

int power_modulus(int base, int power, int mod);

bool finite_automata(char *line, char *substring, size_t m);
bool knuth_morris_pratt(char *line, char *substring, size_t m);

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("wgrep: searchterm [file ...]\n");
        return 1;
    }

    char *search_term = argv[1];
    char *line = NULL;
    size_t line_size = 0;
    size_t search_term_size = strlen(search_term);


    // No files provided as arguments, read from stdin
    if (argc == 2) {
        while (getline(&line, &line_size, stdin) != -1) {
            if (contains_substring(line, search_term, search_term_size))
                printf("%s", line);
        }
    }

    for (int i = 2; i < argc; i++) {
        char *current_filename = argv[i];
        FILE *fp = fopen(current_filename, "r");
        if (fp == NULL) {
            printf("wgrep: cannot open file\n");
            return 1;
        }

        while (getline(&line, &line_size, fp) != -1) {
            if (contains_substring(line, search_term, search_term_size))
                printf("%s", line);
        }
    }

    free(line);
    return 0;
}

bool contains_substring(char *line, char *substring, size_t substring_size) {
    return naive(line, substring, substring_size);
    //return karp_rabin(line, substring, substring_size);
    //return finite_automata(line, substring, substring_size);
    //return knuth_morris_pratt(line, substring, substring_size);
}



// String matching algorithms

bool naive(char *line, char *substring, size_t m) {
    if (*line == 0) return false;
    if (*substring == 0) return true;

    char *current = line;
    bool end_of_line_reached = false;

    while (!end_of_line_reached) {
        for (int i = 0; i < m; i++) {
            char current_line_char = *(current + i);
            char current_substring_char = *(substring + i);

            // Check if end of line
            if (!current_line_char) {
                end_of_line_reached = true;
                break;
            }
            // Current characters do not match
            if (current_line_char != current_substring_char) break;
            // All characters match
            if (i == m - 1) return true;
        }
        current++;
    }

    return false;
}

bool karp_rabin(char *line, char *substring, size_t m) {
    int q = 7919;
    int h = power_modulus(255, m - 1, q);

    return false;
}

bool finite_automata(char *line, char *substring, size_t m) {
    return false;
}

bool knuth_morris_pratt(char *line, char *substring, size_t m) {
    return false;
}

// (mod-1)² must fit in an int
int power_modulus(int base, int power, int mod) {
    if (power == 1) return base % mod;
    int half = power / 2;
    return (power_modulus(base, half, mod) * power_modulus(base, power - half, mod)) % mod;
}
