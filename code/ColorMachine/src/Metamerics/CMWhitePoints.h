
#ifndef CM_WHITE_POINTS_DEFINED
#define CM_WHITE_POINTS_DEFINED

#include "CML.h"

typedef struct CMWhitePoints CMWhitePoints;
struct CMWhitePoints{
  CMLVec3 illXYZ10;
  CMLVec3 illXYZ2;
  CMLVec3 illXYZunnorm10;
  CMLVec3 illXYZunnorm2;
  CMLVec3 illYxy10;
  CMLVec3 illYxy2;
};

void CMFillChromaticAdaptationMatrix(
  CMLMat33 adaptationMatrix,
  const CMLVec3 whitePointYxy10);
  
CMWhitePoints CMGetWhitePoints();

#endif // CM_WHITE_POINTS_DEFINED
