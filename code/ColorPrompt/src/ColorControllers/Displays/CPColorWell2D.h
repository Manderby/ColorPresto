
#include "../../mainC.h"

CP_PROTOTYPE(NAOpenGLSpace);



typedef struct CPColorWell2D CPColorWell2D;



CPColorWell2D* cpAllocColorWell2D(
  CPColorController* colorController,
  size_t fixedIndex);
  
void cpDeallocColorWell2D(CPColorWell2D* well);

void cpSetColorWell2DFixedIndex(CPColorWell2D* well, size_t fixedIndex);

NAOpenGLSpace* cpGetColorWell2DUIElement(CPColorWell2D* well);

void cpUpdateColorWell2D(CPColorWell2D* well);


