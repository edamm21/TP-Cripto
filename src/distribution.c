#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <common/helper.h>
#include "distribution.h"
#include "config.h"
#include "header_parser.h"
#include "header_struct.h"

uint8_t * readFile(char * path, long * fileSize) {
    FILE * bmpImage = fopen(path, "rb");
    fseek(bmpImage, 0, SEEK_END);
    *fileSize = ftell(bmpImage);
    rewind(bmpImage);
    uint8_t * fileData = malloc(sizeof(uint8_t) * (*fileSize));
    size_t readBytes = fread(fileData, sizeof(uint8_t), *fileSize, bmpImage);
    fclose(bmpImage);
    if(readBytes != *fileSize) {
        free(fileData);
        return NULL;
    }
    return fileData;
}

void runDistribution(struct config * config) {
    long fileSize;
    uint8_t * fileData = readFile(config->imageFile, &fileSize);
    if(fileData == NULL)
        return;
    struct header * headerStruct = parseHeader(fileData);
    if(headerStruct == NULL) {
        free(fileData);
        fprintf(stderr, "Error creating header structure from BMP image!");
        return;
    }
    // Esta es la cantidad de datos en si de la imagen sin contar el header
    long L = fileSize - headerStruct->dataOffset;
    uint8_t * bitmap = fileData + headerStruct->dataOffset;

    // tengo que subdividir los datos secretos en bloques de k bytes
    int bytesCount = config->k;
    long blockCount = L / bytesCount; // L / k
    uint8_t dividedInBlocks[blockCount][bytesCount];
    int correspondingBlock = 0;
    for(int i = 0 ; i < L ; i++) {
        int correspondingElementInBlock = i % (bytesCount);
        dividedInBlocks[correspondingBlock][correspondingElementInBlock] = bitmap[i];
        if(correspondingElementInBlock == (bytesCount - 1)) {
            correspondingBlock++;
        }
    }

    uint8_t ** shades[config->shadeCount];
    readShadeFiles(shades, config->shadeCount, config->shadeNames, config->directory);

    // Para no olvidarnos
    free(headerStruct);
}

void readShadeFiles(uint8_t *** shades, int shadeCount, char * shadeNames[MAX_SHADE_COUNT], char * directory) {
    for(int i = 0 ; i < shadeCount ; i++) {
        long fileSize;
        char * completePath = malloc(strlen(directory) + strlen(shadeNames[i]) + 1);
        strcpy(completePath, directory);
        strcat(completePath, shadeNames[i]);
        uint8_t * fileData = readFile(completePath, &fileSize);
        if(fileData == NULL)
            return;
        struct header * headerStruct = parseHeader(fileData);
        if(headerStruct == NULL) {
            free(fileData);
            fprintf(stderr, "Error creating header structure from BMP image!");
            return;
        }
        long L = fileSize - headerStruct->dataOffset;
        uint8_t * bitmap = fileData + headerStruct->dataOffset;
        int numberOf2x2Matrices = L / 4;
        free(completePath);
        free(fileData);
        free(headerStruct);
    }
}