//
// Created by armandouv on 14/01/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


int BUFFER_SIZE = 512;

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("wzip: file1 [file2 ...]\n");
        return 1;
    }

    // Keep current_char in outer scope to handle the case when the last character of a file is the same as the first
    // of the next file. For example:
    // First file ends: ...aaa
    // Second file starts: aa...
    // Expected result: 5a, instead of 3a2a
    bool is_current_char_valid = false;
    char current_char;
    unsigned int current_char_count;
    char *buffer = malloc(sizeof(char) * BUFFER_SIZE);

    for (int i = 1; i < argc; i++) {
        char *current_filename = argv[i];
        FILE *fp = fopen(current_filename, "r");
        if (fp == NULL) {
            printf("wzip: cannot open file\n");
            return 1;
        }

        size_t bytes_read = fread(buffer, 1, BUFFER_SIZE, fp);

        while (bytes_read != 0) {
            int i = 0;

            if (!is_current_char_valid) {
                current_char = buffer[0];
                current_char_count = 1;
                is_current_char_valid = true;
                i = 1;
            }

            for (; i < bytes_read; ++i) {
                if (current_char == buffer[i]) {
                    current_char_count++;
                    continue;
                }
                // Flush count of previous character
                fwrite(&current_char_count, sizeof(unsigned int), 1, stdout);
                fwrite(&current_char, sizeof(char), 1, stdout);
                current_char = buffer[i];
                current_char_count = 1;
            }

            bytes_read = fread(buffer, 1, BUFFER_SIZE, fp);
        }

        fclose(fp);
    }

    // Flush last char read if exists
    if (is_current_char_valid) {
        fwrite(&current_char_count, sizeof(unsigned int), 1, stdout);
        fwrite(&current_char, sizeof(char), 1, stdout);
    }

    return 0;
}
