
#include "CPColorConversionsYcdUVW.h"
#include "CPMetamericsController.h"

#include "../mainC.h"

CM_PROTOTYPE(CMLFunction);
CM_PROTOTYPE(CPWhitePoints);
CM_PROTOTYPE(NASpace);



// /////////////////////
// ISO 3664 2009 D.4.3 Ultraviolet range metameric index
// /////////////////////

typedef struct CPUVMetamericIndexController CPUVMetamericIndexController;

CPUVMetamericIndexController* cmAllocUVMetamericIndexController(void);
void cmDeallocUVMetamericIndexController(CPUVMetamericIndexController* con);

NASpace* cmGetUVMetamericIndexUIElement(CPUVMetamericIndexController* con);
float cmGetUVMetamericIndexAverage(CPUVMetamericIndexController* con);

void cmUpdateUVMetamericIndexController(
  CPUVMetamericIndexController* con,
  CMLFunction* observer10Funcs[3],
  const CPWhitePoints* illWhitePoint10,
  CMReferenceIlluminationType referenceIlluminationType,
  NABool valid);
