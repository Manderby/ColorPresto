
#include "CMMetamericsController.h"
#include "mainC.h"

CM_PROTOTYPE(CMLFunction);
CM_PROTOTYPE(CMWhitePoints);

// /////////////////////
// D.4.3 Ultraviolet range metameric index
// /////////////////////

typedef struct CMUVMetamericColors CMUVMetamericColors;
struct CMUVMetamericColors{
  CMLVec3 uvStandardRGBFloatData[3];
  CMLVec3 uvMetamerRGBFloatData[3];
  float metamericIndex[3];
};

CMUVMetamericColors cmComputeUVMetamericColors(
  CMLFunction* observer10Funcs[3],
  const CMWhitePoints* illWhitePoint10,
  CMReferenceIlluminationType referenceIlluminationType);
