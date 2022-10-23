
#include "mainC.h"

CM_PROTOTYPE(CMWhitePoints);
CM_PROTOTYPE(NASpace);



// /////////////////////
// ISO 3664 2009 D.4.1 Chromaticity Error
// /////////////////////

typedef struct CMChromaticityErrorController CMChromaticityErrorController;

CMChromaticityErrorController* cmAllocChromaticityErrorController(void);
void cmDeallocChromaticityErrorController(CMChromaticityErrorController* con);

NASpace* cmGetChromaticityErrorUIElement(CMChromaticityErrorController* con);

void cmUpdateChromaticityErrorController(
  CMChromaticityErrorController* con,
  const CMWhitePoints* refWhitePoint10,
  const CMWhitePoints* illWhitePoint10);
