
#include "CMMetamericsController.h"
#include "mainC.h"

CM_PROTOTYPE(CMLFunction);
CM_PROTOTYPE(CMWhitePoints);

// /////////////////////
// D.4.3 Ultraviolet range metameric index
// /////////////////////

typedef struct UVMetamericColors UVMetamericColors;
struct UVMetamericColors{
  CMLVec3 uvStandardRGBFloatData[3];
  CMLVec3 uvMetamerRGBFloatData[3];
  float metamericIndex[3];
};

UVMetamericColors cmComputeUVMetamericColors(
  CMLFunction* observer10Funcs[3],
  const CMWhitePoints* wp,
  CMReferenceIlluminationType referenceIlluminationType);
