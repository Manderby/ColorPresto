
#include "../mainC.h"
#include "NAApp.h"
#include "CMThreeDeeController.h"

CM_PROTOTYPE(CMWhitePoints);
CM_PROTOTYPE(NASpace);



typedef struct CMThreeDeeOpacityController CMThreeDeeOpacityController;
typedef struct CMThreeDeeOpacityController CMThreeDeeOpacityController;

CMThreeDeeOpacityController* cmAllocThreeDeeOpacityController(CMThreeDeeController* parent);
void cmDeallocThreeDeeOpacityController(CMThreeDeeOpacityController* con);

NASpace* cmGetThreeDeeOpacityControllerUIElement(CMThreeDeeOpacityController* con);

NABool cmGetThreeDeeOpacityControllerBodySolid(CMThreeDeeOpacityController* con);
float cmGetThreeDeeOpacityControllerPointsOpacity(CMThreeDeeOpacityController* con);
float cmGetThreeDeeOpacityControllerBodyAlpha(CMThreeDeeOpacityController* con);
float cmGetThreeDeeOpacityControllerGridAlpha(CMThreeDeeOpacityController* con);
float cmGetThreeDeeOpacityControllerGridTint(CMThreeDeeOpacityController* con);

void cmUpdateThreeDeeOpacityController(CMThreeDeeOpacityController* con);
