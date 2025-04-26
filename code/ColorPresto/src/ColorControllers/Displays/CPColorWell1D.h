
#include "../../main.h"

CP_PROTOTYPE(NAOpenGLSpace);



typedef struct CPColorWell1D CPColorWell1D;



CPColorWell1D* cpAllocColorWell1D(
  CPColorController* colorController,
  const float* colorData,
  size_t variableIndex);
  
void cpDeallocColorWell1D(CPColorWell1D* well);

NAOpenGLSpace* cpGetColorWell1DUIElement(CPColorWell1D* well);

void cpComputeColorWell1D(CPColorWell1D* well);
void cpUpdateColorWell1D(CPColorWell1D* well);


