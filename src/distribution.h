#ifndef DISTRIBUTION_H
#define DISTRIBUTION_H
#include "config.h"
#include <stdint.h>
void runDistribution(struct config * config);
void readShadeFiles(uint8_t *** shades, int shadeCount, char * shadeNames[MAX_SHADE_COUNT], char * directory);
#endif //DISTRIBUTION_H
