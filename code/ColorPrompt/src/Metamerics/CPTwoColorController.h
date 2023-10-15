
#include "NAMath/NAVectorAlgebra.h"
#include "../mainC.h"

CP_PROTOTYPE(NASpace);
CP_PROTOTYPE(NAOpenGLSpace);



typedef struct CPTwoColorController CPTwoColorController;

CPTwoColorController* cpAllocTwoColorController(void);
void cpDeallocTwoColorController(CPTwoColorController* con);

NAOpenGLSpace* cpGetTwoColorControllerUIElement(CPTwoColorController* con);

void cpUpdateTwoColorController(
  CPTwoColorController* con,
  const float* leftColor,
  const float* rightColor);
  
  

