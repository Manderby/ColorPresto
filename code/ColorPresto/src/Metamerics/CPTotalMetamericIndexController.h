
#include "../main.h"

CP_PROTOTYPE(CPWhitePoints);
CP_PROTOTYPE(NASpace);



typedef struct CPTotalMetamericIndexController CPTotalMetamericIndexController;

CPTotalMetamericIndexController* cpAllocTotalMetamericIndexController(void);
void cpDeallocTotalMetamericIndexController(CPTotalMetamericIndexController* con);

NASpace* cpGetTotalMetamericIndexUIElement(CPTotalMetamericIndexController* con);

void cpUpdateTotalMetamericIndexController(
  CPTotalMetamericIndexController* con,
  float avg5,
  float avg3,
  NABool valid);
