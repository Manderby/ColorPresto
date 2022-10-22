
#include "mainC.h"

CM_PROTOTYPE(CMWhitePoints);

// /////////////////////
// D.4.2 Color Rendering index
// /////////////////////

typedef struct CMColorRenderingColors CMColorRenderingColors;
struct CMColorRenderingColors{
  CMLVec3 crReferenceRGBFloatData[14];
  CMLVec3 crMetamerRGBFloatData[14];
  float colorRenderingIndex[14];
};

CMColorRenderingColors cmComputeColorRenderingColors(
  CMLFunction* observer2Funcs[3],
  const CMWhitePoints* refWhitePoint2,
  const CMWhitePoints* illWhitePoint2,
  const CMLFunction* refSpec);
