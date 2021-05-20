#include <stdint.h>
#include <helper.h>
#include "galios.h"


uint8_t matrix[255][255];

uint8_t inverseValue[255];

void populateMatrix() {
    for (int i = 0; i < 256 ; ++i) {
        for (int j = 0; j < 256 ; ++j) {
            matrix[i][j] = multiply(i,j);
            if (matrix[i][j] == 1) {
                inverseValue[i] = j;
                inverseValue[j] = i;
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