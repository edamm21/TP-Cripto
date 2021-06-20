#include <stdlib.h>
#include "helper.h"
#include "galois.h"
#include <math.h>
#include <stdbool.h>
#include <printf.h>
#include <config.h>
#include <string.h>
#include <header_parser.h>
#include <header_struct.h>
#include <stdio.h>

// https://en.wikipedia.org/wiki/Finite_field_arithmetic#Program_examples
// operaciones sobre el campo de Galois de G(2^8)

uint8_t add(uint8_t a, uint8_t b) {
    return a ^ b;
}

uint8_t subtract(uint8_t a, uint8_t b) {
    return add(a,b);
}

uint8_t divide(uint8_t a, uint8_t b) {
    return getMultiplication(a, getInverse(b));
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
    char currentCompared;
    for(int i = 0 ; i < 8 ;) {
        if(i == 0) {
            currentCompared = F[i] == F[i+1] ? '0' : '1';
            i += 2;
        } else {
            currentCompared = currentCompared == F[i] ? '0' : '1';
            i++;
        }
    }
    return currentCompared;
}

uint8_t binaryToInt(const char * bits) {
    uint8_t out = 0;
    for(int i = 7 ; i >= 0 ; i--) {
        out += bits[7 - i] == '1' ? (int)pow(2, i) : 0;
    }
    return out;
}

uint8_t updateXValue(uint8_t x) {
    int new_x_value = x + 1;
    uint8_t new_x_value_mod = new_x_value % 255;
    return new_x_value != new_x_value_mod ? x - new_x_value_mod : new_x_value;
}

uint8_t getValidX_i_j(uint8_t ***shades, int maxShadeIdx, int innerMatrixIndex) {
    if(maxShadeIdx == 0) {
        return shades[maxShadeIdx][innerMatrixIndex][0];
    }
    uint8_t currentX_i_j = shades[maxShadeIdx][innerMatrixIndex][0];
    uint8_t aux_X_i_j_array[maxShadeIdx];
    int aux_X_i_j_array_count = 0;
    for (int currentShadeIdx = 0; currentShadeIdx < maxShadeIdx; ++currentShadeIdx) {
        uint8_t X_i_j = shades[currentShadeIdx][innerMatrixIndex][0];
        if (X_i_j > currentX_i_j) {
            aux_X_i_j_array[aux_X_i_j_array_count] = X_i_j;
            aux_X_i_j_array_count++;
        } else if (X_i_j == currentX_i_j) {
            currentX_i_j = updateXValue(currentX_i_j);
            int idx = 0;
            bool isValid = false;
            while (!isValid && idx < aux_X_i_j_array_count) {
                uint8_t aux = aux_X_i_j_array[idx];
                if (aux == currentX_i_j) {
                    currentX_i_j = updateXValue(currentX_i_j);
                    idx = 0;
                } else {
                    idx++;
                }
                if (idx == maxShadeIdx) isValid = true;
            }
        }
    }
    return currentX_i_j;
}

uint8_t *readFile(char *path, long *fileSize) {
    FILE *bmpImage = fopen(path, "rb");
    fseek(bmpImage, 0, SEEK_END);
    *fileSize = ftell(bmpImage);
    rewind(bmpImage);
    uint8_t *fileData = malloc(sizeof(uint8_t) * (*fileSize));
    size_t readBytes = fread(fileData, sizeof(uint8_t), *fileSize, bmpImage);
    fclose(bmpImage);
    if (readBytes != *fileSize) {
        free(fileData);
        return NULL;
    }
    return fileData;
}

uint8_t *** readShadeFiles(int shadeCount, char *shadeNames[MAX_SHADE_COUNT], char *directory, int k) {
    uint8_t ***shades = malloc(shadeCount * sizeof(uint8_t **));
    for (int i = 0; i < shadeCount; i++) {
        long fileSize;
        char *completePath = malloc(strlen(directory) + strlen(shadeNames[i]) + 1);
        strcpy(completePath, directory);
        strcat(completePath, shadeNames[i]);
        uint8_t *fileData = readFile(completePath, &fileSize);
        if (fileData == NULL)
            return NULL;
        struct header *headerStruct = parseHeader(fileData);
        if (headerStruct == NULL) {
            free(fileData);
            fprintf(stderr, "Error creating header structure from BMP image!");
            return NULL;
        }
        long L = fileSize - headerStruct->dataOffset;
        uint8_t *bitmap = fileData + headerStruct->dataOffset;
        int blockCount = L / k;
        shades[i] = malloc(sizeof(uint8_t *) * blockCount);
        int blocksAssigned = 0;
        while(blocksAssigned < blockCount) {
            int blockRow = 2 * blocksAssigned % headerStruct->width;
            int blockCol = 2 * (2 * blocksAssigned / headerStruct->width);
            int blockPosition = (headerStruct->height - 1) * headerStruct->width + blockRow - blockCol * headerStruct->width;
            shades[i][blocksAssigned] = malloc(4 * sizeof(uint8_t));
            shades[i][blocksAssigned][0] = bitmap[blockPosition];
            shades[i][blocksAssigned][1] = bitmap[blockPosition + 1];
            shades[i][blocksAssigned][2] = bitmap[blockPosition - headerStruct->width];
            shades[i][blocksAssigned][3] = bitmap[blockPosition - headerStruct->width + 1];
            blocksAssigned++;
        }
        free(completePath);
        free(fileData);
        free(headerStruct);
    }
    return shades;
}

uint8_t *** readShadeFilesFinding(int shadeCount, char *shadeNames[MAX_SHADE_COUNT], char *directory, uint8_t ** header, long * matrixCount, struct header * headerStructParam, int k) {
    uint8_t ***shades = malloc(shadeCount * sizeof(uint8_t **));
    for (int i = 0; i < shadeCount; i++) {
        long fileSize;
        char *completePath = malloc(strlen(directory) + strlen(shadeNames[i]) + 1);
        strcpy(completePath, directory);
        strcat(completePath, shadeNames[i]);
        uint8_t *fileData = readFile(completePath, &fileSize);
        if (fileData == NULL)
            return NULL;
        struct header *headerStruct = parseHeader(fileData);
        if (headerStruct == NULL) {
            free(fileData);
            fprintf(stderr, "Error creating header structure from BMP image!");
            return NULL;
        }
        if(i == 0) {
            *header = malloc(headerStruct->dataOffset * sizeof(uint8_t));
            memcpy(*header, fileData, headerStruct->dataOffset);
            memcpy(headerStructParam, headerStruct, sizeof(struct header));
        }
        long L = fileSize - headerStruct->dataOffset;
        uint8_t *bitmap = fileData + headerStruct->dataOffset;
        long blockCount = L / k;
        *matrixCount = blockCount;
        shades[i] = malloc(sizeof(uint8_t *) * blockCount);
        int blocksAssigned = 0;
        while(blocksAssigned < blockCount) {
            int blockRow = 2 * blocksAssigned % headerStruct->width;
            int blockCol = 2 * (2 * blocksAssigned / headerStruct->width);
            int blockPosition = (headerStruct->height - 1) * headerStruct->width + blockRow - blockCol * headerStruct->width;
            shades[i][blocksAssigned] = malloc(4 * sizeof(uint8_t));
            shades[i][blocksAssigned][0] = bitmap[blockPosition];
            shades[i][blocksAssigned][1] = bitmap[blockPosition + 1];
            shades[i][blocksAssigned][2] = bitmap[blockPosition - headerStruct->width];
            shades[i][blocksAssigned][3] = bitmap[blockPosition - headerStruct->width + 1];
            blocksAssigned++;
        }
        free(completePath);
        free(fileData);
        free(headerStruct);
    }
    return shades;
}

void injectBitsIntoT(char T_i_j[8], const char * W_i_j, const char * V_i_j, const char * U_i_j) {
    T_i_j[0] = W_i_j[5];
    T_i_j[1] = W_i_j[6];
    T_i_j[2] = W_i_j[7];
    T_i_j[3] = V_i_j[5];
    T_i_j[4] = V_i_j[6];
    T_i_j[5] = V_i_j[7];
    T_i_j[6] = U_i_j[6];
    T_i_j[7] = U_i_j[7];
}

bool checkParityBit(char * T_I_J, char parityBit) {
    return calculateParityBit(T_I_J) == parityBit;
}

void printBlock(uint8_t * block, int k) {
    for(int i = 0 ; i < k ; i++) {
        printf("%x - ", block[i]);
    }
    printf("\n");
}


uint8_t * calculateLagrange(uint8_t * X, uint8_t * Y, int k) {
    uint8_t * polynomial = malloc(k * sizeof(uint8_t));
    memset(polynomial,0,k);
    int termsCounter;
    uint8_t res;
    for (int i = 0; i < k ; i++) {
        termsCounter = 0;
        res = 1;
        uint8_t aux[k];
        for(int t = 0 ; t < k ; t++) {
            aux[t] = 0;
        }
        for(int j = 0 ; j < k ; j++) {
            if (i != j) {
                res = getMultiplication(res, add(X[i], X[j]));
                if (termsCounter == 0) {
                    aux[0] = getMultiplication(X[j], Y[i]);
                    aux[1] = Y[i];
                } else {
                    // desplazo los terminos porque ahora va incrementando el grado hasta llegar a k
                    for (int currentMaxGrade = termsCounter; currentMaxGrade >= 0; currentMaxGrade--) {
                        aux[currentMaxGrade + 1] = aux[currentMaxGrade];
                    }
                    aux[0] = getMultiplication(aux[0], X[j]);
                    for (int currentTerm = 1; currentTerm <= termsCounter; currentTerm++) {
                        aux[currentTerm] = add(aux[currentTerm],getMultiplication(aux[currentTerm + 1], X[j]));
                    }
                }
                termsCounter++;
            }
        }
        for(int r = 0 ; r < k ; r++) {
            polynomial[r] = add(polynomial[r], getMultiplication(aux[r], getInverse(res)));
        }
    }
    return polynomial;
}

void freeConfig(struct config * config) {
    for(int i = 0 ; i < config->shadeCount ; i++) {
        free(config->shadeNames[i]);
    }
}

void freeRecoveredBlocks(uint8_t ** blocks, long blockCount) {
    for(int i = 0 ; i < blockCount ; i++) {
        if(blocks[i] != NULL)
            free(blocks[i]);
    }
    free(blocks);
}

void freeShades(uint8_t *** shades, int shadeCount, long blockCount) {
    for(int i = 0 ; i < shadeCount ; i++) {
        for(int j = 0 ; j < blockCount ; j++) {
            free(shades[i][j]);
        }
        free(shades[i]);
    }
    free(shades);
}