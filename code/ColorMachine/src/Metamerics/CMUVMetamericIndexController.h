
#include "CMColorConversionsYcdUVW.h"
#include "CMMetamericsController.h"

#include "mainC.h"

CM_PROTOTYPE(CMLFunction);
CM_PROTOTYPE(CMWhitePoints);
CM_PROTOTYPE(NASpace);



// /////////////////////
// D.4.3 Ultraviolet range metameric index
// /////////////////////

typedef struct CMUVMetamericIndexController CMUVMetamericIndexController;

CMUVMetamericIndexController* cmAllocUVMetamericIndexController(void);
void cmDeallocUVMetamericIndexController(CMUVMetamericIndexController* con);

NASpace* cmGetUVMetamericIndexUIElement(CMUVMetamericIndexController* con);
float cmGetUVMetamericIndexAverage(CMUVMetamericIndexController* con);

void cmUpdateUVMetamericIndexController(
  CMUVMetamericIndexController* con,
  CMLFunction* observer10Funcs[3],
  const CMWhitePoints* illWhitePoint10,
  CMReferenceIlluminationType referenceIlluminationType);
