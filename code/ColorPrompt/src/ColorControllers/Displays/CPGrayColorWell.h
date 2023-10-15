
#include "../../mainC.h"

CM_PROTOTYPE(NAOpenGLSpace);



typedef struct CPGrayColorWell CPGrayColorWell;



CPGrayColorWell* cmAllocGrayColorWell(
  CPColorController* colorController);
  
void cmDeallocGrayColorWell(CPGrayColorWell* well);

NAOpenGLSpace* cmGetGrayColorWellUIElement(CPGrayColorWell* well);

void cmUpdateGrayColorWell(CPGrayColorWell* well);


