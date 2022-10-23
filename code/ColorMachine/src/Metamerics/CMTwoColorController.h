#ifdef __cplusplus
  extern "C"{
#endif

#include "NAMath/NAVectorAlgebra.h"
#include "mainC.h"

CM_PROTOTYPE(NASpace);
CM_PROTOTYPE(NAOpenGLSpace);



typedef struct CMTwoColorController CMTwoColorController;

CMTwoColorController* cmAllocTwoColorController(NASize size);
void cmDeallocTwoColorController(CMTwoColorController* con);

NAOpenGLSpace* cmGetTwoColorControllerUIElement(CMTwoColorController* con);

void cmUpdateTwoColorController(
  CMTwoColorController* con,
  NAVec3f leftColor,
  NAVec3f rightColor);
  
  

#ifdef __cplusplus
  }
#endif
