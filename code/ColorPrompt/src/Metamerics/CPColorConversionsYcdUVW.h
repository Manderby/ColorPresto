
#ifndef CM_COLOR_CONVERSION_YCD_UVW_DEFINED
#define CM_COLOR_CONVERSION_YCD_UVW_DEFINED

#include "NAUtility/NAString.h"



typedef enum{
  REFERENCE_ILLUMINATION_D50,
  REFERENCE_ILLUMINATION_D55,
  REFERENCE_ILLUMINATION_D65,
  REFERENCE_ILLUMINATION_D75,
  NUMBER_OF_REFERENCE_ILLUMINATIONS
} CMReferenceIlluminationType;



void convertYcdtoadaptedYuv(float* yuv, const float* Ycd, const float* srcWhitePointYcd, const float* dstWhitePointYcd);


// ISO 3664 2009 Table D.9
const NAUTF8Char* getGrade(float value);



#endif // CM_COLOR_CONVERSION_YCD_UVW_DEFINED

