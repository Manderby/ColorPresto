
#ifndef CM_WHITE_POINTS_DEFINED
#define CM_WHITE_POINTS_DEFINED

#include "CML.h"



typedef struct CMWhitePoints CMWhitePoints;
struct CMWhitePoints{
  CMLVec3 XYZ;
  CMLVec3 XYZunnorm;
  CMLVec3 Yxy;
  CMLVec3 Yupvp;
  CMLVec3 Yuv;
  CMLVec3 Ycd;
};



void CMFillChromaticAdaptationMatrix(
  CMLMat33 adaptationMatrix,
  const CMLVec3 whitePointYxy10);
  
CMWhitePoints CMGetWhitePoints(
  const CMLFunction* spec,
  const float* wpYxy,
  CMLFunction** observerFuncs);

#endif // CM_WHITE_POINTS_DEFINED
