
#ifndef CP_WHITE_POINTS_DEFINED
#define CP_WHITE_POINTS_DEFINED

#include "CML.h"



typedef struct CPWhitePoints CPWhitePoints;
struct CPWhitePoints{
  CMLVec3 XYZ;
  CMLVec3 XYZunnorm;
  CMLVec3 Yxy;
  CMLVec3 Yupvp;
  CMLVec3 Yuv;
  CMLVec3 Ycd;
  CMLVec3 UVW;
};



void cp_FillChromaticAdaptationMatrix(
  CMLMat33 adaptationMatrix,
  const CMLVec3 whitePointYxy10);
  
CPWhitePoints cpGetWhitePoints(
  const CMLFunction* spec,
  const float* wpYxy,
  CMLFunction** observerFuncs);

#endif // CP_WHITE_POINTS_DEFINED
