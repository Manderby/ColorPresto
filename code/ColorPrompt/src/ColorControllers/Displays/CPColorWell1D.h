
#include "../../mainC.h"

CP_PROTOTYPE(NAOpenGLSpace);



typedef struct CPColorWell1D CPColorWell1D;



CPColorWell1D* cmAllocColorWell1D(
  CPColorController* colorController,
  const float* colorData,
  size_t variableIndex);
  
void cmDeallocColorWell1D(CPColorWell1D* well);

NAOpenGLSpace* cmGetColorWell1DUIElement(CPColorWell1D* well);

void cpUpdateColorWell1D(CPColorWell1D* well);


