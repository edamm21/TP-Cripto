#include "helper.h"

// https://en.wikipedia.org/wiki/Finite_field_arithmetic#Program_examples
// operaciones sobre el campo de Galois de G(2^8)

uint8_t add(uint8_t a, uint8_t b) {
    return a ^ b;
}

uint8_t multiply(uint8_t a, uint8_t b) {
    uint8_t p = 0;
    while (a && b) {
        if (b & 1)
            p ^= a;
        if (a & 0x80)
            a = (a << 1) ^ 0x163;
        else
            a <<= 1;
        b >>= 1;
    }
    return p;
}