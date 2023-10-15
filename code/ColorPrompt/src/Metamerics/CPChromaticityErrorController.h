
#include "../mainC.h"

CP_PROTOTYPE(CPWhitePoints);
CP_PROTOTYPE(NASpace);



// /////////////////////
// ISO 3664 2009 D.4.1 Chromaticity Error
// /////////////////////

typedef struct CPChromaticityErrorController CPChromaticityErrorController;

CPChromaticityErrorController* cpAllocChromaticityErrorController(void);
void cpDeallocChromaticityErrorController(CPChromaticityErrorController* con);

NASpace* cpGetChromaticityErrorUIElement(CPChromaticityErrorController* con);

void cpUpdateChromaticityErrorController(
  CPChromaticityErrorController* con,
  const CPWhitePoints* refWhitePoint10,
  const CPWhitePoints* illWhitePoint10);
