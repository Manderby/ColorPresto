
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



void convertYuvtoYcd(float* Ycd, const float* yuv);

void convertYcdtoadaptedYuv(float* yuv, const float* Ycd, const float* srcWhitePointYcd, const float* dstWhitePointYcd);

// ISO 3664 states in forumal D.14 the computation 6X/(X+15Y+3Z). I'm
// pretty sure, they meant  6Y/(X+15Y+3Z) which is according to
// CIE 1960 UCS. This also corresponds to the fact that UVW is based on UCS.
// In CML, this is Yuv.
// UVW is CIE 1964.
void convertYuvtoUVW(float* UVW, float* yuv, const float* whitePointYuv);

// ISO 3664 2009 Table D.9
const NAUTF8Char* getGrade(float value);



#endif // CM_COLOR_CONVERSION_YCD_UVW_DEFINED

