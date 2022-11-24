
#include "mainC.h"

CM_PROTOTYPE(NASpace);



typedef struct CMMachineLabController CMMachineLabController;

CMMachineLabController* cmAllocMachineLabController(void);
void cmDeallocMachineLabController(CMMachineLabController* con);

NASpace* cmGetMachineLabControllerUIElement(CMMachineLabController* con);

void cmUpdateMachineLabController(CMMachineLabController* con);
