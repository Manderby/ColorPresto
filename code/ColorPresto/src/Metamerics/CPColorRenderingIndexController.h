
#include "../mainC.h"

CP_PROTOTYPE(CPWhitePoints);
CP_PROTOTYPE(NASpace);



// /////////////////////
// ISO 3664 2009 D.4.2 Color Rendering index
// /////////////////////

typedef struct CPColorRenderingIndexController CPColorRenderingIndexController;

CPColorRenderingIndexController* cpAllocColorRenderingIndexController(void);
void cpDeallocColorRenderingIndexController(CPColorRenderingIndexController* con);

NASpace* cpGetColorRenderingIndexUIElement(CPColorRenderingIndexController* con);

void cpUpdateColorRenderingIndexController(
  CPColorRenderingIndexController* con,
  CMLFunction* observer2Funcs[3],
  const CPWhitePoints* illWhitePoint2,
  const CPWhitePoints* refWhitePoint2,
  const CMLFunction* refSpec,
  NABool valid);
