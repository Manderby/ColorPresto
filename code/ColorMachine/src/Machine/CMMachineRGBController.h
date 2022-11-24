
#include "mainC.h"

CM_PROTOTYPE(NASpace);



typedef struct CMMachineRGBController CMMachineRGBController;

CMMachineRGBController* cmAllocMachineRGBController(void);
void cmDeallocMachineRGBController(CMMachineRGBController* con);

NASpace* cmGetMachineRGBControllerUIElement(CMMachineRGBController* con);

void cmUpdateMachineRGBController(CMMachineRGBController* con);
