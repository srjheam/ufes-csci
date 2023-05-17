#ifndef _CSCI_COMMON_H_
#define _CSCI_COMMON_H_

int common_int32_compar(const int *a, const int *b);

int common_float32_compar(const float *a, const float *b);

int common_double64_compar(const double *a, const double *b);

int *common_int32_copy(int *dest, int *src);

float *common_float32_copy(float *dest, float *src);

double *common_double64_copy(float *dest, float *src);

#endif
