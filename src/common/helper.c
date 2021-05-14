#include <stdlib.h>
#include "helper.h"
#include <math.h>

// https://en.wikipedia.org/wiki/Finite_field_arithmetic#Program_examples
// operaciones sobre el campo de Galois de G(2^8)

uint8_t add(uint8_t a, uint8_t b) {
    return a ^ b;
}

uint8_t multiply(uint8_t a, uint8_t b) {
    uint8_t p = 0;
    while (a && b) {
        if (b % 2 != 0)
            p = add(p, a);
        if (a >= 128)
            a = (a << 1) ^ 0x163;
        else
            a <<= 1;
        b >>= 1;
    }
    return p;
}

void freeShadeMatrix(uint8_t *** matrix, int shadeCount, long matrixCount) {
    for(int i = 0 ; i < shadeCount ; i++) {
        for(int j = 0 ; j < matrixCount ; j++) {
            free(matrix[i][j]);
        }
        free(matrix[i]);
    }
    free(matrix);
}

int powerValue(uint8_t x, int power) {
    if(power == 0)
        return 1;
    return multiply(x, powerValue(x, power - 1));
}

char * intToBinary(uint8_t num) {
    char * out = malloc(8);
    int bit = 0;
    for(unsigned char i = 0x80 ; i ; i >>= 1) {
        out[bit++] = num & i ? '1' : '0';
    }
    return out;
}

char * evaluatePolynomial(uint8_t * block, uint8_t X_i_j, int k) {
    int accum = 0;
    for(int term = 0 ; term < k ; term++) {
        accum = add(accum,multiply(block[term], powerValue(X_i_j, term)));
    }
    return intToBinary(accum);
}

char calculateParityBit(char F[8]) {
    char pByte = F[0];
    for(int i = 1 ; i < 8 ; i++) {
        pByte = pByte == F[i] ? '0' : '1';
    }
    return pByte;
}

uint8_t binaryToInt(const char * bits) {
    uint8_t out = 0;
    for(int i = 7 ; i >= 0 ; i--) {
        out += bits[7 - i] == '1' ? (int)pow(2, i) : 0;
    }
    return out;
}