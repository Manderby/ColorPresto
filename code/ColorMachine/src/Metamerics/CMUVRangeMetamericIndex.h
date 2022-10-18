
#include "CMMetamericsController.h"
#include "mainC.h"
CM_PROTOTYPE(CMLFunction);

// /////////////////////
// D.4.3 Ultraviolet range metameric index
// /////////////////////

typedef struct UVMetamericColors UVMetamericColors;
struct UVMetamericColors{
  CMLVec3 uvStandardRGBFloatData[3];
  CMLVec3 uvMetamerRGBFloatData[3];
};

UVMetamericColors cmComputeUVMetamericColors(
  CMReferenceIlluminationType referenceIlluminationType);
