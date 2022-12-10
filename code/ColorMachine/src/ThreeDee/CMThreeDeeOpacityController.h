
#include "../mainC.h"
#include "NAApp.h"
#include "CMThreeDeeController.h"

CM_PROTOTYPE(CMWhitePoints);
CM_PROTOTYPE(NASpace);



typedef struct CMThreeDeeOpacityController CMThreeDeeOpacityController;

CMThreeDeeOpacityController* cmAllocThreeDeeOpacityController(CMThreeDeeController* parent);
void cmDeallocThreeDeeOpacityController(CMThreeDeeOpacityController* con);

NASpace* cmGetThreeDeeOpacityControllerUIElement(CMThreeDeeOpacityController* con);

NABool cmGetThreeDeeOpacityControllerBodySolid(CMThreeDeeOpacityController* con);
double cmGetThreeDeeOpacityControllerPointsOpacity(CMThreeDeeOpacityController* con);
double cmGetThreeDeeOpacityControllerBodyAlpha(CMThreeDeeOpacityController* con);
double cmGetThreeDeeOpacityControllerGridAlpha(CMThreeDeeOpacityController* con);
double cmGetThreeDeeOpacityControllerGridTint(CMThreeDeeOpacityController* con);

void cmUpdateThreeDeeOpacityController(CMThreeDeeOpacityController* con);
