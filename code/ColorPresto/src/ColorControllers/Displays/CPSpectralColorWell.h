
#include "../../main.h"

CP_PROTOTYPE(NAOpenGLSpace);



typedef struct CPSpectralColorWell CPSpectralColorWell;



CPSpectralColorWell* cpAllocSpectralColorWell(
  CPColorController* colorController);
  
void cpDeallocSpectralColorWell(CPSpectralColorWell* well);

NAOpenGLSpace* cpGetSpectralColorWellUIElement(CPSpectralColorWell* well);

void cpUpdateSpectralColorWell(CPSpectralColorWell* well);


