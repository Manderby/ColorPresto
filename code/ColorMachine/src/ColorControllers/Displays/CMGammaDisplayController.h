
#include "../../mainC.h"

CM_PROTOTYPE(NAOpenGLSpace);



typedef struct CMGammaDisplayController CMGammaDisplayController;



CMGammaDisplayController* cmAllocGammaDisplayController();
  
void cmDeallocGammaDisplayController(CMGammaDisplayController* well);

NAOpenGLSpace* cmGetGammaDisplayControllerUIElement(CMGammaDisplayController* well);

void cmUpdateGammaDisplayController(CMGammaDisplayController* well);

