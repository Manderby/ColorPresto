
#include "CMColorConversionsYcdUVW.h"
#include "CMMetamericsController.h"

#include "../mainC.h"

CM_PROTOTYPE(CMWhitePoints);
CM_PROTOTYPE(NASpace);



// /////////////////////
// ISO 3664 2009 D.4.3 Visible range metameric index
// /////////////////////

typedef struct CMVisMetamericIndexController CMVisMetamericIndexController;

CMVisMetamericIndexController* cmAllocVisMetamericIndexController(void);
void cmDeallocVisMetamericIndexController(CMVisMetamericIndexController* con);

NASpace* cmGetVisMetamericIndexUIElement(CMVisMetamericIndexController* con);
float cmGetVisMetamericIndexAverage(CMVisMetamericIndexController* con);

void cmUpdateVisMetamericIndexController(
  CMVisMetamericIndexController* con,
  CMLFunction* observer10Funcs[3],
  const CMWhitePoints* illWhitePoint10,
  const CMLMat33 adaptationMatrix,
  CMReferenceIlluminationType referenceIlluminationType,
  NABool valid);
