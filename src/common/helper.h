#ifndef HELPER_H
#define HELPER_H
#include <stdint.h>

uint8_t add(uint8_t a, uint8_t b);
uint8_t multiply(uint8_t a, uint8_t b);
void freeShadeMatrix(uint8_t *** matrix, int shadeCount, long matrixCount);
char * evaluatePolynomial(uint8_t * block, uint8_t X_i_j, int k);
char calculateParityBit(char F[8]);

#endif
