
#include "../../mainC.h"

CP_PROTOTYPE(NAOpenGLSpace);



typedef struct CPGammaDisplayController CPGammaDisplayController;



CPGammaDisplayController* cmAllocGammaDisplayController(void);
  
void cmDeallocGammaDisplayController(CPGammaDisplayController* well);

NAOpenGLSpace* cmGetGammaDisplayControllerUIElement(CPGammaDisplayController* well);

void cmUpdateGammaDisplayController(CPGammaDisplayController* well);

