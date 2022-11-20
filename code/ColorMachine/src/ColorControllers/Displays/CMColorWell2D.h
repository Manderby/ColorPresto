
#ifdef __cplusplus
  extern "C"{
#endif

#include "mainC.h"

CM_PROTOTYPE(NAOpenGLSpace);



typedef struct CMColorWell2D CMColorWell2D;



CMColorWell2D* cmAllocColorWell2D(
  CMColorController* colorController,
  size_t fixedIndex);
  
void cmDeallocColorWell2D(CMColorWell2D* well);

NAOpenGLSpace* cmGetColorWell2DUIElement(CMColorWell2D* well);

void cmUpdateColorWell2D(CMColorWell2D* well);


#ifdef __cplusplus
  }
#endif
