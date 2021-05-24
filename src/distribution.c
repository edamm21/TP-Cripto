#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <common/helper.h>
#include <stdbool.h>
#include <math.h>
#include "distribution.h"
#include "config.h"
#include "header_parser.h"
#include "header_struct.h"

void runDistribution(struct config *config) {
    long fileSize;
    uint8_t *fileData = readFile(config->imageFile, &fileSize);
    if (fileData == NULL)
        return;
    struct header *headerStruct = parseHeader(fileData);
    if (headerStruct == NULL) {
        free(fileData);
        fprintf(stderr, "Error creating header structure from BMP image!");
        return;
    }
    // Esta es la cantidad de datos en si de la imagen sin contar el header
    long L = fileSize - headerStruct->dataOffset;
    uint8_t *bitmap = fileData + headerStruct->dataOffset;

    // tengo que subdividir los datos secretos en bloques de k bytes
    int bytesCount = config->k;
    long blockCount = L / bytesCount; // L / k
    //uint8_t dividedInBlocks[blockCount][bytesCount];
    uint8_t **dividedInBlocks = malloc(blockCount * sizeof(uint8_t *));
    for(int i = 0 ; i < blockCount ; i++) {
        dividedInBlocks[i] = calloc(config->k, sizeof(uint8_t)); // relleno con 0s
        for(int j = 0 ; j < config->k ; j++) {
            dividedInBlocks[i][j] = bitmap[i * config->k + j];
        }
    }
    const long matrixCount = L / 4;
    uint8_t ***shades = readShadeFiles(config->shadeCount, config->shadeNames, config->directory);
    distributeImage(dividedInBlocks, shades, blockCount, config->shadeCount, matrixCount, config->k);
    writeOutputFile(shades, config, headerStruct, fileData, (int)L);
    // Para no olvidarnos
    free(headerStruct);
    freeShadeMatrix(shades, config->shadeCount, matrixCount);
}

void distributeImage(uint8_t **blocks, uint8_t ***shades, long blockCount, int shadeCount, long innerMatrixCount, int k) {
    // TODO: CHECK IF BLOCK_COUNT < INNER_MATRIX_INDEX
    for (int shadeIndex = 0; shadeIndex < shadeCount; shadeIndex++) {
        for (int innerMatrixIndex = 0; innerMatrixIndex < blockCount; innerMatrixIndex++) {
            uint8_t X_i_j = getValidX_i_j(shades, shadeIndex, innerMatrixIndex);
            *shades[shadeIndex][innerMatrixIndex] = X_i_j;
            char *F_X_i_j = evaluatePolynomial(blocks[innerMatrixIndex], X_i_j, k);
            char p = calculateParityBit(F_X_i_j);
            for (int bit = 0; bit < 8; bit++) {
                if (bit < 3)
                    insertIntoLeastSignificantBits(F_X_i_j[bit], bit % 3, &shades[shadeIndex][innerMatrixIndex][1]);
                else if (bit < 6)
                    insertIntoLeastSignificantBits(F_X_i_j[bit], bit % 3, &shades[shadeIndex][innerMatrixIndex][2]);
                else
                    insertIntoLeastSignificantBits(F_X_i_j[bit], (bit + 1) % 3,&shades[shadeIndex][innerMatrixIndex][3]);
            }
            insertIntoLeastSignificantBits(p, 0, &shades[shadeIndex][innerMatrixIndex][3]);
            free(F_X_i_j);
        }
    }
}

void insertIntoLeastSignificantBits(char bit, int index, uint8_t *cell) {
    char *bits = intToBinary(*cell);
    bits[5 + index] = bit;
    *cell = binaryToInt(bits);
    free(bits);
}

void writeOutputFile(uint8_t *** shades, struct config * config, struct header * header, const uint8_t * headerBytes, int L) {
    for(int i = 0 ; i < config->shadeCount ; i++) {
        char * testDir = malloc(strlen("test-images-out/") + strlen(config->shadeNames[i]) + 1);
        strcpy(testDir, "test-images-out/");
        strcat(testDir, config->shadeNames[i]);
        FILE * f = fopen(testDir, "w+b");
        fwrite(headerBytes, sizeof(uint8_t), header->dataOffset, f);
        int widthLimit = (int)(sqrt(L));
        /*
         *  0  1  2   3
         *  4  5  6   7
         *  8  9  10 11
         *  12 13 14 15
         *
         *  s - 0 1 4 5
         *    - 2 3 6 7
         *    - 8 9 12 13
         *    - 10 11 14 15
         */
        /*
         * s[0][0] -> o[0][0]
         * s[0][1] -> o[0][1]
         * s[0][2] -> o[1][0]
         * s[0][3] -> o[1][1]
         *
         * s[1][0] -> o[0][2]
         * s[1][1] -> o[0][3]
         * s[1][2] -> o[1][2]
         * s[1][3] -> o[1][3]
         *
         * s[2][0] -> o[2][0]
         * s[2][1] -> o[2][1]
         * s[2][2] -> o[3][0]
         * s[2][3] -> o[3][1]
         *
         * s[3][0] -> o[2][2]
         * s[3][1] -> o[2][3]
         * s[3][2] -> o[3][2]
         * s[3][3] -> o[3][3]
         */
        /*int elementsInserted = 0;
        int pasadaActual = 0;
        while(elementsInserted < totalElements) {
            bool primerMitad = true;
            for(int contadorBloque = 0; contadorBloque < header->width ; contadorBloque++) {
                if(primerMitad) {
                    fwrite(&shades[i][contadorBloque % cantidadDePasadas + cantidadDePasadas * pasadaActual][0], sizeof(uint8_t), 1, f);
                    elementsInserted++;
                    fseek(f, header->dataOffset + elementsInserted, SEEK_SET);
                    fwrite(&shades[i][contadorBloque % cantidadDePasadas + cantidadDePasadas * pasadaActual][1], sizeof(uint8_t), 1, f);
                    elementsInserted++;
                    fseek(f, header->dataOffset + elementsInserted, SEEK_SET);
                } else {
                    fwrite(&shades[i][contadorBloque % cantidadDePasadas + cantidadDePasadas * pasadaActual][2], sizeof(uint8_t), 1, f);
                    elementsInserted++;
                    fseek(f, header->dataOffset + elementsInserted, SEEK_SET);
                    fwrite(&shades[i][contadorBloque % cantidadDePasadas + cantidadDePasadas * pasadaActual][3], sizeof(uint8_t), 1, f);
                    elementsInserted++;
                    fseek(f, header->dataOffset + elementsInserted, SEEK_SET);

                }
                if(contadorBloque == (cantidadDePasadas - 1)) {
                    primerMitad = false;
                }
            }
            pasadaActual++;
        }*/
        int index = 0;
        int blockCounter = 0;
        uint8_t * bitmap = malloc(L * sizeof(uint8_t));
        int elementsInserted = 0;
        while(elementsInserted < L) {
            if (index % widthLimit == 0 && index != 0) {
                index += widthLimit;
            }
            if (index >= L) break;

            int ul = index;
            int ur = ul + 1;
            int bl = ul + widthLimit;
            int br = bl + 1;
            bitmap[ul] = shades[i][blockCounter][0];
            bitmap[ur] = shades[i][blockCounter][1];
            bitmap[bl] = shades[i][blockCounter][2];
            bitmap[br] = shades[i][blockCounter][3];
            index += 2;
            blockCounter++;
            elementsInserted += 4;
        }
        printf("shade: %d\n", i);
        printBlock(bitmap, L);
        fwrite(bitmap, sizeof(uint8_t), L, f);
        free(bitmap);
        fclose(f);
    }
}