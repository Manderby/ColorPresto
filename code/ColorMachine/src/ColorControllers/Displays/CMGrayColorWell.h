
#include "../../mainC.h"

CM_PROTOTYPE(NAOpenGLSpace);



typedef struct CMGrayColorWell CMGrayColorWell;



CMGrayColorWell* cmAllocGrayColorWell(
  CMColorController* colorController);
  
void cmDeallocGrayColorWell(CMGrayColorWell* well);

NAOpenGLSpace* cmGetGrayColorWellUIElement(CMGrayColorWell* well);

void cmUpdateGrayColorWell(CMGrayColorWell* well);


