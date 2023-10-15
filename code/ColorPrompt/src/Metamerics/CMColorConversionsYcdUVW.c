
#include "CMColorConversionsYcdUVW.h"
#include "../CPTranslations.h"
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
  if(value <= .25f){return cmTranslate(CMGradeA);}
  else if(value <= .5f){return cmTranslate(CMGradeB);}
  else if(value <= 1.f){return cmTranslate(CMGradeC);}
  else if(value <= 2.f){return cmTranslate(CMGradeD);}
  return cmTranslate(CMGradeE);
}
