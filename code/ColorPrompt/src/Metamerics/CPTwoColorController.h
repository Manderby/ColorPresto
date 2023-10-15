
#include "NAMath/NAVectorAlgebra.h"
#include "../mainC.h"

CP_PROTOTYPE(NASpace);
CP_PROTOTYPE(NAOpenGLSpace);



typedef struct CPTwoColorController CPTwoColorController;

CPTwoColorController* cmAllocTwoColorController(void);
void cmDeallocTwoColorController(CPTwoColorController* con);

NAOpenGLSpace* cmGetTwoColorControllerUIElement(CPTwoColorController* con);

void cmUpdateTwoColorController(
  CPTwoColorController* con,
  const float* leftColor,
  const float* rightColor);
  
  

