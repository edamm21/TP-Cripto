#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "distribution.h"
#include "config.h"
#include "header_parser.h"
#include "header_struct.h"

void runDistribution(struct config * config) {
    FILE * bmpImage = fopen(config->imageFile, "rb");
    fseek(bmpImage, 0, SEEK_END);
    long fileSize = ftell(bmpImage);
    rewind(bmpImage);
    unsigned char fileData[fileSize];
    size_t readBytes = fread(fileData, sizeof(unsigned char), fileSize, bmpImage);
    if(readBytes != fileSize)
        return;
    struct header * headerStruct = parseHeader(fileData);
    if(headerStruct == NULL) {
        fclose(bmpImage);
        fprintf(stderr, "Error creating header structure from BMP image!");
        return;
    }
    // Esta es la cantidad de datos en si de la imagen sin contar el header
    long bitmapDataSize = fileSize - headerStruct->dataOffset;
    // Para no olvidarnos
    free(headerStruct);
    fclose(bmpImage);
}

