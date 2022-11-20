
#ifdef __cplusplus
  extern "C"{
#endif

#include "mainC.h"

CM_PROTOTYPE(NAOpenGLSpace);



typedef struct CMGammaDisplayController CMGammaDisplayController;



CMGammaDisplayController* cmAllocGammaDisplayController();
  
void cmDeallocGammaDisplayController(CMGammaDisplayController* well);

NAOpenGLSpace* cmGetGammaDisplayControllerUIElement(CMGammaDisplayController* well);

void cmUpdateGammaDisplayController(CMGammaDisplayController* well);


#ifdef __cplusplus
  }
#endif
