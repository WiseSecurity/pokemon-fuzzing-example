// Compilation: AFL_USE_ASAN=1 afl-clang-fast -g pokemon_dirty.c -o pokemon_dirty
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/errno.h>

#define MAX_NAME 32

void usage(char *argv0) {
    fprintf(stderr, "Usage: %s <filename with some Pokemon (TM) name*>\n(and please, please don't use dirty words)\n", argv0);
}

int check_abuse(char *name) {
    if (strcasestr(name, "KURW")) {
        return 1;
    }
    else if (strcasestr(name, "FUC")) {
        return 1;
    }
    return 0;
}

int main(int argc, char **argv) {
    FILE *fp;
    char *buff;

    if (argc != 2) {
        usage(*argv);
        return -1;
    }

    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        fprintf(stderr, "Cannot open file %s: %s\n", argv[1], strerror(errno));
        return -1;
    }

    buff = (char*)malloc(MAX_NAME);
    fgets(buff, MAX_NAME, fp);
    buff[strcspn(buff, "\n")] = 0;

    if (check_abuse(buff)) {
        fprintf(stderr, "Some dirty name found :(\n");
        // let's clean memory
        free(buff);
        // and teach user how to use this program
        usage(*argv);
    }

    free(buff);
    return 0;
}
