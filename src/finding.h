#ifndef FINDING_H
#define FINDING_H
#include <stdint.h>
#include "config.h"

void runFinding(struct config * config);
uint8_t * recoverSecretData(uint8_t *** shades, int shadeCount, long matrixCount);

#endif //FINDING_H
