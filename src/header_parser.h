//
// Created by Eugenio Damm on 03/05/2021.
//

#ifndef HEADER_PARSER_H
#define HEADER_PARSER_H

enum header_parser_states {
    READ_SIGNATURE,
    READ_FILE_SIZE,
    READ_RESERVED,
    READ_DATA_OFFSET,
    READ_SIZE,
    READ_WIDTH,
    READ_HEIGHT,
    READ_PLANES,
    READ_BPP,
    READ_COMPRESSION,
    READ_IMAGE_SIZE,
    READ_XPPM,
    READ_YPPM,
    READ_COLORS,
    READ_IMPORTANT_COLORS,
    END,
    ERROR
};

struct header_parser {
    enum header_parser_states state;
    int inner_counter;
};

struct header * parseHeader(unsigned char * header);

#endif //HEADER_PARSER_H
