
#include "../../mainC.h"

CM_PROTOTYPE(NAOpenGLSpace);



typedef struct CMSpectralColorWell CMSpectralColorWell;



CMSpectralColorWell* cmAllocSpectralColorWell(
  CMColorController* colorController);
  
void cmDeallocSpectralColorWell(CMSpectralColorWell* well);

NAOpenGLSpace* cmGetSpectralColorWellUIElement(CMSpectralColorWell* well);

void cmUpdateSpectralColorWell(CMSpectralColorWell* well);


