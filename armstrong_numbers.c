#include <assert.h>
#include <inttypes.h>
#include <math.h>

#include "armstrong_numbers.h"

// See
// https://stackoverflow.com/questions/25892665/performance-of-log10-function-returning-an-int

unsigned int baseTwoDigits(unsigned int x) {
    return x ? 32 - __builtin_clz(x) : 0;
}

unsigned int num_digits(unsigned int x) {
    static const unsigned char guess[33] = {0, 0, 0, 0, 1, 1, 1, 2, 2, 2, 3,
                                            3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6,
                                            6, 6, 7, 7, 7, 8, 8, 8, 9, 9, 9};
    static const unsigned int tenToThe[] = {
        1,      10,      100,      1000,      10000,
        100000, 1000000, 10000000, 100000000, 1000000000,
    };
    unsigned int digits = guess[baseTwoDigits(x)];
    return digits + (x >= tenToThe[digits]);
}

uint64_t ipow(uint8_t base, uint8_t exp) {
    assert(base <= 9 && exp <= 10);
    static const uint64_t powers[10][11] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},

        {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024},

        {1, 3, 3 * 3, 3 * 3 * 3, 3 * 3 * 3 * 3, 3 * 3 * 3 * 3 * 3,
         3 * 3 * 3 * 3 * 3 * 3, 3 * 3 * 3 * 3 * 3 * 3 * 3,
         3 * 3 * 3 * 3 * 3 * 3 * 3 * 3, 3 * 3 * 3 * 3 * 3 * 3 * 3 * 3 * 3,
         3 * 3 * 3 * 3 * 3 * 3 * 3 * 3 * 3 * 3},

        {1, 4, 4 * 4, 4 * 4 * 4, 4 * 4 * 4 * 4, 4 * 4 * 4 * 4 * 4,
         4 * 4 * 4 * 4 * 4 * 4, 4 * 4 * 4 * 4 * 4 * 4 * 4,
         4 * 4 * 4 * 4 * 4 * 4 * 4 * 4, 4 * 4 * 4 * 4 * 4 * 4 * 4 * 4 * 4,
         4 * 4 * 4 * 4 * 4 * 4 * 4 * 4 * 4 * 4},

        {1, 5, 5 * 5, 5 * 5 * 5, 5 * 5 * 5 * 5, 5 * 5 * 5 * 5 * 5,
         5 * 5 * 5 * 5 * 5 * 5, 5 * 5 * 5 * 5 * 5 * 5 * 5,
         5 * 5 * 5 * 5 * 5 * 5 * 5 * 5, 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5,
         5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5 * 5},

        {1, 6, 6 * 6, 6 * 6 * 6, 6 * 6 * 6 * 6, 6 * 6 * 6 * 6 * 6,
         6 * 6 * 6 * 6 * 6 * 6, 6 * 6 * 6 * 6 * 6 * 6 * 6,
         6 * 6 * 6 * 6 * 6 * 6 * 6 * 6, 6 * 6 * 6 * 6 * 6 * 6 * 6 * 6 * 6,
         6 * 6 * 6 * 6 * 6 * 6 * 6 * 6 * 6 * 6},

        {1, 7, 7 * 7, 7 * 7 * 7, 7 * 7 * 7 * 7, 7 * 7 * 7 * 7 * 7,
         7 * 7 * 7 * 7 * 7 * 7, 7 * 7 * 7 * 7 * 7 * 7 * 7,
         7 * 7 * 7 * 7 * 7 * 7 * 7 * 7, 7 * 7 * 7 * 7 * 7 * 7 * 7 * 7 * 7,
         7 * 7 * 7 * 7 * 7 * 7 * 7 * 7 * 7 * 7},

        {1, 8, 8 * 8, 8 * 8 * 8, 8 * 8 * 8 * 8, 8 * 8 * 8 * 8 * 8,
         8 * 8 * 8 * 8 * 8 * 8, 8 * 8 * 8 * 8 * 8 * 8 * 8,
         8 * 8 * 8 * 8 * 8 * 8 * 8 * 8, 8 * 8 * 8 * 8 * 8 * 8 * 8 * 8 * 8,
         8 * 8 * 8 * 8 * 8 * 8 * 8 * 8 * 8 * 8},

        {1, 9, 9 * 9, 9 * 9 * 9, 9 * 9 * 9 * 9, 9 * 9 * 9 * 9 * 9,
         9 * 9 * 9 * 9 * 9 * 9, 9 * 9 * 9 * 9 * 9 * 9 * 9,
         9 * 9 * 9 * 9 * 9 * 9 * 9 * 9, 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9,
         9ul * 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9},
    };
    return powers[base][exp];
}

bool is_armstrong_number(uint32_t candidate) {
    if (candidate < 0)
        return false;
    uint32_t n = candidate;
    uint8_t n_digits = num_digits(n);
    uint32_t sum = 0;
    for (; n; n /= 10) {
        sum += ipow(n % 10, n_digits);
    }
    return sum == candidate;
}
