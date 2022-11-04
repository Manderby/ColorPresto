
#ifdef __cplusplus
  extern "C"{
#endif

#include "mainC.h"

CM_PROTOTYPE(NAOpenGLSpace);



typedef struct CMColorWell1D CMColorWell1D;



CMColorWell1D* cmAllocColorWell1D(
  CMColorController* colorController,
  size_t variableIndex);
  
void cmDeallocColorWell1D(CMColorWell1D* well);

NAOpenGLSpace* cmGetColorWell1DUIElement(CMColorWell1D* well);

void cmUpdateColorWell1D(CMColorWell1D* well);


#ifdef __cplusplus
  }
#endif
