
#include "../mainC.h"

CM_PROTOTYPE(CPWhitePoints);
CM_PROTOTYPE(NASpace);



// /////////////////////
// ISO 3664 2009 D.4.2 Color Rendering index
// /////////////////////

typedef struct CPColorRenderingIndexController CPColorRenderingIndexController;

CPColorRenderingIndexController* cmAllocColorRenderingIndexController(void);
void cmDeallocColorRenderingIndexController(CPColorRenderingIndexController* con);

NASpace* cmGetColorRenderingIndexUIElement(CPColorRenderingIndexController* con);

void cmUpdateColorRenderingIndexController(
  CPColorRenderingIndexController* con,
  CMLFunction* observer2Funcs[3],
  const CPWhitePoints* illWhitePoint2,
  const CPWhitePoints* refWhitePoint2,
  const CMLFunction* refSpec,
  NABool valid);
