
#include "mainC.h"
#include "CMThreeDeeController.h"

CM_PROTOTYPE(CMWhitePoints);
CM_PROTOTYPE(NASpace);



typedef struct CMCoordinateController CMCoordinateController;

CMCoordinateController* cmAllocCoordinateController(CMThreeDeeController* parentController);
void cmDeallocCoordinateController(CMCoordinateController* con);

NASpace* cmGetCoordinateUIElement(CMCoordinateController* con);

CoordSysType cmGetCoordinateCoordSysType(CMCoordinateController* con);
CMLColorType cmGetCoordinateColorSpaceType(CMCoordinateController* con);
NAInt cmGetCoordinateSteps3D(CMCoordinateController* con);

void cmUpdateCoordinateController(CMCoordinateController* con);
