#include "vec2.h"
#include "math.h"
#include <arduino.h>

void add2(float* v1, float* v2, float * ans){
  ans[0] = v1[0] + v2[0];
  ans[1] = v1[1] + v2[1];
}
void sub2(float* v1, float* v2, float * ans){
  ans[0] = v1[0] - v2[0];
  ans[1] = v1[1] - v2[1];
}
void scale2(float *v, float scale, float* ans){
  ans[0] = v[0] * scale;
  ans[1] = v[1] * scale;
}
float norm2(float* v){
  return sqrt(v[0] * v[0] + v[1] * v[1]);
}
void normalize2(float* v){
  float n = norm2(v);
  scale2(v, 1./n, v);
}
void negate2(float* v, float* ans){
  ans[0] = -v[0];
  ans[1] = -v[1];
}
void perp2(float* v, float* ans){
  ans[0] = -v[1];
  ans[1] = v[0];
}
float dot2(float* v1, float*v2){
  return v1[0] * v2[0] + v1[1] * v2[1];
}
float copy2(float* frm, float* _to){
  _to[0] = frm[0];
  _to[1] = frm[1];
}
void print2(float* v, char* name){
  Serial.print(name);
  Serial.print(":[");
  Serial.print(v[0]);
  Serial.print(", ");
  Serial.print(v[1]);
  Serial.println("]");
}
