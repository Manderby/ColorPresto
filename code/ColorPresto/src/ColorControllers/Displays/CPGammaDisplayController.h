
#include "../../main.h"

CP_PROTOTYPE(NAOpenGLSpace);



typedef struct CPGammaDisplayController CPGammaDisplayController;



CPGammaDisplayController* cpAllocGammaDisplayController(void);
  
void cpDeallocGammaDisplayController(CPGammaDisplayController* well);

NAOpenGLSpace* cpGetGammaDisplayControllerUIElement(CPGammaDisplayController* well);

void cpUpdateGammaDisplayController(CPGammaDisplayController* well);

