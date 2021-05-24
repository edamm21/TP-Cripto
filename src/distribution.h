#ifndef DISTRIBUTION_H
#define DISTRIBUTION_H
#include "config.h"
#include <stdint.h>
#include "header_struct.h"

void runDistribution(struct config * config);
void distributeImage(uint8_t ** blocks, uint8_t *** shades, long blockCount, int shadeCount, long innerMatrixCount, int k);
void insertIntoLeastSignificantBits(char bit, int index, uint8_t * cell);
void writeOutputFile(uint8_t *** shades, struct config * config, struct header * header, const uint8_t * headerBytes, int L);

#endif //DISTRIBUTION_H
