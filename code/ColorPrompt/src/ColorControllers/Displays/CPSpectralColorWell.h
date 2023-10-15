
#include "../../mainC.h"

CM_PROTOTYPE(NAOpenGLSpace);



typedef struct CPSpectralColorWell CPSpectralColorWell;



CPSpectralColorWell* cmAllocSpectralColorWell(
  CPColorController* colorController);
  
void cmDeallocSpectralColorWell(CPSpectralColorWell* well);

NAOpenGLSpace* cmGetSpectralColorWellUIElement(CPSpectralColorWell* well);

void cmUpdateSpectralColorWell(CPSpectralColorWell* well);


