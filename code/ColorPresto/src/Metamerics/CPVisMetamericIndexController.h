
#include "CPColorConversionsYcdUVW.h"
#include "CPMetamericsController.h"

#include "../main.h"

CP_PROTOTYPE(CPWhitePoints);
CP_PROTOTYPE(NASpace);



// /////////////////////
// ISO 3664 2009 D.4.3 Visible range metameric index
// /////////////////////

typedef struct CPVisMetamericIndexController CPVisMetamericIndexController;

CPVisMetamericIndexController* cpAllocVisMetamericIndexController(void);
void cpDeallocVisMetamericIndexController(CPVisMetamericIndexController* con);

NASpace* cpGetVisMetamericIndexUIElement(CPVisMetamericIndexController* con);
float cpGetVisMetamericIndexAverage(CPVisMetamericIndexController* con);

void cpUpdateVisMetamericIndexController(
  CPVisMetamericIndexController* con,
  CMLFunction* observer10Funcs[3],
  const CPWhitePoints* illWhitePoint10,
  const CMLMat33 adaptationMatrix,
  CPReferenceIlluminationType referenceIlluminationType,
  NABool valid);
