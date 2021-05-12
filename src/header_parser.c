//
// Created by Eugenio Damm on 03/05/2021.
//
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "header_struct.h"
#include "header_parser.h"

static bool isValidSignature(const uint8_t * signature) {
    return signature[0] == 'B' && signature[1] == 'M';
}

static int hexToDec(const uint8_t tmp[4]) {
    return tmp[0] | tmp[1] << 8 | tmp[2] << 16 | tmp[3] << 24;
}

static enum header_parser_states feedToParser(uint8_t b, struct header_parser * parser, struct header * header, unsigned char tmp[4]) {
    switch (parser->state) {
        case READ_SIGNATURE:
            header->signature[parser->inner_counter++] = b;
            if(parser->inner_counter == 2) {
                if (isValidSignature(header->signature)) {
                    parser->state = READ_FILE_SIZE;
                    parser->inner_counter = 0;
                } else {
                    parser->state = ERROR;
                }
            }
            break;
        case READ_FILE_SIZE:
            tmp[parser->inner_counter++] = b;
            if(parser->inner_counter == 4) {
                header->fileSize = hexToDec(tmp);
                parser->state = READ_RESERVED;
                parser->inner_counter = 0;
            }
            break;
        case READ_RESERVED:
            header->reserved[parser->inner_counter++] = b;
            if(parser->inner_counter == 4) {
                parser->state = READ_DATA_OFFSET;
                parser->inner_counter = 0;
            }
            break;
        case READ_DATA_OFFSET:
            tmp[parser->inner_counter++] = b;
            if(parser->inner_counter == 4) {
                header->dataOffset = hexToDec(tmp);
                parser->state = READ_SIZE;
                parser->inner_counter = 0;
            }
            break;
        case READ_SIZE:
            tmp[parser->inner_counter++] = b;
            if(parser->inner_counter == 4) {
                header->size = hexToDec(tmp);
                parser->state = READ_WIDTH;
                parser->inner_counter = 0;
            }
            break;
        case READ_WIDTH:
            tmp[parser->inner_counter++] = b;
            if(parser->inner_counter == 4) {
                header->width = hexToDec(tmp);
                parser->state = READ_HEIGHT;
                parser->inner_counter = 0;
            }
            break;
        case READ_HEIGHT:
            tmp[parser->inner_counter++] = b;
            if(parser->inner_counter == 4) {
                header->height = hexToDec(tmp);
                parser->state = READ_PLANES;
                parser->inner_counter = 0;
            }
            break;
        case READ_PLANES:
            tmp[parser->inner_counter++] = b;
            if(parser->inner_counter == 2) {
                header->planes = hexToDec(tmp);
                parser->state = READ_BPP;
                parser->inner_counter = 0;
            }
            break;
        case READ_BPP:
            tmp[parser->inner_counter++] = b;
            if(parser->inner_counter == 2) {
                header->bitsPerPixel = hexToDec(tmp);
                parser->state = READ_COMPRESSION;
                parser->inner_counter = 0;
            }
            break;
        case READ_COMPRESSION:
            tmp[parser->inner_counter++] = b;
            if(parser->inner_counter == 4) {
                header->compression = hexToDec(tmp);
                parser->state = READ_IMAGE_SIZE;
                parser->inner_counter = 0;
            }
            break;
        case READ_IMAGE_SIZE:
            tmp[parser->inner_counter++] = b;
            if(parser->inner_counter == 4) {
                header->imageSize = hexToDec(tmp);
                parser->state = READ_XPPM;
                parser->inner_counter = 0;
            }
            break;
        case READ_XPPM:
            tmp[parser->inner_counter++] = b;
            if(parser->inner_counter == 4) {
                header->xPixelsPerM = hexToDec(tmp);
                parser->state = READ_YPPM;
                parser->inner_counter = 0;
            }
            break;
        case READ_YPPM:
            tmp[parser->inner_counter++] = b;
            if(parser->inner_counter == 4) {
                header->yPixelsPerM = hexToDec(tmp);
                parser->state = READ_COLORS;
                parser->inner_counter = 0;
            }
            break;
        case READ_COLORS:
            tmp[parser->inner_counter++] = b;
            if(parser->inner_counter == 4) {
                header->colorsUsed = hexToDec(tmp);
                parser->state = READ_IMPORTANT_COLORS;
                parser->inner_counter = 0;
            }
            break;
        case READ_IMPORTANT_COLORS:
            tmp[parser->inner_counter++] = b;
            if(parser->inner_counter == 4) {
                header->importantColors = hexToDec(tmp);
                parser->state = END;
                parser->inner_counter = 0;
            }
            break;
        case END:
        case ERROR:
            break;
    }
    return parser->state;
}

struct header * parseHeader(uint8_t * header) {
    struct header * headerStruct = calloc(1, sizeof(struct header));
    if(header == NULL)
        return NULL;
    struct header_parser parser;
    parser.inner_counter = 0;
    parser.state = READ_SIGNATURE;
    int i = 0;
    int offset = (int)header[10] + (int)header[11] + (int)header[12] + (int)header[13] - 1;
    enum header_parser_states currentState = parser.state;
    unsigned char tmp[4];
    while(i < offset && currentState != ERROR && currentState != END) {
        currentState = feedToParser(header[i], &parser, headerStruct, tmp);
        i++;
    }
    return headerStruct;
}
