#ifndef DISTRIBUTION_H
#define DISTRIBUTION_H
#include "config.h"
#include <stdint.h>
#include "header_struct.h"

void runDistribution(struct config * config);
uint8_t *** readShadeFiles(int shadeCount, char * shadeNames[MAX_SHADE_COUNT], char * directory);
void distributeImage(uint8_t ** blocks, uint8_t *** shades, long blockCount, int shadeCount, long innerMatrixCount, int k);
void insertIntoLeastSignificantBits(char bit, int index, uint8_t * cell);
void writeOutputFile(uint8_t *** shades, struct config * config, struct header * header);

#endif //DISTRIBUTION_H
