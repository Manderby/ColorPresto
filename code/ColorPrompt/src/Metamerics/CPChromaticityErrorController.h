
#include "../mainC.h"

CP_PROTOTYPE(CPWhitePoints);
CP_PROTOTYPE(NASpace);



// /////////////////////
// ISO 3664 2009 D.4.1 Chromaticity Error
// /////////////////////

typedef struct CPChromaticityErrorController CPChromaticityErrorController;

CPChromaticityErrorController* cmAllocChromaticityErrorController(void);
void cmDeallocChromaticityErrorController(CPChromaticityErrorController* con);

NASpace* cmGetChromaticityErrorUIElement(CPChromaticityErrorController* con);

void cmUpdateChromaticityErrorController(
  CPChromaticityErrorController* con,
  const CPWhitePoints* refWhitePoint10,
  const CPWhitePoints* illWhitePoint10);
