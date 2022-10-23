
#include "mainC.h"

CM_PROTOTYPE(CMWhitePoints);
CM_PROTOTYPE(NASpace);



// /////////////////////
// D.4.2 Color Rendering index
// /////////////////////

typedef struct CMColorRenderingIndexController CMColorRenderingIndexController;

CMColorRenderingIndexController* cmAllocColorRenderingIndexController(void);
void cmDeallocColorRenderingIndexController(CMColorRenderingIndexController* con);

NASpace* cmGetColorRenderingIndexUIElement(CMColorRenderingIndexController* con);

void cmUpdateColorRenderingIndexController(
  CMColorRenderingIndexController* con,
  CMLFunction* observer2Funcs[3],
  const CMWhitePoints* illWhitePoint2,
  const CMWhitePoints* refWhitePoint2,
  const CMLFunction* refSpec);
