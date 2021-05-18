#include <stdint.h>
#include <common/helper.h>
#include <stdlib.h>
#include <stdbool.h>
#include "finding.h"

void runFinding(struct config * config) {
    uint8_t * headerForCopying;
    long matrixCount;
    uint8_t *** shades = readShadeFilesFinding(config->shadeCount, config->shadeNames, config->directory, headerForCopying, &matrixCount);
    uint8_t * recoveredBitmap = recoverSecretData(shades, config->k, matrixCount);

    // TODO
    //freeShadeMatrix(shades, config->shadeCount, )
}

// TODO: pasar al helper
uint8_t calculateLagrange(uint8_t * X, uint8_t * Y, int k) {
    return 1;
}

uint8_t calculateYPrime(uint8_t s1_j, uint8_t X_i_j, uint8_t Y_i_j) {
    return 1;
}

uint8_t * recoverSecretData(uint8_t *** shades, int shadeCount, long matrixCount) {
    for(int matrixIndex = 0 ; matrixIndex < matrixCount ; matrixIndex++) {
        uint8_t allY_i_js[shadeCount];
        uint8_t allX_i_js[shadeCount];
        int shadeIndex;
        for(shadeIndex = 0 ; shadeIndex < shadeCount ; shadeIndex++) {
            char * W_i_j = intToBinary(shades[shadeIndex][matrixIndex][1]);
            char * V_i_j = intToBinary(shades[shadeIndex][matrixIndex][2]);
            char * U_i_j = intToBinary(shades[shadeIndex][matrixIndex][3]);
            char T_i_j[8];
            injectBitsIntoT(T_i_j, W_i_j, V_i_j, U_i_j);
            bool isParityBitValid = checkParityBit(T_i_j, U_i_j[5]);
            if(!isParityBitValid) {
                //HACER TODOS LOS FREE NECESARIOS
                return -1;
            }
            allY_i_js[shadeIndex] = binaryToInt(T_i_j);
            allX_i_js[shadeCount] = shades[shadeIndex][matrixIndex][0];
        }
        uint8_t * secretValues = malloc(shadeCount * sizeof(uint8_t));
        secretValues[0] = calculateLagrange(allX_i_js, allY_i_js, shadeCount);
        for(shadeIndex = 0 ; shadeIndex < shadeCount ; shadeIndex++) {
            uint8_t Y_prime_i_j = calculateYPrime(secretValues[0], allX_i_js[shadeIndex], allY_i_js[shadeIndex]);
            // TODO: aca me agarro la duda
            //secretValues[1 + shadeIndex] = calculateLagrange(allX_i_js,  , shadeCount);
        }
    }
}