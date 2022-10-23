
#include "CMColorConversionsYcdUVW.h"
#include "CMMetamericsController.h"

#include "mainC.h"

CM_PROTOTYPE(CMWhitePoints);


// /////////////////////
// D.4.3 Visible range metameric index
// /////////////////////

typedef struct CMVisMetamericColors CMVisMetamericColors;
struct CMVisMetamericColors{
  CMLVec3 visStandardRGBFloatData[5];
  CMLVec3 visMetamerRGBFloatData[5];
  float metamericIndex[5];
};

CMVisMetamericColors cmComputeVisMetamericColors(
  CMLFunction* observer10Funcs[3],
  const CMWhitePoints* illWhitePoint10,
  const CMLMat33 adaptationMatrix,
  CMReferenceIlluminationType referenceIlluminationType);
