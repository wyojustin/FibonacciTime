#ifndef VEC2_H
#define VEC2_H
#include <math.h>

void add2(float* v1, float* v2, float * ans);
void sub2(float* v1, float* v2, float * ans);
void scale2(float *v, float scale, float* ans);
float norm2(float* v);
void normalize2(float* v);
void negate2(float* v, float* ans);
void perp2(float* v, float* ans);
float dot2(float* v1, float*v2);
float copy2(float* frm, float* _to);
void print2(float* v, char* name);
#endif
