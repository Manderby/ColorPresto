
#include "../../mainC.h"

CP_PROTOTYPE(NAOpenGLSpace);



typedef struct CPGrayColorWell CPGrayColorWell;



CPGrayColorWell* cpAllocGrayColorWell(
  CPColorController* colorController);
  
void cpDeallocGrayColorWell(CPGrayColorWell* well);

NAOpenGLSpace* cpGetGrayColorWellUIElement(CPGrayColorWell* well);

void cpUpdateGrayColorWell(CPGrayColorWell* well);


