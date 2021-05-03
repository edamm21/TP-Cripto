#include <stdio.h>
#include <string.h>
#include "args_parser.h"
#include "finding.h"
#include "distribution.h"

int main(int argc, char * argv[]) {
    struct config config;
    memset(&config, 0, sizeof(config));
    parseArgs(argc, argv, &config);
    if(config.type == 'd') {
        runDistribution(&config);
    } else {
        runFinding();
    }
    return 0;
}