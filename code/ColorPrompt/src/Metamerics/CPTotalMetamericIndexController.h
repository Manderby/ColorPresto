
#include "../mainC.h"

CM_PROTOTYPE(CPWhitePoints);
CM_PROTOTYPE(NASpace);



typedef struct CPTotalMetamericIndexController CPTotalMetamericIndexController;

CPTotalMetamericIndexController* cmAllocTotalMetamericIndexController(void);
void cmDeallocTotalMetamericIndexController(CPTotalMetamericIndexController* con);

NASpace* cmGetTotalMetamericIndexUIElement(CPTotalMetamericIndexController* con);

void cmUpdateTotalMetamericIndexController(
  CPTotalMetamericIndexController* con,
  float avg5,
  float avg3,
  NABool valid);
