//
// Created by armandouv on 27/12/21.
//

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    if (argc == 1) return 0;
    for (int i = 1; i < argc; i++) {
        char *current_filename = argv[i];
        FILE *fp = fopen(current_filename, "r");
        if (fp == NULL) {
            printf("wcat: cannot open file\n");
            exit(1);
        }

        char *buffer = malloc(sizeof(char) * 20);
        while (fgets(buffer, 20, fp) != NULL) {
            printf("%s", buffer);
        }
    }
    return 0;
}