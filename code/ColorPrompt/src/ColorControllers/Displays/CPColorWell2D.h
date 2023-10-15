
#include "../../mainC.h"

CM_PROTOTYPE(NAOpenGLSpace);



typedef struct CPColorWell2D CPColorWell2D;



CPColorWell2D* cmAllocColorWell2D(
  CPColorController* colorController,
  size_t fixedIndex);
  
void cmDeallocColorWell2D(CPColorWell2D* well);

void cmSetColorWell2DFixedIndex(CPColorWell2D* well, size_t fixedIndex);

NAOpenGLSpace* cmGetColorWell2DUIElement(CPColorWell2D* well);

void cmUpdateColorWell2D(CPColorWell2D* well);


