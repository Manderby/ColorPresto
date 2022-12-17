
#include "../mainC.h"
#include "CMThreeDeeController.h"

CM_PROTOTYPE(CMWhitePoints);
CM_PROTOTYPE(NASpace);



typedef struct CMThreeDeeCoordinateController CMThreeDeeCoordinateController;

CMThreeDeeCoordinateController* cmAllocThreeDeeCoordinateController(CMThreeDeeController* threeDeeController);
void cmDeallocThreeDeeCoordinateController(CMThreeDeeCoordinateController* con);

NASpace* cmGetThreeDeeCoordinateControllerUIElement(CMThreeDeeCoordinateController* con);

CoordSysType cmGetThreeDeeCoordinateControllerCoordSysType(CMThreeDeeCoordinateController* con);
CMLColorType cmGetThreeDeeCoordinateControllerColorSpaceType(CMThreeDeeCoordinateController* con);
NAInt cmGetThreeDeeCoordinateControllerSteps3D(CMThreeDeeCoordinateController* con);

void cmUpdateThreeDeeCoordinateController(CMThreeDeeCoordinateController* con);
