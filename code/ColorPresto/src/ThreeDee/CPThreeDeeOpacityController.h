
#include "../mainC.h"
#include "NAApp/NAApp.h"
#include "CPThreeDeeController.h"

CP_PROTOTYPE(CPWhitePoints);
CP_PROTOTYPE(NASpace);



typedef struct CPThreeDeeOpacityController CPThreeDeeOpacityController;
typedef struct CPThreeDeeOpacityController CPThreeDeeOpacityController;

CPThreeDeeOpacityController* cpAllocThreeDeeOpacityController(CPThreeDeeController* parent);
void cpDeallocThreeDeeOpacityController(CPThreeDeeOpacityController* con);

NASpace* cpGetThreeDeeOpacityControllerUIElement(CPThreeDeeOpacityController* con);

NABool cpGetThreeDeeOpacityControllerBodySolid(CPThreeDeeOpacityController* con);
float cpGetThreeDeeOpacityControllerPointsOpacity(CPThreeDeeOpacityController* con);
float cpGetThreeDeeOpacityControllerBodyAlpha(CPThreeDeeOpacityController* con);
float cpGetThreeDeeOpacityControllerGridAlpha(CPThreeDeeOpacityController* con);
float cpGetThreeDeeOpacityControllerGridTint(CPThreeDeeOpacityController* con);

void cpUpdateThreeDeeOpacityController(CPThreeDeeOpacityController* con);
