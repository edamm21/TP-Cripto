#include "args_parser.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <unistd.h>
#include "config.h"

static void usage() {
    fprintf(stderr,
            "Usage: [OPTION]...\n"
            "\n");
    exit(1);
}

static void version(void) {
    fprintf(stderr, "TP Criptografia\n"
                    "ITBA Criptografia y Seguridad 2021/Q1\n");
}

static void parseType(char * arg, char * type) {
    if(strcmp(arg, "d") != 0 && strcmp(arg, "k") != 0) {
        fprintf(stderr, "First argument should be either d or k. Try h for help");
        exit(1);
    } else {
        *type = *arg;
        return;
    }
}

static void parseString(char * src, char * dest) {
    strcpy(dest, src);
}

static void parseK(char * arg, int * type) {
    int k = atoi(arg);
    if(k < 4 || k > 6) {
        fprintf(stderr, "K value should be between 4 and 6. Try h for help.\n");
        exit(1);
    } else {
        *type = k;
        return;
    }
}

static void checkFileExistence(char * path) {
    FILE * f = fopen(path, "r");
    if(f == NULL) {
        fprintf(stderr, "File does not exist. Check file path.\n");
        exit(1);
    }
    fclose(f);
}

static void checkDirectory(char * path) {
    DIR * d = opendir(path);
    if(d == NULL || errno == ENOENT) {
        fprintf(stderr, "Directory does not exist. Check path.\n");
        exit(1);
    }
    closedir(d);
}

// [d-k] [file] [k] [directory]
// [h] <- help
void parseArgs(int argc, char **argv, struct config * config) {
    if(argc == 1) {
        fprintf(stderr, "Arguments needed to execute. Try h for help.\n");
        exit(1);
    } else if(argc == 2 && strcmp(argv[1], "h") == 0) {
        usage();
        exit(0);
    } else if(argc == 5) {
        for(int i = 0 ; i < 4 ; i++) {
            switch (i) {
                case 0:
                    parseType(argv[i + 1], &config->type);
                    break;
                case 1:
                    parseString(argv[i + 1], config->imageFile);
                    break;
                case 2:
                    parseK(argv[i + 1], &config->k);
                    break;
                case 3:
                    parseString(argv[i + 1], config->directory);
                    break;
                default:
                    break;
            }
        }
        if(config->type == 'd') {
            checkFileExistence(config->imageFile);
        }
        checkDirectory(config->directory);
        return;
    } else {
        fprintf(stderr, "Error in arguments passed. Try h for help.\n");
        exit(1);
    }
}
