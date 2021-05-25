#ifndef HELPER_H
#define HELPER_H
#include <stdint.h>
#include <stdbool.h>
#include "constants.h"
#include "header_struct.h"

uint8_t add(uint8_t a, uint8_t b);
uint8_t multiply(uint8_t a, uint8_t b);
void freeShadeMatrix(uint8_t *** matrix, int shadeCount, long matrixCount);
char * evaluatePolynomial(uint8_t * block, uint8_t X_i_j, int k);
char calculateParityBit(char F[8]);
char * intToBinary(uint8_t num);
uint8_t binaryToInt(const char * bits);
uint8_t getValidX_i_j(uint8_t ***shades, int currentShadeIndex, int innerMatrixIndex);
uint8_t *** readShadeFiles(int shadeCount, char * shadeNames[MAX_SHADE_COUNT], char * directory, int k);
uint8_t *** readShadeFilesFinding(int shadeCount, char *shadeNames[MAX_SHADE_COUNT], char *directory, uint8_t ** header, long * matrixCount, struct header * headerStructParam, int k);
uint8_t *readFile(char *path, long *fileSize);
void injectBitsIntoT(char T_i_j[8], const char * W_i_j, const char * V_i_j, const char * U_i_j);
bool checkParityBit(char * T_I_J, char parityBit);
uint8_t * calculateLagrange(uint8_t * X, uint8_t * Y, int k);
void printBlock(uint8_t * block, int k);

#endif
