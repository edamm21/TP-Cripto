#ifndef CONFIG_H
#define CONFIG_H

#define MAX_SHADE_COUNT 20

struct config {
    char type;
    char imageFile[255];
    int k;
    char directory[255];
    int shadeCount;
    char * shadeNames[MAX_SHADE_COUNT];
};

#endif //CONFIG_H
