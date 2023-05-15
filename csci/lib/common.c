#include "csci/common.h"

int common_int32_compar(const int *a, const int *b) { return *a - *b; }

int common_float32_compar(const float *a, const float *b) { return *a - *b; }

int common_double64_compar(const double *a, const double *b) { return *a - *b; }

int *common_int32_copy(int *dest, int *src) {
    *dest = *src;
    return dest;
}

float *common_float32_copy(float *dest, float *src) {
    *dest = *src;
    return dest;
}

double *common_double64_copy(float *dest, float *src) {
    *dest = *src;
    return dest;
}
