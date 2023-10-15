
#include "CPColorConversionsYcdUVW.h"
#include "CPMetamericsController.h"

#include "../mainC.h"

CP_PROTOTYPE(CPWhitePoints);
CP_PROTOTYPE(NASpace);



// /////////////////////
// ISO 3664 2009 D.4.3 Visible range metameric index
// /////////////////////

typedef struct CPVisMetamericIndexController CPVisMetamericIndexController;

CPVisMetamericIndexController* cmAllocVisMetamericIndexController(void);
void cmDeallocVisMetamericIndexController(CPVisMetamericIndexController* con);

NASpace* cmGetVisMetamericIndexUIElement(CPVisMetamericIndexController* con);
float cmGetVisMetamericIndexAverage(CPVisMetamericIndexController* con);

void cmUpdateVisMetamericIndexController(
  CPVisMetamericIndexController* con,
  CMLFunction* observer10Funcs[3],
  const CPWhitePoints* illWhitePoint10,
  const CMLMat33 adaptationMatrix,
  CPReferenceIlluminationType referenceIlluminationType,
  NABool valid);
