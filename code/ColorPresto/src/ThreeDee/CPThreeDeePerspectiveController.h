
#include "../mainC.h"
#include "NAApp/NAApp.h"
#include "CPThreeDeeController.h"

CP_PROTOTYPE(CPWhitePoints);
CP_PROTOTYPE(NASpace);



typedef struct CPThreeDeePerspectiveController CPThreeDeePerspectiveController;

CPThreeDeePerspectiveController* cpAllocThreeDeePerspectiveController(CPThreeDeeController* parent);
void cpDeallocThreeDeePerspectiveController(CPThreeDeePerspectiveController* con);

void cpMoveRotationMouse(NAReaction reaction);
void cpScrollRotation(NAReaction reaction);

NASpace* cpGetThreeDeePerspectiveControllerUIElement(CPThreeDeePerspectiveController* con);

double cpGetThreeDeePerspectiveControllerRotationStep(CPThreeDeePerspectiveController* con);
double cpGetThreeDeePerspectiveControllerRotationAnglePol(CPThreeDeePerspectiveController* con);
double cpGetThreeDeePerspectiveControllerRotationAngleEqu(CPThreeDeePerspectiveController* con);
double cpGetThreeDeePerspectiveControllerZoom(CPThreeDeePerspectiveController* con);
void cpSetThreeDeePerspectiveControllerZoom(CPThreeDeePerspectiveController* con, double zoom);

void cpUpdateThreeDeePerspectiveController(CPThreeDeePerspectiveController* con);
