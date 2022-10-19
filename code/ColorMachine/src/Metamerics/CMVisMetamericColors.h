
#include "CMMetamericsController.h"
#include "mainC.h"

CM_PROTOTYPE(CMWhitePoints);


// /////////////////////
// D.4.3 Visible range metameric index
// /////////////////////

typedef struct VisMetamericColors VisMetamericColors;
struct VisMetamericColors{
  CMLVec3 visStandardRGBFloatData[5];
  CMLVec3 visMetamerRGBFloatData[5];
  float metamericIndex[5];
};

VisMetamericColors cmComputeVisMetamericColors(
  CMLFunction* observer10Funcs[3],
  const CMWhitePoints* wp,
  const CMLMat33 adaptationMatrix,
  CMReferenceIlluminationType referenceIlluminationType);
