
#include "../mainC.h"
#include "CPThreeDeeController.h"

CP_PROTOTYPE(CPWhitePoints);
CP_PROTOTYPE(NASpace);



typedef struct CPThreeDeeCoordinateController CPThreeDeeCoordinateController;

CPThreeDeeCoordinateController* cpAllocThreeDeeCoordinateController(CPThreeDeeController* threeDeeController);
void cpDeallocThreeDeeCoordinateController(CPThreeDeeCoordinateController* con);

NASpace* cpGetThreeDeeCoordinateControllerUIElement(CPThreeDeeCoordinateController* con);

CoordSysType cpGetThreeDeeCoordinateControllerCoordSysType(CPThreeDeeCoordinateController* con);
CMLColorType cpGetThreeDeeCoordinateControllerColorSpaceType(CPThreeDeeCoordinateController* con);
NAInt cpGetThreeDeeCoordinateControllerSteps3D(CPThreeDeeCoordinateController* con);

void cpUpdateThreeDeeCoordinateController(CPThreeDeeCoordinateController* con);
