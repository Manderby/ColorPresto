
#include "mainC.h"

CM_PROTOTYPE(CMWhitePoints);
CM_PROTOTYPE(NASpace);



typedef struct CMTotalMetamericIndexController CMTotalMetamericIndexController;

CMTotalMetamericIndexController* cmAllocTotalMetamericIndexController(void);
void cmDeallocTotalMetamericIndexController(CMTotalMetamericIndexController* con);

NASpace* cmGetTotalMetamericIndexUIElement(CMTotalMetamericIndexController* con);

void cmUpdateTotalMetamericIndexController(
  CMTotalMetamericIndexController* con,
  float avg5,
  float avg3,
  NABool valid);
