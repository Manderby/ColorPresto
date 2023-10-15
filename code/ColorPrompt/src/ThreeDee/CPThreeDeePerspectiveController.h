
#include "../mainC.h"
#include "NAApp.h"
#include "CPThreeDeeController.h"

CP_PROTOTYPE(CPWhitePoints);
CP_PROTOTYPE(NASpace);



typedef struct CPThreeDeePerspectiveController CPThreeDeePerspectiveController;

CPThreeDeePerspectiveController* cmAllocThreeDeePerspectiveController(CPThreeDeeController* parent);
void cmDeallocThreeDeePerspectiveController(CPThreeDeePerspectiveController* con);

NABool cmMoveRotationMouse(NAReaction reaction);
NABool cmScrollRotation(NAReaction reaction);

NASpace* cmGetThreeDeePerspectiveControllerUIElement(CPThreeDeePerspectiveController* con);

double cmGetThreeDeePerspectiveControllerRotationStep(CPThreeDeePerspectiveController* con);
double cmGetThreeDeePerspectiveControllerRotationAnglePol(CPThreeDeePerspectiveController* con);
double cmGetThreeDeePerspectiveControllerRotationAngleEqu(CPThreeDeePerspectiveController* con);
double cmGetThreeDeePerspectiveControllerZoom(CPThreeDeePerspectiveController* con);
void cmSetThreeDeePerspectiveControllerZoom(CPThreeDeePerspectiveController* con, double zoom);

void cmUpdateThreeDeePerspectiveController(CPThreeDeePerspectiveController* con);
