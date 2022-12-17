
#include "CMColorConversionsYcdUVW.h"
#include "../mainC.h"


// todo: add conversions to main window or even CML.

void convertYcdtoadaptedYuv(float* yuv, const float* Ycd, const float* srcWhitePointYcd, const float* dstWhitePointYcd){
  float cfactor = Ycd[1] * dstWhitePointYcd[1] / srcWhitePointYcd[1];
  float dfactor = Ycd[2] * dstWhitePointYcd[2] / srcWhitePointYcd[2];
  float divisor = (16.518f + 1.481f * cfactor - dfactor);
  yuv[0] = Ycd[0];
  yuv[1] = (10.872f + 0.404f * cfactor - 4.f * dfactor) / divisor;
  yuv[2] = 5.520f / divisor;
}

const NAUTF8Char* getGrade(float value){
  if(value <= .25f){return "A";}
  else if(value <= .5f){return "B";}
  else if(value <= 1.f){return "C";}
  else if(value <= 2.f){return "D";}
  return "E";
}
