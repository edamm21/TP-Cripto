#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include "config.h"
#include "args_parser.h"
#include "custom_print.h"



static void help() {
    printlgu("\nDistribution mode mandatory parameters:\n");
    printlnb("d: ");
    printlnu("Indicates that distribution mode will be used.\n");
    printlnb("file.bmp: ");
    printlnu("File name with '.bmp' extension. It is the image to distribute.\n");
    printlnb("k: ");
    printlnu("Integer number between 4 and 6. Represents the minimum amount of shadows needed to retrieve the secret in a (k, n) scheme. \n");
    printlnb("directory: ");
    printlnu("Directory with the images used to distribute the secret. Must contain images with a '.bmp' extension, 8 bits per pixel and equal in size to the secret image.\n");
    printlnb("\nExample:\n");
    printlcn("./TP_Cripto d imageToHide.bmp 4 images/\n");

    printlgu("\nRecovery mode mandatory parameters:\n");
    printlnb("r: ");
    printlnu("Indicates that the recovery mode will be used.\n");
    printlnb("file.bmp: ");
    printlnu("File name with '.bmp' extension. Will contain the secret image revealed at the end of the program execution.\n");
    printlnb("k: ");
    printlnu("Integer number between 4 and 6. Represents the minimum amount of shadows needed to retrieve the secret in a (k, n) scheme. \n");
    printlnb("directory: ");
    printlnu("Directory with the images that contain the secret. Must contain images with a '.bmp' extension, 8 bits per pixel and equal in size to the secret image. \n");
    printlnb("\nExample:\n");
    printlcn("./TP_Cripto r imageRevealed.bmp 4 images/\n");
    exit(1);
}

static void version(void) {
    fprintf(stderr, "TP Criptografia\n"
                    "ITBA Criptografia y Seguridad 2021/Q1\n");
}

static void parseType(char * arg, char * type) {
    if(strcmp(arg, "d") != 0 && strcmp(arg, "r") != 0) {
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

static int checkDirectory(struct config * config) {
    DIR * d = opendir(config->directory);
    if(d == NULL || errno == ENOENT) {
        fprintf(stderr, "Directory does not exist. Check path.\n");
        exit(1);
    }
    struct dirent * dir;
    int fileCount = 0;
    while((dir = readdir(d)) != NULL) {
        if(strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0) {
            fileCount++;
            if(fileCount == MAX_SHADE_COUNT) break;
            config->shadeNames[fileCount - 1] = malloc(strlen(dir->d_name) + 1);
            strcpy(config->shadeNames[fileCount - 1], dir->d_name);
        }
    }
    closedir(d);
    return fileCount;
}

// [d-r] [file] [k] [directory]
// [h] <- help
void parseArgs(int argc, char **argv, struct config * config) {
    if(argc == 1) {
        fprintf(stderr, "Arguments needed to execute. Try h for help.\n");
        exit(1);
    } else if(argc == 2 && strcmp(argv[1], "h") == 0) {
        help();
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
        config->shadeCount = checkDirectory(config);
        if(config->shadeCount < config->k) {
            fprintf(stderr, "Not enough shades to run process. Check shade directory.\nGiven k: %d, shades provided: %d\n",
                    config->k, config->shadeCount);
            exit(1);
        }
        return;
    } else {
        fprintf(stderr, "Error in arguments passed. Try h for help.\n");
        exit(1);
    }
}
