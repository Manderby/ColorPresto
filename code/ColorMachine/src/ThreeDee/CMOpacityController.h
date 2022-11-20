
#include "mainC.h"
#include "NAApp.h"
#include "CMThreeDeeController.h"

CM_PROTOTYPE(CMWhitePoints);
CM_PROTOTYPE(NASpace);



typedef struct CMOpacityController CMOpacityController;

CMOpacityController* cmAllocOpacityController(CMThreeDeeController* parentController);
void cmDeallocOpacityController(CMOpacityController* con);

NASpace* cmGetOpacityUIElement(CMOpacityController* con);

NABool cmGetOpacityBodySolid(CMOpacityController* con);
double cmGetOpacityPointsOpacity(CMOpacityController* con);
double cmGetOpacityBodyAlpha(CMOpacityController* con);
double cmGetOpacityGridAlpha(CMOpacityController* con);
double cmGetOpacityGridTint(CMOpacityController* con);

void cmUpdateOpacityController(CMOpacityController* con);
