#include <stdint.h>
#include <common/helper.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "finding.h"

void runFinding(struct config * config) {
    printf("Finding hidden image...\n");
    uint8_t * headerForCopying = NULL;
    long matrixCount;
    struct header headerStruct;
    uint8_t *** shades = readShadeFilesFinding(config->shadeCount, config->shadeNames, config->directory, &headerForCopying, &matrixCount, &headerStruct, config->k);
    long L = headerStruct.fileSize - headerStruct.dataOffset;
    uint8_t ** recoveredBitmap = recoverSecretData(shades, config->k, matrixCount, L/config->k);
    if(recoveredBitmap == NULL) {
        fprintf(stderr, "Error recovering hidden image!\n");
        free(headerForCopying);
        freeShades(shades, config->shadeCount, matrixCount);
        freeConfig(config);
        return;
    }
    createSecretImage(recoveredBitmap, headerForCopying, config, headerStruct, L/config->k);
    free(headerForCopying);
    freeShades(shades, config->shadeCount, matrixCount);
    freeConfig(config);
    freeRecoveredBlocks(recoveredBitmap, matrixCount);
    // TODO
    //freeShadeMatrix(shades, config->shadeCount, )
}

void createSecretImage(uint8_t ** blocks, uint8_t * header, struct config * config, struct header headerStruct, long blockCount) {
    FILE * out = fopen(config->imageFile, "w+b");
    fwrite(header, sizeof(uint8_t), headerStruct.dataOffset, out);
    fseek(out, headerStruct.dataOffset, SEEK_SET);
    for(int blockIndex = 0 ; blockIndex < blockCount ; blockIndex++) {
        fwrite(blocks[blockIndex], sizeof(uint8_t), config->k, out);
        fseek(out, headerStruct.dataOffset + ((blockIndex + 1) * config->k), SEEK_SET);
    }
    fclose(out);
}

uint8_t ** recoverSecretData(uint8_t *** shades, int k, long matrixCount, long blockCount) {
    uint8_t ** recoveredBlocks = malloc(blockCount * sizeof(uint8_t *));
    for(int matrixIndex = 0 ; matrixIndex < blockCount ; matrixIndex++) {
        uint8_t allY_i_js[k];
        uint8_t allX_i_js[k];
        int shadeIndex;
        for(shadeIndex = 0 ; shadeIndex < k ; shadeIndex++) {
            char * W_i_j = intToBinary(shades[shadeIndex][matrixIndex][1]);
            char * V_i_j = intToBinary(shades[shadeIndex][matrixIndex][2]);
            char * U_i_j = intToBinary(shades[shadeIndex][matrixIndex][3]);
            char T_i_j[8];
            injectBitsIntoT(T_i_j, W_i_j, V_i_j, U_i_j);
            bool isParityBitValid = checkParityBit(T_i_j, U_i_j[5]);
            if(!isParityBitValid) {
                //TODO HACER TODOS LOS FREE NECESARIOS
                free(W_i_j);
                free(V_i_j);
                free(U_i_j);
                freeRecoveredBlocks(recoveredBlocks, blockCount);
                return NULL;
            }
            allY_i_js[shadeIndex] = binaryToInt(T_i_j);
            allX_i_js[shadeIndex] = shades[shadeIndex][matrixIndex][0];
            free(W_i_j);
            free(V_i_j);
            free(U_i_j);
        }
        recoveredBlocks[matrixIndex] = malloc(k * sizeof(uint8_t));
        uint8_t * toCopy = calculateLagrange(allX_i_js, allY_i_js, k);
        memcpy(recoveredBlocks[matrixIndex], toCopy, k * sizeof(uint8_t));
        free(toCopy);
    }
    return recoveredBlocks;
}

