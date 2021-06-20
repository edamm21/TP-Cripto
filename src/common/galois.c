#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "helper.h"
#include "galois.h"

uint8_t ** matrix = NULL;
uint8_t * inverseValue = NULL;

void populateMatrix() {
    matrix = malloc(256 * sizeof(uint8_t*));
    inverseValue = malloc(256 * sizeof(uint8_t));
    for (int i = 0; i < 256 ; ++i) {
        matrix[i] = malloc(256 * sizeof(uint8_t));
        for (int j = 0; j < 256 ; ++j) {
            matrix[i][j] = multiply(i,j);
            if (matrix[i][j] == 1) {
                inverseValue[i] = j;
            }
        }
    }
}

uint8_t getMultiplication(uint8_t a, uint8_t b) {
    return matrix[a][b];
}

uint8_t getInverse(uint8_t a) {
    return inverseValue[a];
}