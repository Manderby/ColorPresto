
#include "../mainC.h"
#include "NAApp.h"
#include "CMThreeDeeController.h"

CM_PROTOTYPE(CMWhitePoints);
CM_PROTOTYPE(NASpace);



typedef struct CMThreeDeePerspectiveController CMThreeDeePerspectiveController;

CMThreeDeePerspectiveController* cmAllocThreeDeePerspectiveController(CMThreeDeeController* parent);
void cmDeallocThreeDeePerspectiveController(CMThreeDeePerspectiveController* con);

NABool cmMoveRotationMouse(NAReaction reaction);
NABool cmScrollRotation(NAReaction reaction);

NASpace* cmGetThreeDeePerspectiveControllerUIElement(CMThreeDeePerspectiveController* con);

double cmGetThreeDeePerspectiveControllerRotationStep(CMThreeDeePerspectiveController* con);
double cmGetThreeDeePerspectiveControllerRotationAnglePol(CMThreeDeePerspectiveController* con);
double cmGetThreeDeePerspectiveControllerRotationAngleEqu(CMThreeDeePerspectiveController* con);
double cmGetThreeDeePerspectiveControllerZoom(CMThreeDeePerspectiveController* con);
void cmSetThreeDeePerspectiveControllerZoom(CMThreeDeePerspectiveController* con, double zoom);

void cmUpdateThreeDeePerspectiveController(CMThreeDeePerspectiveController* con);
