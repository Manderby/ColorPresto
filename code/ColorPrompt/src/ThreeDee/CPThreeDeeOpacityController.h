
#include "../mainC.h"
#include "NAApp.h"
#include "CPThreeDeeController.h"

CM_PROTOTYPE(CPWhitePoints);
CM_PROTOTYPE(NASpace);



typedef struct CPThreeDeeOpacityController CPThreeDeeOpacityController;
typedef struct CPThreeDeeOpacityController CPThreeDeeOpacityController;

CPThreeDeeOpacityController* cmAllocThreeDeeOpacityController(CPThreeDeeController* parent);
void cmDeallocThreeDeeOpacityController(CPThreeDeeOpacityController* con);

NASpace* cmGetThreeDeeOpacityControllerUIElement(CPThreeDeeOpacityController* con);

NABool cmGetThreeDeeOpacityControllerBodySolid(CPThreeDeeOpacityController* con);
float cmGetThreeDeeOpacityControllerPointsOpacity(CPThreeDeeOpacityController* con);
float cmGetThreeDeeOpacityControllerBodyAlpha(CPThreeDeeOpacityController* con);
float cmGetThreeDeeOpacityControllerGridAlpha(CPThreeDeeOpacityController* con);
float cmGetThreeDeeOpacityControllerGridTint(CPThreeDeeOpacityController* con);

void cmUpdateThreeDeeOpacityController(CPThreeDeeOpacityController* con);
