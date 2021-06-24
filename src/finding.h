#ifndef FINDING_H
#define FINDING_H
#include <stdint.h>
#include "header_struct.h"
#include "config.h"

void runFinding(struct config * config);
uint8_t ** recoverSecretData(uint8_t *** shades, int k, long matrixCount, long blockCount);
void createSecretImage(uint8_t ** blocks, uint8_t * header, struct config * config, struct header headerStruct, long blockCount);

#endif //FINDING_H
