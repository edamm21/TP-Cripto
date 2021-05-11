//
// Created by Eugenio Damm on 03/05/2021.
//
#include <stdlib.h>
#include <stdbool.h>
#include "header_struct.h"
#include "header_parser.h"

static bool isValidSignature(const uint8_t * signature) {
    return signature[0] == 'B' && signature[1] == 'M';
}

static enum header_parser_states feedToParser(uint8_t b, struct header_parser * parser, struct header * header) {
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
            header->fileSize = (header->fileSize << (8 * parser->inner_counter)) | b;
            parser->inner_counter++;
            if(parser->inner_counter == 4) {
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
            header->dataOffset = header->dataOffset * 16 + (int)b;
            parser->inner_counter++;
            if(parser->inner_counter == 4) {
                parser->state = READ_SIZE;
                parser->inner_counter = 0;
            }
            break;
        case READ_SIZE:
            header->size = header->size * 16 + (int)b;
            parser->inner_counter++;
            if(parser->inner_counter == 4) {
                parser->state = READ_WIDTH;
                parser->inner_counter = 0;
            }
            break;
        case READ_WIDTH:
            header->width = header->width * 16 + (int)b;
            parser->inner_counter++;
            if(parser->inner_counter == 4) {
                parser->state = READ_HEIGHT;
                parser->inner_counter = 0;
            }
            break;
        case READ_HEIGHT:
            header->height = header->height * 16 + (int)b;
            parser->inner_counter++;
            if(parser->inner_counter == 4) {
                parser->state = READ_PLANES;
                parser->inner_counter = 0;
            }
            break;
        case READ_PLANES:
            header->planes = header->planes * 16 + (int)b;
            parser->inner_counter++;
            if(parser->inner_counter == 2) {
                parser->state = READ_BPP;
                parser->inner_counter = 0;
            }
            break;
        case READ_BPP:
            header->bitsPerPixel = header->bitsPerPixel * 16 + (int)b;
            parser->inner_counter++;
            if(parser->inner_counter == 2) {
                parser->state = READ_COMPRESSION;
                parser->inner_counter = 0;
            }
            break;
        case READ_COMPRESSION:
            header->compression = header->compression * 16 + (int)b;
            parser->inner_counter++;
            if(parser->inner_counter == 4) {
                parser->state = READ_IMAGE_SIZE;
                parser->inner_counter = 0;
            }
            break;
        case READ_IMAGE_SIZE:
            header->imageSize = header->imageSize * 16 + (int)b;
            parser->inner_counter++;
            if(parser->inner_counter == 4) {
                parser->state = READ_XPPM;
                parser->inner_counter = 0;
            }
            break;
        case READ_XPPM:
            header->xPixelsPerM = header->xPixelsPerM * 16 + (int)b;
            parser->inner_counter++;
            if(parser->inner_counter == 4) {
                parser->state = READ_YPPM;
                parser->inner_counter = 0;
            }
            break;
        case READ_YPPM:
            header->yPixelsPerM = header->yPixelsPerM * 16 + (int)b;
            parser->inner_counter++;
            if(parser->inner_counter == 4) {
                parser->state = READ_COLORS;
                parser->inner_counter = 0;
            }
            break;
        case READ_COLORS:
            header->colorsUsed = header->colorsUsed * 16 + (int)b;
            parser->inner_counter++;
            if(parser->inner_counter == 4) {
                parser->state = READ_IMPORTANT_COLORS;
                parser->inner_counter = 0;
            }
            break;
        case READ_IMPORTANT_COLORS:
            header->importantColors = header->importantColors * 16 + (int)b;
            parser->inner_counter++;
            if(parser->inner_counter == 4) {
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
    while(i < offset && currentState != ERROR && currentState != END) {
        currentState = feedToParser(header[i], &parser, headerStruct);
        i++;
    }
    return headerStruct;
}
