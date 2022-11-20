
#include "mainC.h"
#include "NAApp.h"
#include "CMThreeDeeController.h"

CM_PROTOTYPE(CMWhitePoints);
CM_PROTOTYPE(NASpace);



typedef struct CMRotationController CMRotationController;

CMRotationController* cmAllocRotationController(CMThreeDeeController* parentController);
void cmDeallocRotationController(CMRotationController* con);

NABool cmMoveRotationMouse(NAReaction reaction);
NABool cmScrollRotation(NAReaction reaction);

NASpace* cmGetRotationUIElement(CMRotationController* con);

double cmGetRotationStep(CMRotationController* con);
double cmGetRotationViewPol(CMRotationController* con);
double cmGetRotationViewEqu(CMRotationController* con);
double cmGetRotationZoom(CMRotationController* con);
void cmSetRotationZoom(CMRotationController* con, double zoom);

void cmUpdateRotationController(CMRotationController* con);
