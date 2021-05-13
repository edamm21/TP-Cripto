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
    //uint8_t dividedInBlocks[blockCount][bytesCount];
    uint8_t ** dividedInBlocks = malloc(blockCount * sizeof(uint8_t*));
    dividedInBlocks[0] = malloc(bytesCount * sizeof(uint8_t));
    int correspondingBlock = 0;
    for(int i = 0 ; i < L ; i++) {
        int correspondingElementInBlock = i % (bytesCount);
        dividedInBlocks[correspondingBlock][correspondingElementInBlock] = bitmap[i];
        if(correspondingElementInBlock == (bytesCount - 1)) {
            dividedInBlocks[++correspondingBlock] = malloc(bytesCount * sizeof(uint8_t));
        }
    }
    const long matrixCount = L / 4;
    uint8_t *** shades = readShadeFiles(config->shadeCount, config->shadeNames, config->directory);
    distributeImage(dividedInBlocks, shades, blockCount, config->shadeCount, matrixCount, config->k);
    // Para no olvidarnos
    free(headerStruct);
    freeShadeMatrix(shades, config->shadeCount, matrixCount);
}

uint8_t *** readShadeFiles(int shadeCount, char * shadeNames[MAX_SHADE_COUNT], char * directory) {
    uint8_t *** shades = malloc(shadeCount * sizeof(uint8_t**));
    for(int i = 0 ; i < shadeCount ; i++) {
        long fileSize;
        char * completePath = malloc(strlen(directory) + strlen(shadeNames[i]) + 1);
        strcpy(completePath, directory);
        strcat(completePath, shadeNames[i]);
        uint8_t * fileData = readFile(completePath, &fileSize);
        if(fileData == NULL)
            return NULL;
        struct header * headerStruct = parseHeader(fileData);
        if(headerStruct == NULL) {
            free(fileData);
            fprintf(stderr, "Error creating header structure from BMP image!");
            return NULL;
        }
        long L = fileSize - headerStruct->dataOffset;
        uint8_t * bitmap = fileData + headerStruct->dataOffset;
        int numberOfXWYZMatrices = L / 4;
        shades[i] = malloc(sizeof(uint8_t*) * numberOfXWYZMatrices);
        for(int blockCount = 0 ; blockCount < numberOfXWYZMatrices ; blockCount++) {
            int ul = blockCount * 2;
            int ur = ul + 1;
            int bl = ul + headerStruct->width;
            int br = bl + 1;
            shades[i][blockCount] = malloc(sizeof(uint8_t) * 4);
            shades[i][blockCount][0] = bitmap[ul];
            shades[i][blockCount][1] = bitmap[ur];
            shades[i][blockCount][2] = bitmap[bl];
            shades[i][blockCount][3] = bitmap[br];
        }
        free(completePath);
        free(fileData);
        free(headerStruct);
    }
    return shades;
}

void distributeImage(uint8_t ** blocks, uint8_t *** shades, long blockCount, int shadeCount, long innerMatrixCount, int k) {
    for(int blockIndex = 0 ; blockIndex < blockCount ; blockIndex++) {
        for (int shadeIndex = 0; shadeIndex < shadeCount; shadeIndex++) {
            for(int innerMatrixIndex = 0 ; innerMatrixIndex < innerMatrixCount ; innerMatrixIndex++) {
                uint8_t X_i_j = shades[shadeIndex][innerMatrixIndex][0];
                char * F_X_i_j = evaluatePolynomial(blocks[blockIndex], X_i_j, k);
                char p = calculateParityBit(F_X_i_j);
                for(int bit = 0 ; bit < 8 ; bit++) {
                    if(bit < 3)
                        insertIntoLeastSignificantBits(F_X_i_j[bit], bit % 3, &shades[shadeIndex][innerMatrixIndex][1]);
                    else if(bit < 6)
                        insertIntoLeastSignificantBits(F_X_i_j[bit], bit % 3, &shades[shadeIndex][innerMatrixIndex][2]);
                    else
                        insertIntoLeastSignificantBits(F_X_i_j[bit], (bit + 1) % 3, &shades[shadeIndex][innerMatrixIndex][3]);
                }
                insertIntoLeastSignificantBits(p, 0, &shades[shadeIndex][innerMatrixIndex][3]);
                free(F_X_i_j);
            }
        }
    }
}

// TODO
void insertIntoLeastSignificantBits(char bit, int index, uint8_t * cell) {
    char * bits = intToBinary(*cell);
    bits[5 + index] = bit;
    *cell = binaryToInt(bits);
    free(bits);
}